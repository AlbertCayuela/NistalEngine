#include "ResourceMaterial.h"
#include "Application.h"
#include <string>

ResourceMaterial::ResourceMaterial(uint uuid, std::string meta_path, Resource* parent) : Resource(uuid, type)
{
	this->meta_path = meta_path;
	this->parent = parent;

	this->meta_path = this->meta_path.substr(this->meta_path.find_last_of("/\\") + 1);
	std::string::size_type const p(this->meta_path.find_last_of('.'));
	texture_path = this->meta_path.substr(0, p);
	LOG("TEXTUREEEEEEEEEEEEE PATH %s", texture_path.c_str());
	App->importer->TextureSaving(texture_path, "textures/");
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
