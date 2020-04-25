#pragma once
// \file ApplicationLayer.h
// TODO: File Purpose
// Created by Dali Yi

// CPP Lib
#include <memory>

// File Lib
#include <GameLayer/IGameLayer.h>
#include <ApplicationLayer/Window/IWindow.h>
#include <ApplicationLayer/Graphics/IGraphics.h>
#include <ApplicationLayer/Audio/IAudio.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class IGameLayer;
	class IOpSys;
	class IKeyboard;
	class IMouse;
	class EngineSetting;

	// \class ApplicationLayer 
	// TODO: Class Purpose 
	class ApplicationLayer
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		// Default Constructor 
		ApplicationLayer();

		// Default Destructor 
		virtual ~ApplicationLayer();

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- /
		static ApplicationLayer* Get();

		bool Init();
		virtual bool PostInit();
		void Run();
		void Cleanup();

		// Pure Vertual Function 
		virtual std::unique_ptr<halo::IGameLayer> CreateGameLayer() = 0;

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		// Static 
		static ApplicationLayer* s_pApp;
		static constexpr char s_dataSavingDirectory[] = "Saved/Logs/";

		// Systems
		std::unique_ptr<IOpSys> m_pOpSys;
		std::unique_ptr<IGameLayer> m_pGameLogic;
		std::unique_ptr<IWindow> m_pWindow;
		std::unique_ptr<IGraphics> m_pGraphics;
		std::unique_ptr<IAudio> m_pAudio;

		// Settings
		std::shared_ptr<EngineSetting> m_pEngineSetting;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //
		bool LoadSystemSettings();
		bool CreateDirectories();
		bool InitSDL();

		// Testing New Stuff Area
		void TestTinyXml2();

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		// Getter 
		IGraphics* GetGraphics() const { return m_pGraphics.get(); }
		IAudio* GetAudio() const { return m_pAudio.get(); }
		IKeyboard* GetKeyboardInput() const { return m_pWindow->GetKeyboard(); }
		IMouse* GetMouseInput() const { return m_pWindow->GetMouse(); }
		IGameLayer* GetGameLayer() { return m_pGameLogic.get(); }
	};
}