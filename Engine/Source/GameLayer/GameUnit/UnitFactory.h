#pragma once
// \file UnitFactory.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <memory>
#include <functional>
#include <unordered_map>

#include <Utils/TinyXml/tinyxml2.h>
#include <GameLayer/GameUnit/GameUnit.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class IComponent;
	class IProcess;

	// \class UnitFactory 
	// TODO: Class Purpose 
	class UnitFactory
	{
	public:
		// Alias
		using ComponentFunction = std::function<std::unique_ptr<IComponent>(std::shared_ptr<GameUnit>, const char*)>;
		using ProcessFunction = std::function<std::shared_ptr<IProcess>(std::shared_ptr<GameUnit>)>;
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		UnitFactory();

		// Default Destructor 
		~UnitFactory();

		std::shared_ptr<GameUnit> CreateUnit(const char* pFileName);
		void RegisterComponentCreator(const char* pComponentName, ComponentFunction pFunction);
		void RegisterProcessCreator(const char* pProcessName, ProcessFunction pFunction);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		// Factory
		static GameUnit::ID s_nextUnitID;
		std::unordered_map<std::string, ComponentFunction> m_componentCreators;
		std::unordered_map<std::string, ProcessFunction> m_processCreators;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //
		std::unique_ptr<IComponent> CreateComponent(tinyxml2::XMLElement* pData, std::shared_ptr<GameUnit> pOwner);
		std::shared_ptr<IProcess> CreateProcess(tinyxml2::XMLElement* pData, std::shared_ptr<GameUnit> pOwner);

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //

	};
}