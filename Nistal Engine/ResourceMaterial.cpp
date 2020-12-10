#include "ResourceMaterial.h"

ResourceMaterial::ResourceMaterial(uint uuid) : Resource(uuid, type)
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
