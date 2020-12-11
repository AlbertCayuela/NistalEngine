#ifndef __RESOURCEMESH_H__
#define __RESOURCEMESH_H__

#include <string>
#include "Resource.h"

class ResourceMesh : public Resource
{

public:

	ResourceMesh(uint uuid, std::string meta_path);
	~ResourceMesh();

	bool LoadToMemory();
	bool UnloadFromMemory();

protected:

	std::string meta_path;

};

#endif