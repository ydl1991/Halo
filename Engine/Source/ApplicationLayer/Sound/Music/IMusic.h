#pragma once
// \file IMusic.h 
// TODO: File Purpose 
// Created by Dali Yi

#include "..\..\..\GameLayer\Resource\IResource.h"

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class IMusic 
	// TODO: Class Purpose 
	class IMusic
		: public IResource
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		IMusic(IResource* pResource);

		// Default Destructor 
		virtual ~IMusic();


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
		virtual void* GetNativeMusic() const = 0;

	};
}