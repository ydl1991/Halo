#pragma once
// \file IOpSys.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <memory>
#include <string>
#include <vector>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class IWindow;
	
	// \Enum IOpSysTextColor 
	// Text Colors 
	enum IOpSysTextColor : uint8_t
	{
		Black = 0,
		Blue,
		Green,
		Cyan,
		Red,
		Magenta,
		Brown,
		LightGrey,
		DarkGrey,
		LightBlue,
		LightGreen,
		LightCyan,
		LightRed,
		LightMagenta,
		Yellow,
		White,
	};

	// \class IOpSys 
	// TODO: Class Purpose 
	class IOpSys
	{
	public:
		using ID = size_t;
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		IOpSys();

		// Default Destructor 
		virtual ~IOpSys();

		// Factory Method
		static std::unique_ptr<IOpSys> Create();

		// Make Folder Request
		bool MakeFolder(const char* path);

		// Interface
		virtual const char* GetSystemName() const = 0;
		virtual std::unique_ptr<IWindow> CreateSystemWindow(const char* name, uint32_t width, uint32_t height) = 0;
		virtual void GetDateTime(std::string& date, std::string& time) = 0;
		virtual void GetFileLastModifiedTime(const char* filePath, std::string& time) = 0;
		virtual void SetConsoleTextColor(halo::IOpSysTextColor color) = 0;
		virtual void SetCurrentWorkingDirectory(const std::string& path) = 0;
		virtual std::vector<std::string> GetAllFiles(const std::string& path) = 0;

		// static 
		static ID GUIDGenerator();
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


	};
}