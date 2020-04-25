#include "LuaScripter.h"

// C++ Library
#include <assert.h>

// Engine Library
#include <GameLayer/Script/LuaScripter.h>
#include <GameLayer/Resource/IResource.h>
#include <Utils/Log.h>

using halo::LuaScripter;

LuaScripter::LuaScripter()
	: m_pState{ nullptr, nullptr }
	, m_stackSize{ 0 }
{
	
}

LuaScripter::~LuaScripter()
{
	
}

bool halo::LuaScripter::Init()
{
	// Create Lua State, Lua State creates Lua scripting environment
	// Lua State contains all the lua code and lua stack
	m_pState = std::unique_ptr<lua_State, decltype(&lua_close)>(luaL_newstate(), &lua_close);

	// Opens up standard library that we can use for lua script
	luaL_openlibs(m_pState.get());

	return true;
}

bool halo::LuaScripter::RunScript(std::shared_ptr<IResource> pResource)
{
	bool error = luaL_loadbuffer(m_pState.get(),
		reinterpret_cast<char*>(pResource->GetData().data()),
		pResource->GetData().size(), "script")
		|| lua_pcall(m_pState.get(), 0, 0, 0);

	if (error)
	{
		PrintLuaError();
	}

	return !error;
}

bool halo::LuaScripter::RunScript(const char* fileName)
{
	bool error = luaL_dofile(m_pState.get(), fileName);

	if (error)
	{
		PrintLuaError();
	}

	return !error;
}

void halo::LuaScripter::CreateTable()
{
	lua_newtable(m_pState.get());
	++m_stackSize;
}

void halo::LuaScripter::AddToTable(const char* pKey)
{
	// Add whatever is currently on the stack
	// useful for adding tables to tables
	lua_setfield(m_pState.get(), -2, pKey);
	--m_stackSize;
}

void halo::LuaScripter::AddToTable(size_t index)
{
	lua_rawseti(m_pState.get(), -2, index);
	--m_stackSize;
}

void halo::LuaScripter::AddToTable(const char* pKey, lua_CFunction pFunction)
{
	// Add Lua function
	lua_pushcfunction(m_pState.get(), pFunction);
	lua_setfield(m_pState.get(), -2, pKey);
}

void halo::LuaScripter::AddToTable(const char* pKey, void* pUserData)
{
	// C++ pointer type of data 
	lua_pushlightuserdata(m_pState.get(), pUserData);
	lua_setfield(m_pState.get(), -2, pKey);
}

void halo::LuaScripter::RetrieveElementFromTable(const char* pKey)
{
	lua_getfield(m_pState.get(), -1, pKey);
	++m_stackSize;
}

void halo::LuaScripter::RetrieveElementFromTable(uint32_t index)
{
	lua_geti(m_pState.get(), -1, index);
	++m_stackSize;
}

void halo::LuaScripter::GetGlobal(const char* pName)
{
	// Retrieve a Lua global variable and store it on the top of the Lua stack
	lua_getglobal(m_pState.get(), pName);
	++m_stackSize;
}

void halo::LuaScripter::SetGlobal(const char* pName)
{
	// pop the value at the top of the lua stack and set it  
	// as new value of the global variable "name"
	lua_setglobal(m_pState.get(), pName);
	--m_stackSize;
}

void halo::LuaScripter::PushNumber(double number)
{
	lua_pushnumber(m_pState.get(), number);
	++m_stackSize;
}

void halo::LuaScripter::PushString(const char* pStr)
{
	lua_pushstring(m_pState.get(), pStr);
	++m_stackSize;
}

void halo::LuaScripter::PushInt(int integer)
{
	lua_pushinteger(m_pState.get(), integer);
	++m_stackSize;
}

void halo::LuaScripter::PushBool(bool boolean)
{
	lua_pushboolean(m_pState.get(), boolean);
	++m_stackSize;
}

void halo::LuaScripter::PushNil()
{
	lua_pushnil(m_pState.get());
	++m_stackSize;
}

double halo::LuaScripter::GetNumber()
{
	// get the number at the top of the stack
	double val = lua_tonumber(m_pState.get(), -1);
	Pop();
	return val;
}

double halo::LuaScripter::GetNumber(int index)
{
	assert(index > 0 && index <= m_stackSize);

	// get the number at the index of the stack
	double val = lua_tonumber(m_pState.get(), index);
	Pop();
	return val;
}

const char* halo::LuaScripter::GetString()
{
	// get the string at the top of the stack
	const char* val = lua_tostring(m_pState.get(), -1);
	Pop();
	return val;
}

const char* halo::LuaScripter::GetString(int index)
{
	assert(index > 0 && index <= m_stackSize);

	const char* val = lua_tostring(m_pState.get(), index);
	Pop();
	return val;
}

lua_Integer halo::LuaScripter::GetInt()
{
	// get the int at the top of the stack
	auto val = lua_tointeger(m_pState.get(), -1);
	Pop();
	return val;
}

