#include "Log.h"

// ------------------------ //
//		Import Files        //
// ------------------------ //
// System
#include <iostream>
#include <stdarg.h>
#include <iomanip>
#include <string>
#include <chrono>
#include <sstream>
//#include <Windows.h>
#include <unordered_map>
// Engine
#include <ApplicationLayer/Settings/EngineSetting.h>

using halo::Log;

const char* Log::s_categoryNames[halo::LogCategory::NumCategory] = {

	"One_Time",							// -- Log Only Once
	"System",							// -- Log System Message
	"Display",							// -- Log Normal Message
	"Resources",						// -- Log Resource Message
	"Lua",								// -- Log Lua Message
	"Warning",							// -- Log Warning
	"Error",							// -- Log Error
	"Fatal",							// -- Log Fatal Message (Will Lead To Crash)
};

const char* Log::s_folderNames[halo::LogCategory::NumCategory] = {

	"OneTime_Log/",						// -- fileName for One-time logs
	"System_Log/",						// -- fileName for System logs
	"Display_Log/",						// -- fileName for Normal Message logs 
	"Resource_Log/",					// -- fileName for Resource Message
	"Lua_Log/",							// -- fileName for Lua Message
	"Warning_Log/",						// -- fileName for Warning
	"Error_Log/",						// -- fileName for Error
	"Fatal_Log/",						// -- fileName for Fatal Message (Will Lead To Crash)
};

const char* Log::s_emergencyLevel[halo::LogLevel::Total] = {

	"Normal",							// -- Emergency Level 1
	"Urgent",							// -- Emergency Level 2
	"Critical",							// -- Emergency Level 3
};

halo::IOpSysTextColor Log::s_logColors[halo::LogCategory::NumCategory] = {
	
	halo::IOpSysTextColor::LightGrey,	// -- Color For Log Once Message
	halo::IOpSysTextColor::LightCyan,	// -- Color For System Message
	halo::IOpSysTextColor::White,		// -- Color For Normal Message
	halo::IOpSysTextColor::LightGreen,	// -- Color For Resource Related Message
	halo::IOpSysTextColor::Green,		// -- Color For Lua Related Message	
	halo::IOpSysTextColor::Yellow,		// -- Color For Warning Message
	halo::IOpSysTextColor::Red,			// -- Color For Errow Message
	halo::IOpSysTextColor::LightRed		// -- Color For Fatal Message
};


Log::Log()
	: m_messageBuffer{}
	, m_isUsingLog{ true }
	, m_securityLevel{ halo::LogLevel::Level2 }
	, m_pOpSys{ nullptr }
{
	InitBanList();
}

Log::~Log()
{
	m_pOpSys = nullptr;
}

// ------------------------------- //
//	Get singleton Logger instance
//-------------------------------- //
Log* halo::Log::GetInstance()
{
	static Log log;
	return &log;
}

// ------------------------------- //
//		Initialize Logger
//-------------------------------- //
bool halo::Log::Initialize(halo::IOpSys* pSystem, const std::shared_ptr<halo::EngineSetting>& pSettings)
{
	// Assign Operating System 
	m_pOpSys = pSystem;

	// Load and apply log setting
	if (ReadLogSettings(pSettings))
	{
		LOG_SYSTEM("Log Setting Loading Completed.");
	}

	// Create folders if not already did 
	m_pOpSys->MakeFolder(s_logDirectory);

	return true;
}

// ------------------------------- //
//		Open Log file for write
//-------------------------------- //
bool halo::Log::OpenLogFileForWrite(halo::LogCategory category, std::string& date)
{
	// combine the directory and file name
	std::string path = s_logDirectory + std::string(s_folderNames[category]);

	// Make Folder (make folder)
	m_pOpSys->MakeFolder(path.c_str());

	// open file to write
	m_out.open(path + date + ".txt", std::ios::out | std::ios::app);

	if (!m_out.is_open())
	{
		return false;
	}

	return true;
}

// ------------------------------- //
//		Read Log Settings
//-------------------------------- //
bool halo::Log::ReadLogSettings(const std::shared_ptr<halo::EngineSetting>& pSettings)
{
	m_isUsingLog = pSettings->GetBool("isUsingLog");
	m_securityLevel = (halo::LogLevel)(pSettings->GetInt("securityLevel") - 1);

	std::stringstream ss(pSettings->GetString("categoryBanList"));
	int i = 0;
	char c;
	while (ss >> c)
	{
		if (c != ',' && i < halo::NumCategory)
		{
			m_categoryBanList[i] = c - '0';
			++i;
		}
	}

	return true;
}

