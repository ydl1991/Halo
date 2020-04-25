#pragma once
// \file ITexture.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <GameLayer/Resource/IResource.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class ITexture 
	// TODO: Class Purpose 
	class ITexture : public IResource
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		ITexture(IResource* pResource);

		// Default Destructor 
		virtual ~ITexture();



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
		virtual void* GetNativeTexture() const = 0;
		virtual int GetTextureWidth() const = 0;
		virtual int GetTextureHeight() const = 0;
	};
}