#pragma once
// \file IView.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <memory>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class GameUnit;
	class ApplicationLayer;
	class IGameLayer;

	// \class IView 
	// TODO: Class Purpose 
	class IView
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		IView(std::shared_ptr<halo::GameUnit> pGameUnit);

		// Default Destructor 
		virtual ~IView();

		// pure virtuals
		virtual bool Init() = 0;
		virtual void UpdateInput(float delta) { };
		virtual void ViewScene() {};
		virtual void RegisterWithScript() { }

	protected:
		// --------------------------------------------------------------------- //
		// Protected Member Variables
		// --------------------------------------------------------------------- //
		std::shared_ptr<GameUnit> m_pOwner;
		IGameLayer* m_pGameLayer;
		size_t m_listIndex;

		// --------------------------------------------------------------------- //
		// Protected Member Functions
		// --------------------------------------------------------------------- //

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		// Owner Object
		void SetOwner(std::shared_ptr<halo::GameUnit> pUnit) { m_pOwner = pUnit; }
		
		// View List
		void SetListIndex(size_t index) { m_listIndex = index; }
		size_t GetListIndex() const { return m_listIndex; }
	};
}