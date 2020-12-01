#ifndef __RESOURCEMESH_H__
#define __RESOURCEMESH_H__

#include "Resource.h"

class ResourceMesh : public Resource
{

public:

	ResourceMesh(uint uuid);
	~ResourceMesh();

	bool LoadToMemory();
	bool UnloadFromMemory();

};

#endif