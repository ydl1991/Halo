#pragma once
// \file ResourceCache.h 
// TODO: File Purpose 
// Created by Dali Yi

// C++ Library
#include <memory>
#include <unordered_map>
// Engine Library
#include <GameLayer/Resource/IResource.h>
// Log
#include <Utils/Log.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class IGraphics;
	class IAudio;

	// \class ResourceCache 
	// TODO: Class Purpose 
	class ResourceCache
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		static ResourceCache& Get();

		// Takes in interface pointers to each module responsible for loading resources
		bool Init(IGraphics* pGraphics, IAudio* pAudio);
		void CleanUp();

		// acquire a IResource type resource
		std::shared_ptr<IResource> AcquireResource(const char* filepath);

		// acquire a casted sub-class type resource
		template <class ResourceType>
		std::shared_ptr<ResourceType> AcquireResource(const char* filepath);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		std::unordered_map<std::string, std::shared_ptr<IResource>> m_resourceMap;
		IGraphics* m_pGraphics;
		IAudio* m_pAudio;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		ResourceCache();

		// Default Destructor 
		~ResourceCache();

		ResourceCache(const ResourceCache& copy) = delete;
		ResourceCache(ResourceCache&& copy) = delete;
		ResourceCache& operator=(const ResourceCache& copy) = delete;
		ResourceCache& operator=(ResourceCache&& copy) = delete;

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		// use only when you know you have acquired before
		template <class ResourceType>
		std::shared_ptr<ResourceType> AccessExistingResources(const char* filepath);

	};

	template<class ResourceType>
	inline std::shared_ptr<ResourceType> ResourceCache::AcquireResource(const char* filepath)
	{
		auto pResource = AcquireResource(filepath);
		// like dynamic cast for shared pointer
		return std::static_pointer_cast<ResourceType>(pResource);
	}

	template<class ResourceType>
	inline std::shared_ptr<ResourceType> ResourceCache::AccessExistingResources(const char* filepath)
	{
		auto pResource = m_resourceMap.find(filepath);
		if (pResource == m_resourceMap.end())
		{
			LOG_ERROR("Resource has not been loaded before!");
			return nullptr;
		}

		return std::static_pointer_cast<ResourceType>(pResource->second);
	}
}