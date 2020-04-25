#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <unordered_set>
#include <shlwapi.h>
#include <Lua/lua.hpp>
#include <ApplicationLayer/OS/IOpSys.h>
#include <Utils/Log.h>

// Aliases
using StrVec = std::vector<std::string>;
using StrSet = std::unordered_set<std::string>;

// Functions
static int LuaLog(lua_State* pState);
static int LuaLogError(lua_State* pState);
void ReadFilesModificationRecord(StrSet& timeSet);
void WriteFileUpdateRecord(const StrVec& fileModTime);
bool SearchDirectory(halo::IOpSys* pOS, const std::string& path, const StrSet& record, StrVec& headers, StrVec& fileModTime);

int main(int argc, char* args[])
{
	if (argc < 2)
	{
		return 1;
	}

	// Get all file paths
	std::string path = args[1];
	auto pOS = halo::IOpSys::Create();

	// Retrive and Parse recorded last-modified times of all the header files
	std::unordered_set<std::string> fileTimeSet;
	ReadFilesModificationRecord(fileTimeSet);

	// Vector that stores the new files modication time
	std::vector<std::string> modificationTimeForWrite;

	// Vector that stores the files name after filter
	std::vector<std::string> headerFiles;

	// Get all the header files, filter out the onces that has been newly modified by comparing file modification record 
	bool engineChanged = SearchDirectory(pOS.get(), path + "Engine\\", fileTimeSet, headerFiles, modificationTimeForWrite);
	bool gameChanged = SearchDirectory(pOS.get(), path + "Game\\", fileTimeSet, headerFiles, modificationTimeForWrite);

	// Create Lua State, Lua State creates Lua scripting environment
	auto pLuaState = std::unique_ptr<lua_State, decltype(&lua_close)>(
		luaL_newstate(), &lua_close);
	// Opens up standard library that we can use for lua script
	luaL_openlibs(pLuaState.get());
	// Bind Logger
	lua_register(pLuaState.get(), "LOG", &LuaLog);
	lua_register(pLuaState.get(), "LOG_ERROR", &LuaLogError);

	// Create global tables
	lua_newtable(pLuaState.get());

	// Loop through to parse in lua
	for (size_t i = 1; i <= headerFiles.size(); ++i)
	{
		lua_pushstring(pLuaState.get(), headerFiles[i - 1].c_str());
		lua_rawseti(pLuaState.get(), -2, i);
	}

	// Create a globle variable and pack everything above into this variable called logic
	lua_setglobal(pLuaState.get(), "g_headerFiles");

	bool error = luaL_dofile(pLuaState.get(), "GluaGen.lua");
	if (error)
	{
		LOG_LUAERROR(lua_tostring(pLuaState.get(), -1));
		lua_pop(pLuaState.get(), 1);
	}
	
	// write file modification time to .txt
	if (engineChanged || gameChanged)
		WriteFileUpdateRecord(modificationTimeForWrite);
	else
		LOG_DISPLAY("No File Have Been Updated Since Last Time! No Gen File Generated!");

	return 0;
}

int LuaLog(lua_State* pState)
{
	// Get the message from the stack
	// In lua, stack can be accessed backwards by using negative numbers:
	//        [-1] top of the stack
	const char* message = lua_tostring(pState, -1);

	// Grab debug info from the stack (where this was called from)
	lua_Debug ar;
	lua_getstack(pState, 1, &ar);
	lua_getinfo(pState, "Slnt", &ar);

	// Shorten file name for easy reading
	static std::string file;
	file = ar.short_src;
	file = file.substr(file.rfind('/') + 1);

	// Log it!
	LOG_LUA_A(ar.currentline, file.c_str(), message);

	return 0;
}

int LuaLogError(lua_State* pState)
{
	// Get the message from the stack
	// In lua, stack can be accessed backwards by using negative numbers:
	//        [-1] top of the stack
	const char* message = lua_tostring(pState, -1);

	// Grab debug info from the stack (where this was called from)
	lua_Debug ar;
	lua_getstack(pState, 1, &ar);
	lua_getinfo(pState, "Slnt", &ar);

	// Shorten file name for easy reading
	static std::string file;
	file = ar.short_src;
	file = file.substr(file.rfind('/') + 1);

	// Log it!
	LOG_LUAERROR_A(ar.currentline, file.c_str(), message);

	return 0;
}

void ReadFilesModificationRecord(StrSet& timeSet)
{
	std::fstream newfile;
	newfile.open("Data/LastUpdateTime.txt", std::ios::in);
	//checking whether the file is open
	if (newfile.is_open())
	{   
		std::string temp;
		//read data from file object and put it into string.
		while (std::getline(newfile, temp)) 
		{ 
			timeSet.emplace(temp);
		}
		//close the file object.
		newfile.close(); 
	}
}

void WriteFileUpdateRecord(const StrVec& fileModTime)
{
	std::fstream newfile;
	newfile.open("Data/LastUpdateTime.txt", std::ios::out);
	//checking whether the file is open
	if (newfile.is_open())
	{
		for (auto& s : fileModTime)
		{
			newfile << s + "\n";
		}

		newfile.close();
	}
}

bool SearchDirectory(halo::IOpSys* pOS, const std::string& path, const StrSet& record, StrVec& headers, StrVec& fileModTime)
{
	bool write = false;
	// Get engine files
	auto engineFiles = pOS->GetAllFiles(path);
	// Fileter Files
	for (auto& file : engineFiles)
	{
		std::string filePath = path + file;
		const size_t kSize = filePath.size();
		// Only file with extention .h is added
		if (filePath[kSize - 1] == 'h' && filePath[kSize - 2] == '.')
		{
			// get file modification info from the system
			std::string fileInfo = "";
			pOS->GetFileLastModifiedTime(filePath.c_str(), fileInfo);

			fileInfo = filePath.substr(filePath.find_last_of('\\') + 1) + " " + fileInfo;

			// if the current fileInfo is not exist in our record, means it is changed since last time we run GluaGen
			if (record.find(fileInfo) == record.end())
			{
				write = true;
				// so we update it to our headers
				headers.emplace_back(std::move(filePath));
			}

			fileModTime.emplace_back(fileInfo);
		}
	}

	return write;
}
