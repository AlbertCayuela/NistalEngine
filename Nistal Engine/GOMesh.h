#ifndef __GOMESH_H__
#define __GOMESH_H__

#include "GOComponent.h"
#include "ModuleLoadFBX.h"

class GOMesh : public GOComponent
{
public:

	GOMesh(GameObject* game_object);
	~GOMesh();

	modelData mesh_info;
};

#endif
