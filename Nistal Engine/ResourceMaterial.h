#ifndef __RESOURCEMATERIAL_H__
#define __RESOURCEMATERIAL_H__

#include "Resource.h"

class ResourceMaterial : public Resource 
{
	
public:

	ResourceMaterial(uint uuid);
	~ResourceMaterial();

	bool LoadToMemory();
	bool UnloadFromMemory();

};

#endif