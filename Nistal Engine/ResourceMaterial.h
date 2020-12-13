#ifndef __RESOURCEMATERIAL_H__
#define __RESOURCEMATERIAL_H__

#include "Resource.h"
#include <string>

class ResourceMaterial : public Resource 
{
	
public:

	ResourceMaterial(uint uuid, std::string meta_path, Resource* parent);
	~ResourceMaterial();

	bool LoadToMemory();
	bool UnloadFromMemory();

};

#endif