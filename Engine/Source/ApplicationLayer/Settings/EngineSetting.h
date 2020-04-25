#pragma once
// \file EngineSetting.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <unordered_map>
#include <string>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class EngineSetting 
	// TODO: Class Purpose 
	class EngineSetting
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		EngineSetting(std::unordered_map<std::string, std::string>& setting) : m_settings{ std::move(setting) } {};
		~EngineSetting() {};

		// Functions to retrive data 
		const int GetInt(std::string key) { return std::stoi(m_settings[key]); }
		const std::string GetString(std::string key) { return m_settings[key]; }
		const bool GetBool(std::string key) { return std::stoi(m_settings[key]); }

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		std::unordered_map<std::string, std::string> m_settings;
	};
}