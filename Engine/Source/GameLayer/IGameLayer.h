#pragma once
// \file IGameLayer.h 
// TODO: File Purpose 
// Created by Dali Yi

// C++ Library
#include <memory>
#include <vector>
#include <unordered_map>
// Engine Library
#include <GameLayer/GameUnit/UnitFactory.h>
#include <GameLayer/Process/ProcessController.h>
#include <GameLayer/Event/EventDispatcher.h>
#include <GameLayer/Script/IScripter.h>
#include <GameLayer/Script/LuaScripter.h>
#include <GameLayer/Physics/IPhysicsSimulation.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class IView;
	class RenderableComponent;

	// \class IGameLayer 
	// TODO: Class Purpose 
	class IGameLayer
	{
	public:
		// Alias
		using ID = uint32_t;
		using GameUnitMap = std::unordered_map<GameUnit::ID, std::shared_ptr<GameUnit>>;
		using RenderableMap = std::unordered_map<GameUnit::ID, RenderableComponent*>;
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		
		// ----- Test ---- //
		int m_testKill;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		IGameLayer();

		// Default Destructor 
		virtual ~IGameLayer();

		virtual const char* GetGameName() const = 0;

		// virtuals
		virtual bool Init();
		virtual bool PostInit();
		virtual void Update(float deltaSeconds);
		virtual std::shared_ptr<GameUnit> SpawnGameUnit(const char* filename);

		// Functions
		void AddGameUnit(GameUnit::ID id, std::shared_ptr<GameUnit> pUnit);
		void DestroyGameUnit(GameUnit::ID id);
		void RegisterRenderable(GameUnit::ID id, RenderableComponent* pRenderable);
		
		// View Related
		void AddView(std::unique_ptr<IView> pView);
		void AddPendingViews(std::unique_ptr<IView> pView);
		void AddDeleteView(size_t index);
		void DeleteViews();

	protected:
		// --------------------------------------------------------------------- //
		// Protected Member Variables
		// --------------------------------------------------------------------- //
		UnitFactory m_unitFactory;
		GameUnitMap m_unitMap;
		RenderableMap m_renderableMap;
		ProcessController m_processController;
		std::unique_ptr<IScripter> m_scripter;

		// --------------------------------------------------------------------- //
		// Protected Member Functions
		// --------------------------------------------------------------------- //
		void AddPendingViewsToViews();
		virtual void RegisterWithScript();

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		std::vector<std::unique_ptr<IView>> m_views;
		std::vector<std::unique_ptr<IView>> m_pendingViews;
		std::vector<size_t> m_viewDeleteList;
		std::unique_ptr<halo::IPhysicsSimulation> m_pPhysics;
		bool m_wantsToQuit;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //
		void Cleaning();
		void RegisterComponentCreationFunctions();
		void RegisterProcessCreationFunctions();
		void RemoveRenderable(GameUnit::ID id);
		bool LuaRemoveUnit(GameUnit::ID id);

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		const UnitFactory& GetUnitFactory() const { return m_unitFactory; }
		const GameUnitMap& GetAllUnits() const { return m_unitMap; }
		std::shared_ptr<GameUnit> GetGameUnit(GameUnit::ID id) { return m_unitMap[id]; }
		const RenderableMap& GetAllRenderables() const { return m_renderableMap; }
		ProcessController& GetProcessController() { return m_processController; }
		bool WantsToQuit() const { return m_wantsToQuit; }
		
		// Get Scripter according to language
		template<class LanguageScripter>
		LanguageScripter* GetScripter();
	};

	// Get Scripter according to the language
	template<class LanguageScripter>
	inline LanguageScripter* IGameLayer::GetScripter()
	{
		return dynamic_cast<LanguageScripter*>(m_scripter.get());
	}
}