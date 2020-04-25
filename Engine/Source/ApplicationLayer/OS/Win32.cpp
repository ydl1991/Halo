#include "Win32.h"

#include <Windows.h>

#include <ApplicationLayer/Window/WindowSDL.h>

using halo::Win32;

Win32::Win32()
{
	
}

Win32::~Win32()
{
	
}

const char* halo::Win32::GetSystemName() const
{
	return "Windows";
}

std::unique_ptr<halo::IWindow> halo::Win32::CreateSystemWindow(const char* name, uint32_t width, uint32_t height)
{
	// TODO: Check which library to use using preprocessor defines

	// Right now we are only using SDL in concert with windows
	std::unique_ptr<IWindow> pWindow = std::make_unique<WindowSDL>();
	if (pWindow->Init(name, width, height))
	{
		return pWindow;
	}

	return nullptr;
}

//---------------------------//
// Get Current Date And Time
//---------------------------//
void halo::Win32::GetDateTime(std::string& date, std::string& time)
{
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	char buf[40] = { 0 };

	// Get Date
	sprintf_s(buf, "%04d-%02d-%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay);
	date = buf;

	// Get Time
	sprintf_s(buf, "%02d:%02d:%02d", sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	time = buf;
}

//-----------------------------//
// Get File Last Modified Time
//-----------------------------//
void halo::Win32::GetFileLastModifiedTime(const char* filePath, std::string& time)
{
	WIN32_FILE_ATTRIBUTE_DATA fileAttrData = { 0 };
	GetFileAttributesExA(filePath, GetFileExInfoStandard, &fileAttrData);
	
	FILETIME ftLastModified = fileAttrData.ftLastWriteTime;
	SYSTEMTIME sysTime, localTime;
	FileTimeToSystemTime(&ftLastModified, &sysTime);
	SystemTimeToTzSpecificLocalTime(nullptr, &sysTime, &localTime);

	char buf[40] = { 0 };
	sprintf_s(buf, "%04d-%02d-%02d %02d:%02d", localTime.wYear, localTime.wMonth, localTime.wDay, localTime.wHour, localTime.wMinute);
	time = buf;
}

//-----------------------------//
// Set Console Text Print Color
//-----------------------------//
void halo::Win32::SetConsoleTextColor(halo::IOpSysTextColor color)
{
	// Change console color
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

//-------------------------------//
// Set Current Working Directory
//-------------------------------//
void halo::Win32::SetCurrentWorkingDirectory(const std::string& path)
{
	SetCurrentDirectoryA(path.c_str());
}

std::vector<std::string> halo::Win32::GetAllFiles(const std::string& path)
{
	std::vector<std::string> files;
	IntervalGetFilesRecursive(path, "", files);
	return files;
}

void halo::Win32::IntervalGetFilesRecursive(const std::string& path, const std::string& dir, std::vector<std::string>& files)
{
	std::string fullPath = path + "\\" + dir + "\\*";
	WIN32_FIND_DATAA findData;
	HANDLE findHandle = FindFirstFileA(fullPath.c_str(), &findData);
	if (findHandle == INVALID_HANDLE_VALUE)
	{
		return;
	}

	std::string rootDirectory = dir;
	if (!rootDirectory.empty())
	{
		rootDirectory += "\\";
	}

	while (true)
	{
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			std::string directoryName = findData.cFileName;
			if (directoryName != "." && directoryName != "..")
			{
				std::string nextDirectory = rootDirectory + directoryName;
				IntervalGetFilesRecursive(path, nextDirectory, files);
			}
		}
		else
		{
			files.emplace_back(rootDirectory + findData.cFileName);
		}

		bool result = FindNextFileA(findHandle, &findData);
		if (!result)
		{
			break;
		}
	}
}
