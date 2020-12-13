#ifndef __RESOURCEMESH_H__
#define __RESOURCEMESH_H__

#include <string>
#include "Resource.h"
#include "ModuleLoadFBX.h"

class ResourceMesh : public Resource
{

public:

	ResourceMesh(uint uuid, std::string meta_path, Resource* parent);
	~ResourceMesh();

	bool LoadToMemory();
	bool UnloadFromMemory();

public:

	Resource* parent;
	std::string meta_path;
	modelData model_info;

};

#endif