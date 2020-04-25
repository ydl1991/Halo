#pragma once
// \file TransformComponent.h 
// TODO: File Purpose 
// Created by Dali Yi

#include "..\IComponent.h"

#include <memory>
#include <Lua/lua.hpp>

// Vector
#include <Utils/Math/Vectors/Vector2D.h>
// scripter
#include <GameLayer/Script/LuaScripter.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class TransformComponent 
	// TODO: Class Purpose 
	class TransformComponent
		: public IComponent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		static const ID m_sComponentID;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		TransformComponent() = default;
		TransformComponent(std::weak_ptr<halo::GameUnit> pOwner, const char* pName);

		// Default Destructor 
		virtual ~TransformComponent();

		// Inherited via IComponent
		bool Init(tinyxml2::XMLElement* pData) final override;
		ID GetID() const final override;

		void Move(float x, float y);

		// Lua Macro Register Script
		LUA_U_REGISTER();

		// Lua Custom functions binding
		LUA_CUSTOMGLUE(Move);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		Vector2D m_position;
		float m_rotation;
		Vector2D m_facing;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		// Position
		const Vector2D& GetPosition() const { return m_position; }
		
		// Rotation
		float GetRotation() const { return m_rotation; }

		// Facing Direction
		const Vector2D& FacingTo() const { return m_facing; }
		void UpdateFacing(float x, float y);

		// Lua Getters and Setters Binding
		LUA_GETGLUE(GetX, float, m_position.m_x);
		LUA_SETGLUE(SetX, float, m_position.m_x);
		LUA_GETGLUE(GetY, float, m_position.m_y);
		LUA_SETGLUE(SetY, float, m_position.m_y);
	};
}

// ---------------------------- //
//		Functions For Lua
// ---------------------------- //
namespace Lua
{
	static int TransformComponentMove(lua_State* pState);
}