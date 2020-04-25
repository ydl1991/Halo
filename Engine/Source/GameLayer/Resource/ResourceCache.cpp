#include "ResourceCache.h"
// C++
#include <algorithm>
#include <string>
#include <fstream>
// Engine
#include <ApplicationLayer/Graphics/IGraphics.h>
#include <ApplicationLayer/Texture/ITexture.h>
#include <ApplicationLayer/Audio/IAudio.h>
#include <ApplicationLayer/Sound/Chunk/ISoundChunk.h>
#include <ApplicationLayer/Sound/Music/IMusic.h>

using halo::ResourceCache;

ResourceCache::ResourceCache()
	: m_pGraphics{ nullptr }
	, m_pAudio{ nullptr }
{

}

ResourceCache::~ResourceCache()
{

}

ResourceCache& halo::ResourceCache::Get()
{
	// TODO: insert return statement here
	static ResourceCache sResourceCache;
	return sResourceCache;
}

bool halo::ResourceCache::Init(IGraphics* pGraphics, IAudio* pAudio)
{
	m_pGraphics = pGraphics;
	m_pAudio = pAudio;
	return true;
}

void halo::ResourceCache::CleanUp()
{
	m_resourceMap.clear();
}

std::shared_ptr<halo::IResource> halo::ResourceCache::AcquireResource(const char* filepath)
{
	// c:/Hellow/World.txt
	// c:\\Hello\\World/txt
	// c:/HELLOW/WORLD.txt
	// c:\\HelloW\\World.txt
	
	std::string path = filepath;
	std::transform(path.begin(), path.end(), path.begin(), std::tolower);
	std::replace(path.begin(), path.end(), '\\', '/');

	auto resItr = m_resourceMap.find(path);
	if (resItr == m_resourceMap.end())
	{
		// mean read in, in binary form
		std::ifstream inFile(path.c_str(), std::ios_base::binary | std::ios_base::in);
		if (inFile.fail())
		{
			LOG_ERROR("Failed to open file: %s", path.c_str());
			return nullptr;
		}

		// find the size of the file in bytes;
		inFile.seekg(0, std::ios::end);
		std::streampos size = inFile.tellg();
		inFile.seekg(0, std::ios::beg);

		// Read contents into vector of bytes
		std::vector<std::byte> data(static_cast<size_t>(size));
		inFile.read(reinterpret_cast<char*>(data.data()), size);

		inFile.close();

		// Make the resource
		std::string extension = path.substr(path.find_last_of('.') + 1);
		auto pResource = std::make_shared<IResource>(path, data);

		// PNG JPG
		if (extension == "png" || extension == "jpg")
		{
			auto pTexture = m_pGraphics->LoadTexture(pResource.get());
			if (pTexture)
			{
				LOG_DISPLAY("Successfully loaded texture!");
			}
			resItr = m_resourceMap.emplace(path, pTexture).first;
		}
		// MP3
		else if (extension == "mp3")
		{
			auto pMusic = m_pAudio->LoadMusic(pResource.get());
			if (pMusic)
			{
				LOG_DISPLAY("Successfully loaded music!");
			}
			resItr = m_resourceMap.emplace(path, pMusic).first;
		}
		// WAV OGG 
		else if (extension == "ogg" || extension == "wav")
		{
			auto pSoundChunk = m_pAudio->LoadSoundChunk(pResource.get());
			if (pSoundChunk)
			{
				LOG_DISPLAY("Successfully loaded sound chunk!");
			}
			resItr = m_resourceMap.emplace(path, pSoundChunk).first;
		}
	}

	return resItr->second;
}