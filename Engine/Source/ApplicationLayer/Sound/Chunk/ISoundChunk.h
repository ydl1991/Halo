#pragma once
// \file ISoundChunk.h 
// TODO: File Purpose 
// Created by Dali Yi

#include "..\..\..\GameLayer\Resource\IResource.h"

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class ISoundChunk 
	// TODO: Class Purpose 
	class ISoundChunk
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
		ISoundChunk(IResource* pResource);

		// Default Destructor 
		virtual ~ISoundChunk();


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
		virtual void* GetNativeSoundChunk() const = 0;

	};
}