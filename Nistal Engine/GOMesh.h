#ifndef __GOMESH_H__
#define __GOMESH_H__

#include "GOComponent.h"
#include "ModuleLoadFBX.h"

class GOMesh : public GOComponent
{
public:

	GOMesh(GameObject* game_object, const char* name);
	~GOMesh();
	void DrawMesh(uint texture_id = NULL);
	void SetMesh(const char* path);

	void SaveSceneMesh(JSON_Array* componentsObj, GameObject* game_object);

	modelData mesh_info;

	std::string name;
};

#endif
