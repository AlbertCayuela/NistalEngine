#include "ResourceMaterial.h"
#include <string>

ResourceMaterial::ResourceMaterial(uint uuid, std::string meta_path) : Resource(uuid, type)
{
}

ResourceMaterial::~ResourceMaterial()
{
}

bool ResourceMaterial::LoadToMemory()
{
	return false;
}

bool ResourceMaterial::UnloadFromMemory()
{
	return false;
}
