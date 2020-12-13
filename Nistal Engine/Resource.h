#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include "Globals.h"

enum RESOURCE_TYPE {

	RESOURCE_MESH,
	RESOURCE_MATERIAL,
	RESOURCE_UNKNOWN

};

class ResourceMesh;
class ResourceMaterial;
class Resource
{
public:

	Resource(uint uuid, RESOURCE_TYPE type);
	virtual ~Resource();

	RESOURCE_TYPE GetResourceType() const;
	uint GetUUID() const;
	bool IsLoadedToMemory() const;
	bool LoadToMemory();
	bool UnloadToMemory();
	uint CountReferences() const;

public:

	uint uuid = 0;
	RESOURCE_TYPE type = RESOURCE_UNKNOWN;
	ResourceMesh* resource_mesh = nullptr;
	ResourceMaterial* resource_material = nullptr;
};

#endif
