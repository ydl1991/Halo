#pragma once
// \file IResource.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <string>
#include <vector>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class IResource 
	// TODO: Class Purpose 
	class IResource
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		IResource(const std::string& filepath, std::vector<std::byte>& data);

		// Default Destructor 
		virtual ~IResource();


	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		std::string m_filepath;
		std::vector<std::byte> m_data;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		std::vector<std::byte>& GetData() { return m_data; }
		const std::string& GetFilepath() const { return m_filepath; }

	};
}