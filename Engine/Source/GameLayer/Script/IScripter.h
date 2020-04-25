#pragma once
// \file IScripter.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <memory>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class IResource;

	// \class IScripter 
	// TODO: Class Purpose 
	class IScripter
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		IScripter();

		// Default Destructor 
		virtual ~IScripter();

		// Functions
		virtual bool Init() = 0;
		virtual bool RunScript(std::shared_ptr<IResource> pResource) = 0;
		virtual bool RunScript(const char* filepath) = 0;

		// Create IGraphics Unique Pointer
		static std::unique_ptr<IScripter> Create();

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