lua_Integer halo::LuaScripter::GetInt(int index)
{
	assert(index > 0 && index <= m_stackSize);

	auto val = lua_tointeger(m_pState.get(), index);
	Pop();
	return val;
}

bool halo::LuaScripter::GetBool()
{
	// get the bool at the top of the stack
	bool val = lua_toboolean(m_pState.get(), -1);
	Pop();
	return val;
}

bool halo::LuaScripter::GetBool(int index)
{
	assert(index > 0 && index <= m_stackSize);

	bool val = lua_toboolean(m_pState.get(), index);
	Pop();
	return val;
}

void halo::LuaScripter::StartFunction(const char* pFunctionName)
{
	GetGlobal(pFunctionName);
}

bool halo::LuaScripter::CallFunction(uint32_t numReturn)
{
	if (lua_pcall(m_pState.get(), m_stackSize - 1, numReturn, 0) != 0)
	{
		PrintLuaError();
		m_stackSize = 0;
		return false;
	}

	m_stackSize = numReturn;
	return true;
}

void halo::LuaScripter::Pop()
{
	lua_pop(m_pState.get(), 1);
	--m_stackSize;
}

void halo::LuaScripter::Pop(int32_t num)
{
	assert(m_stackSize >= num);
	lua_pop(m_pState.get(), num);
	m_stackSize -= num;
}

void halo::LuaScripter::PopAll()
{
	lua_pop(m_pState.get(), m_stackSize);
	assert(lua_gettop(m_pState.get()) == 0);
	m_stackSize = 0;
}

void halo::LuaScripter::PrintLuaError()
{
	LOG_LUAERROR(lua_tostring(m_pState.get(), -1));
	lua_pop(m_pState.get(), 1);
}

void halo::LuaScripter::PrintCurrentStack()
{
	int nItems = lua_gettop(m_pState.get());

	LOG_LUA("Printing Lua Stack! Number of Items Currently in Stack: (%d)", nItems);

	for (int i = 1; i <= nItems; ++i)
	{
		int type = lua_type(m_pState.get(), i);

		switch (type)
		{
		case LUA_TNUMBER:
			LOG_LUA("Item at Stack Index [%d] - %s ( Number )", i, lua_tonumber(m_pState.get(), i));
			break;
		case LUA_TSTRING:
			LOG_LUA("Item at Stack Index [%d] - %s ( String )", i, lua_tostring(m_pState.get(), i));
			break;
		case LUA_TBOOLEAN:
			LOG_LUA("Item at Stack Index [%d] - %s ( Bool )", i, lua_toboolean(m_pState.get(), i));
			break;
		case LUA_TNIL:
			LOG_LUA("Item at Stack Index [%d] - ( Nil )", i);
			break;
		case LUA_TFUNCTION:
			LOG_LUA("Item at Stack Index [%d] - %s ( Function )", i, luaL_tolstring(m_pState.get(), i, nullptr));
			lua_pop(m_pState.get(), 1); // remove the string
			break;
		case LUA_TTABLE:
			LOG_LUA("Item at Stack Index [%d] - %s ( Table )", i, luaL_tolstring(m_pState.get(), i, nullptr));
			lua_pop(m_pState.get(), 1); // remove the string
			PrintTable(i);
			break;
		}
	}
}

void halo::LuaScripter::PrintTable(uint32_t index)
{
	LOG_LUA("Printing Table at Index - %d!", index);
	InternalPrintTable(index, 0);
}

void halo::LuaScripter::InternalPrintTable(uint32_t index, int level)
{
	std::string layerSpace = "";
	int layer = level;
	while (layer--)
	{
		layerSpace += "  ";
	}
	
	lua_pushnil(m_pState.get());
	while (lua_next(m_pState.get(), index) != 0)
	{
		std::string key = lua_tostring(m_pState.get(), -2);
		int type = lua_type(m_pState.get(), -1);

		switch (type)
		{
		case LUA_TNUMBER:
			LOG_LUA(std::string(layerSpace + key + " ( Number ) - Value: %s").c_str(), lua_tonumber(m_pState.get(), -1));
			break;
		case LUA_TSTRING:
			LOG_LUA(std::string(layerSpace + key + " ( String ) - Value: %s").c_str(), lua_tostring(m_pState.get(), -1));
			break;
		case LUA_TBOOLEAN:
			LOG_LUA(std::string(layerSpace + key + " ( Bool ) - Value: %s").c_str(), lua_toboolean(m_pState.get(), -1));
			break;
		case LUA_TNIL:
			LOG_LUA(std::string(layerSpace + key + " ( Nil ) - Value: Nil").c_str());
			break;
		case LUA_TFUNCTION:
			LOG_LUA(std::string(layerSpace + key + " ( Function )").c_str());
			break;
		case LUA_TTABLE:
			LOG_LUA(std::string(layerSpace + key + " ( Table )").c_str());
			InternalPrintTable(lua_gettop(m_pState.get()), level + 1);
			break;
		}

		lua_pop(m_pState.get(), 1);
	}
}
