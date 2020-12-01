#include "ResourceMesh.h"

ResourceMesh::ResourceMesh(uint uuid) : Resource(uuid, type)
{

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
