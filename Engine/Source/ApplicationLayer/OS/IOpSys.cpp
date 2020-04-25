#include "IOpSys.h"

#include <chrono>
#include <filesystem>
#include <Windows.h>

#include <ApplicationLayer/OS/Win32.h>
#include <Utils/Log.h>

using halo::IOpSys;

IOpSys::IOpSys()
{
	
}

IOpSys::~IOpSys()
{
	
}

std::unique_ptr<IOpSys> halo::IOpSys::Create()
{
#ifdef _WIN32
	return std::make_unique<Win32>();
#else
	// TODO: Log error
	return nullptr;
#endif
}

// ----------------------------- //
// Create folder according to path
// ----------------------------- //
bool halo::IOpSys::MakeFolder(const char* path)
{
	// Make Folder (make folder)
	if (!std::filesystem::create_directories(path))
	{
		return true;
	}

	return false;
}

//---------------------------//
//		Generate GUID
//---------------------------//
halo::IOpSys::ID halo::IOpSys::GUIDGenerator()
{
#ifdef _WIN32
	UUID uuid;
	auto ignore = UuidCreate(&uuid);

	char* str;
	ignore = UuidToStringA(&uuid, (RPC_CSTR*)&str);
	
	size_t id = std::hash<std::string>{}(str);

	RpcStringFreeA((RPC_CSTR*)&str);

	return id;
#else
	return "";
#endif
}
