#include "UnitFactory.h"

#include <Utils/Log.h>
#include <GameLayer/Components/RenderableComponent/RenderableComponent.h>
#include <ApplicationLayer/ApplicationLayer.h>


using halo::UnitFactory;

halo::GameUnit::ID UnitFactory::s_nextUnitID = 0;

UnitFactory::UnitFactory()
{
	
}

UnitFactory::~UnitFactory()
{
	
}

std::shared_ptr<halo::GameUnit> halo::UnitFactory::CreateUnit(const char* pFileName)
{
	// Everything is in that namespace
	using namespace tinyxml2;
	XMLDocument doc;
	XMLError error = doc.LoadFile(pFileName);

	if (error != XML_SUCCESS)
	{
		LOG_ERROR("Failed to load file: %s -- %s", pFileName, XMLDocument::ErrorIDToName(error));
		return nullptr;
	}

	// Create Game Unit
	std::shared_ptr<GameUnit> pUnit = std::make_shared<GameUnit>(s_nextUnitID);
	++s_nextUnitID;

	// Get the root
	XMLElement* pRoot = doc.RootElement();
	if (!pUnit->Init(pRoot))
	{
		LOG_ERROR("Failed to init game unit from %s.", pFileName);
		return nullptr;
	}

	// Get Game Layer Pointer
	IGameLayer* pGameLayer = halo::ApplicationLayer::Get()->GetGameLayer();

	// Parse and add components
	for (XMLElement* pComponent = pRoot->FirstChildElement("Components")->FirstChildElement();
		pComponent != nullptr;
		pComponent = pComponent->NextSiblingElement())
	{
		LOG_DISPLAY("Found Component: %s.", pComponent->Name());

		// Create Component
		auto component = CreateComponent(pComponent, pUnit);
		// Register component if its a renderable component
		if (component->GetID() == RenderableComponent::m_sComponentID)
		{
			pGameLayer->RegisterRenderable(pUnit->GetID(), dynamic_cast<RenderableComponent*>(component.get()));
			LOG_DISPLAY("Successfully Registered Renderable for Unit - %d", pUnit->GetID());
		}
		// add component to game unit
		pUnit->AddComponent(std::move(component));
	}

	if (!pUnit->PostInit())
	{
		LOG_ERROR("Game unit %s failed PostInit.", pUnit->GetName());
		return nullptr;
	}

	// Parse and add components
	for (XMLElement* pProcess = pRoot->FirstChildElement("Processes")->FirstChildElement();
		pProcess != nullptr;
		pProcess = pProcess->NextSiblingElement())
	{
		LOG_DISPLAY("Found Process: %s.", pProcess->Name());

		// Create Process
		auto process = CreateProcess(pProcess, pUnit);

		// Attach Process
		pGameLayer->GetProcessController().AttachProcess(std::move(process));
	}

	return pUnit;
}

void halo::UnitFactory::RegisterComponentCreator(const char* pComponentName, ComponentFunction pFunction)
{
	m_componentCreators.emplace(pComponentName, pFunction);
}

void halo::UnitFactory::RegisterProcessCreator(const char* pProcessName, ProcessFunction pFunction)
{
	m_processCreators.emplace(pProcessName, pFunction);
}

std::unique_ptr<halo::IComponent> halo::UnitFactory::CreateComponent(tinyxml2::XMLElement* pData, std::shared_ptr<GameUnit> pOwner)
{
	const char* pName = pData->Name();
	std::unique_ptr<IComponent> pComponent;

	// find component creator function
	auto createItr = m_componentCreators.find(pName);
	if (createItr != m_componentCreators.end())
	{
		//Found it! Create Component!
		pComponent = std::move(createItr->second(pOwner, pName));
	}
	else
	{
		LOG_ERROR("Could not find component creator for: %s", pName);
		return nullptr;
	}

	// Init Component
	if (!pComponent->Init(pData))
	{
		LOG_ERROR("Failed to init %s on %s", pName, pOwner->GetName().c_str());
		return nullptr;
	}

	return pComponent;
}

std::shared_ptr<halo::IProcess> halo::UnitFactory::CreateProcess(tinyxml2::XMLElement* pData, std::shared_ptr<GameUnit> pOwner)
{
	const char* pName = pData->Name();
	std::shared_ptr<IProcess> pProcess;

	// find process creator function
	auto createItr = m_processCreators.find(pName);
	if (createItr != m_processCreators.end())
	{
		//Found it! Create Process!
		pProcess = std::move(createItr->second(pOwner));
	}
	else
	{
		LOG_ERROR("Could not find process creator for: %s", pName);
		return nullptr;
	}

	// Init Process
	if (!pProcess->Init(pData))
	{
		LOG_ERROR("Failed to init %s on %s", pName, pOwner->GetName().c_str());
		return nullptr;
	}

	return pProcess;
}