// ---------------------- //
//	Init Banning List
//----------------------- //
void halo::Log::InitBanList()
{
	for (int i = 0; i < halo::LogCategory::NumCategory; ++i)
	{
		m_categoryBanList[i] = 0;
	}
}

// ------------------------------------------------------------------------------- //
// Arguments order important, format must next to ... and they must be the last two
//-------------------------------------------------------------------------------- //
void halo::Log::Print(halo::LogCategory category, halo::LogLevel level, int line, const char* file, const char* format, ...)
{
	// If logger is currently off, or category is banned, exit
	if (!m_isUsingLog || m_categoryBanList[category])
		return;

	// variadic arguments 
	{
		va_list args;
		va_start(args, format);
		vsprintf_s(m_messageBuffer, format, args);
		va_end(args);
	}

	// Truncate fully-qualified path
	std::string path = file;
	path = path.substr(path.find_last_of('\\') + 1);

	// Get date and time now
	std::string date = "----------", time = "--:--:--";
	if(m_pOpSys)
		m_pOpSys->GetDateTime(date, time);

	// Print out message in specific color
	{
		// Change console color
		if (m_pOpSys)
			m_pOpSys->SetConsoleTextColor(s_logColors[category]);

		std::cout << "[" << date << " " << time << "]" << " [ " << s_emergencyLevel[level] << " ] " << "[ " << s_categoryNames[category] << " ] [ " << path << "(" << line << ") ] - " << m_messageBuffer << std::endl;
	}

	// Check emergency level and open Log file for write if meets security requirement
	if (m_pOpSys && level >= m_securityLevel)
	{
		OpenLogFileForWrite(category, date);

		// write log and close file
		m_out << "[" << date << " " << time << "]" << " [ " << s_emergencyLevel[level] << " ] " << "[ " << s_categoryNames[category] << " ] [ " << path << "(" << line << ") ] - " << m_messageBuffer << std::endl;

		m_out.close();
	}
}

// ---------------------------------------------------------------------------------------------------------- //
//								Code Abandon Area (Might reactivate later)
// ---------------------------------------------------------------------------------------------------------- //

//// ------------------------------- //
////	Open setting file for write
////-------------------------------- //
//bool halo::Log::WriteLogSettings()
//{
//	// combine the directory and file name
//	std::string path = s_settingDirectory + std::string("Settings.txt");
//
//	m_out.open(path, std::ios::out | std::ios::trunc);
//
//	if (m_out.bad())
//	{
//		LOG_ERROR("Failed to open log setting file! Unable to save log settings!");
//		return false;
//	}
//
//	// Collect saving info
//	LogSetting setting;
//	CollectLogSettings(setting);
//
//	// Write the whole data struct in one swoop!
//	m_out.write((char*)&setting, sizeof(setting));
//
//	m_out.close();
//
//	return true;
//}

//// ------------------------------- //
////		Collecting setting data
////-------------------------------- //
//void halo::Log::CollectLogSettings(LogSetting& setting)
//{
//	setting.m_isUsingLog = m_isUsingLog;
//	setting.m_securityLevel = m_securityLevel;
//	std::memcpy(setting.m_categoryBan, m_categoryBan, sizeof(bool) * halo::LogCategory::NumCategory);
//}

//// ------------------------------- //
////		Apply setting data
////-------------------------------- //
//void halo::Log::ParseLogSettings(LogSetting& setting)
//{
//	LOG(halo::LogCategory::Display, halo::Level1, "Loading Log Settings! Current Setting:")
//
//	m_isUsingLog = setting.m_isUsingLog;
//	LOG_DISPLAY("Log Activation: %s", m_isUsingLog ? "True" : "False");
//
//	m_securityLevel = (halo::LogLevel)setting.m_securityLevel;
//	LOG_DISPLAY("Log Security Level: Level %d", m_securityLevel + 1);
//
//	std::memcpy(m_categoryBan, setting.m_categoryBan, sizeof(bool) * halo::LogCategory::NumCategory);
//	LOG_DISPLAY("Log Ban List Updated!");
//}