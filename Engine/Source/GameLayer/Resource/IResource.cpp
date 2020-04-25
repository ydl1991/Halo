#include "IResource.h"

using halo::IResource;

halo::IResource::IResource(const std::string& filepath, std::vector<std::byte>& data)
	: m_data{ std::move(data) }
	, m_filepath{ filepath }
{
}

IResource::~IResource()
{
	
}