#include "ApplicationLayer.h"

#include <fstream>
#include <chrono>
// temporary
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

#include <ApplicationLayer/OS/IOpSys.h>
#include <ApplicationLayer/Input/IKeyboard.h>
#include <ApplicationLayer/Input/IMouse.h>
#include <ApplicationLayer/Settings/EngineSetting.h>
#include <GameLayer/Resource/ResourceCache.h>
#include <Utils/Log.h>

// TEMPORARY - Testing Xml Parsing
#include <Utils/TinyXml/tinyxml2.h>
// TEMPORARY - Testing Actor Factory
#include <GameLayer/GameUnit/UnitFactory.h>

using halo::ApplicationLayer;

ApplicationLayer* ApplicationLayer::s_pApp = nullptr;

ApplicationLayer::ApplicationLayer()
	: m_pEngineSetting{ nullptr }
{
	//

	
}

ApplicationLayer::~ApplicationLayer()
{
	
}

ApplicationLayer* halo::ApplicationLayer::Get()
{
	// TODO: insert return statement here
	return s_pApp;
}

// ------------------------------- //
//	Initialize Application Layer
//-------------------------------- //
bool halo::ApplicationLayer::Init()
{
	LOG_SYSTEM("Initializing ApplicationLayer.");
	s_pApp = this;

	// Init Operating System
	m_pOpSys = IOpSys::Create();
	if (!m_pOpSys)
	{
		LOG_ERROR("Failed to Create System.");
		return false;
	}

	// Load System Settings
	if (!LoadSystemSettings())
	{
		LOG_WARNING("Failed to Load System Settings.");
	}

	// Create necessary directories
	if (!CreateDirectories())
	{
		LOG_WARNING("Failed to Create Saving Folder.");
	}

	// Init Log 
	if (!Log::GetInstance()->Initialize(m_pOpSys.get(), m_pEngineSetting))
	{
		LOG_ERROR("Failed to Initialize Logger.");
		return false;
	}

	// Create Game
	m_pGameLogic = CreateGameLayer();
	if (!m_pGameLogic)
	{
		LOG_ERROR("Failed to Create Game.");
		return false;
	}

	// Init SDL (window, renderer, input system)
	if (!InitSDL())
	{
		LOG_ERROR("Failed to init SDL. Exit system now.");
		return false;
	}

	// Resource Cache
	bool result = ResourceCache::Get().Init(m_pGraphics.get(), m_pAudio.get());
	if (!result)
	{
		LOG_ERROR("Failed to init Resource Cache!");
		return false;
	}

	// Init Game
	if (!m_pGameLogic->Init())
	{
		LOG_ERROR("Failed to Init Game.");
		return false;
	}

	// Log out system and game info
	LOG_SYSTEM("OS: %s", m_pOpSys->GetSystemName());
	LOG_SYSTEM("Game Name: %s", m_pGameLogic->GetGameName());

	return PostInit();
}

bool halo::ApplicationLayer::PostInit()
{
	// post init game layer which init IViews
	if (!m_pGameLogic->PostInit())
	{
		LOG_ERROR("Failed to init views!");
		return false;
	}

	return true;
}

// ------------------------------- //
//		Run Application Layer
//-------------------------------- //
void halo::ApplicationLayer::Run()
{
	// Calculate delta seconds
	// std::chrono
	
	using namespace std::chrono;

	auto lastClock = high_resolution_clock::now();

	// main loop
	while (m_pWindow->ProcessEvents() && !m_pGameLogic->WantsToQuit())
	{
		// how much time has elapsed since the last frame?
		high_resolution_clock::time_point currentClock = high_resolution_clock::now();
		float deltaSeconds = duration_cast<duration<float>>(currentClock - lastClock).count();

#if _DEBUG
		if (deltaSeconds > 1)
		{
			LOG_WARNING("High frame time detected. DeltaSeconds manually Set!")
			deltaSeconds = 0.016f;
		}
#endif
		// Simulate Game
		m_pGameLogic->Update(deltaSeconds);

		// Update Audio
		m_pAudio->Update();

		// Refresh keyboard and mouse state at the end of game loop
		m_pWindow->NextFrame();

		lastClock = currentClock;
	}


	LOG_SYSTEM("Running Successfully.");
}

