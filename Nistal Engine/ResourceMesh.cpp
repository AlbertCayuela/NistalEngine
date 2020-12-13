#include "ResourceMesh.h"
#include "Application.h"

ResourceMesh::ResourceMesh(uint uuid, std::string meta_path, Resource* parent) : Resource(uuid, type)
{
	this->meta_path = meta_path;
	this->parent = parent;
	LOG("New Resource Mesh with path: %s", this->meta_path.c_str());
	App->importer->SaveOwnFormat(model_info, to_string(parent->uuid));
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
