#ifndef __GOMATERIAL_H__
#define __GOMATERIAL_H__

#include "GOComponent.h"

class GOMaterial : public GOComponent
{

public:

	GOMaterial(GameObject* game_object, const char* name);
	~GOMaterial();
	void LoadThisTex(const char* texture_path);
	void GetNewMaterial(std::string new_material_path);

	void SaveSceneMaterial(JSON_Array* componentsObj);

	uint texture_id;
	std::string name;

};

#endif
