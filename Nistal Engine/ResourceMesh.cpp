#include "ResourceMesh.h"

ResourceMesh::ResourceMesh(uint uuid, std::string meta_path, Resource* parent) : Resource(uuid, type)
{
	this->meta_path = meta_path;
	LOG("New Resource Mesh with path: %s", this->meta_path.c_str());
}

ResourceMesh::~ResourceMesh()
{
}

bool ResourceMesh::LoadToMemory()
{
	return false;
}

bool ResourceMesh::UnloadFromMemory()
{
	return false;
}
