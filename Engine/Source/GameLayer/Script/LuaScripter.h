#pragma once
// \file LuaScripter.h 
// TODO: File Purpose 
// Created by Dali Yi

// ------------------------------------ //
//				Lua Macro
// ------------------------------------ //
#define LUA_GETGLUE(functionName, memberType, varName) memberType functionName() const { return varName; }
#define LUA_SETGLUE(functionName, memberType, varName) void functionName(memberType arg) { varName = arg; }
#define LUA_REGISTER() virtual void RegisterWithScript() final override;
#define LUA_U_REGISTER() LUA_REGISTER()
#define LUA_CUSTOMGLUE(functionName)

#include ".\IScripter.h"

// C++ Library
#include <memory>
#include <Lua/lua.hpp>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class LuaScripter 
	// TODO: Class Purpose 
	class LuaScripter final : public IScripter
	{
		using UniqueLuaState = std::unique_ptr<lua_State, decltype(&lua_close)>;
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		LuaScripter();

		// Default Destructor 
		virtual ~LuaScripter();

		// Inherited via IScripter
		virtual bool Init() final override;
		virtual bool RunScript(std::shared_ptr<IResource> pResource) final override;
		virtual bool RunScript(const char* filepath) final override;
		
		// Print
		void PrintCurrentStack();
		void PrintTable(uint32_t index);

		// Helper Functions
		// Table
		void CreateTable();
		void AddToTable(const char* pKey);
		void AddToTable(size_t index);
		void AddToTable(const char* pKey, lua_CFunction pFunction);
		void AddToTable(const char* pKey, void* pUserData);
		void RetrieveElementFromTable(const char* pKey);
		void RetrieveElementFromTable(uint32_t index);
		// Push
		void PushNumber(double number);
		void PushString(const char* pStr);
		void PushInt(int integer);
		void PushBool(bool boolean);
		void PushNil();
		// Call Lua Function
		void StartFunction(const char* pFunctionName);
		bool CallFunction(uint32_t numReturn);
		// Pop
		void Pop();
		void Pop(int32_t num);
		void PopAll();

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		UniqueLuaState m_pState;
		int32_t m_stackSize;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //
		// Error printing
		void PrintLuaError();
		
		// Print
		void InternalPrintTable(uint32_t index, int level);

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		// Get
		double GetNumber();
		double GetNumber(int index);
		const char* GetString();
		const char* GetString(int index);
		lua_Integer GetInt();
		lua_Integer GetInt(int index);
		bool GetBool();
		bool GetBool(int index);
		// Global
		void GetGlobal(const char* pName);
		void SetGlobal(const char* pName);
	};
}