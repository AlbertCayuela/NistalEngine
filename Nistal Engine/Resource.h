#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include "Globals.h"

enum RESOURCE_TYPE {

	RESOURCE_MESH,
	RESOURCE_MATERIAL,
	RESOURCE_UNKNOWN

};

class Resource
{
public:

	Resource(uint uuid, RESOURCE_TYPE type);
	virtual ~Resource();

};

#endif
