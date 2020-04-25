#pragma once
// \file Log.h 
// TODO: File Purpose 
// Created by Dali Yi

// Logger Macro
#define LOG(category, level, format, ...) { halo::Log::GetInstance()->Print(category, level, __LINE__, __FILE__, format, __VA_ARGS__); }
#define LOG_ERROR(format, ...) { LOG(halo::Error, halo::Level2, format, __VA_ARGS__); }
#define LOG_WARNING(format, ...) { LOG(halo::Warning, halo::Level2, format, __VA_ARGS__); }
#define LOG_FATAL(format, ...) { LOG(halo::Fatal, halo::Level3, format, __VA_ARGS__); }
#define LOG_SYSTEM(format, ...) { LOG(halo::System, halo::Level1, format, __VA_ARGS__); }
#define LOG_DISPLAY(format, ...) { LOG(halo::Display, halo::Level1, format, __VA_ARGS__); }
#define LOG_LUAERROR(format, ...) { LOG(halo::Lua, halo::Level2, format, __VA_ARGS__); }
#define LOG_LUAERROR_A(line, file, format, ...) { halo::Log::GetInstance()->Print(halo::Lua, halo::Level2, line, file, format, __VA_ARGS__); }
#define LOG_LUA(format, ...) { LOG(halo::Lua, halo::Level1, format, __VA_ARGS__); }
#define LOG_LUA_A(line, file, format, ...) { halo::Log::GetInstance()->Print(halo::Lua, halo::Level1, line, file, format, __VA_ARGS__); }

#define DEFINE_USE_LOGGER(command) { halo::Log::GetInstance()->SetLoggerUsage(command); }
#define BAN_LOG_CATEGORY(category) { halo::Log::GetInstance()->BanCategory(category); }
#define UNBAN_LOG_CATEGORY(category) { halo::Log::GetInstance()->UnBanCategory(category); }

// ------------------------ //
//		Import Files        //
// ------------------------ //
// System
#include <fstream>
#include <memory>
// Engine
#include <ApplicationLayer/OS/IOpSys.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \Enum Log Emergency Level 
	enum LogLevel : uint8_t
	{
		Level1 = 0,
		Level2,
		Level3,
		Total,
	};

	// \Enum Log Category 
	enum LogCategory : uint8_t
	{
		// Prints a message to consol Only Once
		Once = 0,

		// Prints a system message to consol
		System,

		// Prints a message to consol
		Display,

		// Prints a message regarding resources
		Resources,

		// Prints a message regarding lua
		Lua,

		// Prints a warning to console.
		Warning,

		// Prints an error to console.
		Error,

		// Always prints a fatal error to console and crashes (even if logging is disabled) 
		Fatal,

		// Total Num Category
		NumCategory,
	};

	class EngineSetting;

	// \class Log 
	// Singleton class that log message to console 
	class Log
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Destructor 
		~Log();
		
		// Static Functions 
		static Log* GetInstance();			// Get Singleton Log Object

		// Initialize Logger 
		bool Initialize(halo::IOpSys* pSystem, const std::shared_ptr<EngineSetting>& pSettings);

		// Log Settings Read and Write 
		bool ReadLogSettings(const std::shared_ptr<EngineSetting>& pSettings);				// Read Log Settings from file

		// Print out logging message with categories 
		void Print(halo::LogCategory categoty, halo::LogLevel level, int line, const char* file, const char* format, ...);

		// Getters 
		bool IsUsingLog() const { return m_isUsingLog; }
		const char* CurrentSecurityLevel() const { return s_emergencyLevel[m_securityLevel]; }
		// Setters 
		void SetLoggerUsage(bool use) { m_isUsingLog = use; }
		void SetSecurityLevel(halo::LogLevel level) { m_securityLevel = level; }
		void BanCategory(halo::LogCategory categoty) { m_categoryBanList[categoty] = true; }
		void UnBanCategory(halo::LogCategory categoty) { m_categoryBanList[categoty] = false; }

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		// Static 
		static constexpr char s_logDirectory[] = "Saved/Logs/";
		static constexpr char s_settingDirectory[] = "Data/LogSetting/";
		static const char* s_categoryNames[halo::LogCategory::NumCategory];
		static const char* s_folderNames[halo::LogCategory::NumCategory];
		static const char* s_emergencyLevel[halo::LogLevel::Total];
		static halo::IOpSysTextColor s_logColors[halo::LogCategory::NumCategory];

		// File writing 
		std::ofstream m_out;
		std::ifstream m_in;

		// System Raw Pointer 
		halo::IOpSys* m_pOpSys;

		// Message Buffer 
		char m_messageBuffer[512];

		// Settings 
		bool m_isUsingLog;
		halo::LogLevel m_securityLevel;
		bool m_categoryBanList[halo::LogCategory::NumCategory];

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		Log();

		// Open/Close Directory 
		bool OpenLogFileForWrite(halo::LogCategory category, std::string& date);

		// Log Setting Functions 
		
		// Get Current Date And Time 
		void InitBanList();

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //

	};
}