// ------------------------------- //
//		Clean Up Layer
//-------------------------------- //
void halo::ApplicationLayer::Cleanup()
{
	LOG_SYSTEM("Cleaning Up.");

	ResourceCache::Get().CleanUp();

	m_pGameLogic = nullptr;
	m_pGraphics = nullptr;
	m_pAudio = nullptr;
	m_pWindow = nullptr;
	m_pOpSys = nullptr;
}

// ------------------------------- //
//		Load System Settings
//-------------------------------- //
bool halo::ApplicationLayer::LoadSystemSettings()
{
	// open the directory and file name
	std::ifstream in;
	in.open("Setting/EngineSettings/Settings.txt", std::ios::in);

	if (!in.is_open())
	{
		LOG_ERROR("Failed to open engine setting file, unable to load settings.");
		return false;
	}

	// Collect saving info
	std::unordered_map<std::string, std::string> temp;
	std::string key = "", value = "";
	while (in >> key >> value)
	{
		temp[key] = value;
	}

	// close file
	in.close();

	// pass into engine setting
	m_pEngineSetting = std::make_shared<EngineSetting>(temp);

	return true;
}

// ------------------------------- //
//		Make Folders In Advance
//-------------------------------- //
bool halo::ApplicationLayer::CreateDirectories()
{
	if (!m_pOpSys->MakeFolder(s_dataSavingDirectory))
		return false;

	return true;
}

bool halo::ApplicationLayer::InitSDL()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	TTF_Init();

	// Create SDL Window
	m_pWindow = m_pOpSys->CreateSystemWindow(m_pGameLogic->GetGameName(), 
											 m_pEngineSetting->GetInt("windowWidth"),
		                                     m_pEngineSetting->GetInt("windowHeight"));

	if (!m_pWindow)
	{
		return false;
	}

	// Create SDL Graphic Renderer
	m_pGraphics = IGraphics::Create();
	if (!m_pGraphics)
	{
		LOG_ERROR("Failed to Create IGraphics Instance.");
		return false;
	}

	// Init Graphic Renderer
	if (!m_pGraphics->Init(m_pWindow.get()))
	{
		return false;
	}

	// Init Keyboard and Mouse and Attach to SDL Window
	auto pKeyboard = IKeyboard::Create();
	if (!pKeyboard)
	{
		LOG_ERROR("Failed to Create Keyboard Instance.");
		return false;
	}
	if (!pKeyboard->Init())
	{
		return false;
	}

	auto pMouse = IMouse::Create();
	if (!pMouse)
	{
		LOG_ERROR("Failed to Create Mouse Instance.");
		return false;
	}
	if (!pMouse->Init())
	{
		return false;
	}

	// Attach our keyboard and mouse to SDL window
	m_pWindow->AttachKeyboard(std::move(pKeyboard));
	m_pWindow->AttachMouse(std::move(pMouse));

	// Init SDL Audio
	m_pAudio = halo::IAudio::Create();
	if (!m_pAudio)
	{
		LOG_ERROR("Failed to Create Audio.");
		return false;
	}
	
	if (!m_pAudio->Init())
	{
		return false;
	}

	return true;
}

// ----- //
// test
void halo::ApplicationLayer::TestTinyXml2()
{
	// Everything is in that namespace
	using namespace tinyxml2;
	XMLDocument doc;
	const char* pFileName = "Assets/XML/TestPlayerUnit.xml";
	XMLError error = doc.LoadFile(pFileName);

	if (error != XML_SUCCESS)
	{
		LOG_ERROR("Failed to load file: %s -- %s", pFileName, XMLDocument::ErrorIDToName(error));
		return;
	}

	// Get the root
	XMLElement* pRoot = doc.RootElement();

	// Grab Data
	XMLElement* pTrans = pRoot->FirstChildElement("TransformComponent");
	XMLElement* pPosition = pTrans->FirstChildElement("Position");

	float x = pPosition->FloatAttribute("x");
	int y = pPosition->IntAttribute("y");
	
	LOG_DISPLAY("(%d -- %d)", x, y);
}
