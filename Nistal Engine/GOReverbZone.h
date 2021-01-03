#ifndef __GOREVERBZONE_H__
#define __GOREVERBZONE_H__

#include "GOComponent.h"

class GOReverbZone : public GOComponent 
{
public:

	GOReverbZone(GameObject* game_object, const char* name);
	~GOReverbZone();
};

#endif
