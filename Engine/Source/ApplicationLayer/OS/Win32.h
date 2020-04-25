#pragma once
// \file Win32.h 
// TODO: File Purpose 
// Created by Dali Yi

#include ".\IOpSys.h"

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class Win32 
	// TODO: Class Purpose 
	class Win32 final : public IOpSys
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		Win32();

		// Default Destructor 
		~Win32();

		// Inherited via IOpSys
		const char* GetSystemName() const final override;
		std::unique_ptr<IWindow> CreateSystemWindow(const char* name, uint32_t width, uint32_t height) final override;
		void GetDateTime(std::string& date, std::string& time) final override;
		void GetFileLastModifiedTime(const char* filePath, std::string& time) final override;
		void SetConsoleTextColor(halo::IOpSysTextColor color) final override;
		void SetCurrentWorkingDirectory(const std::string& path) final override;
		std::vector<std::string> GetAllFiles(const std::string& path) final override;
	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //
		void IntervalGetFilesRecursive(const std::string& path, const std::string& dir, std::vector<std::string>& files);

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //


	};
}