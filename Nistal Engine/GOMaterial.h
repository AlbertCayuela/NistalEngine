#ifndef __GOMATERIAL_H__
#define __GOMATERIAL_H__

#include "GOComponent.h"

class GOMaterial : public GOComponent
{

public:

	GOMaterial(GameObject* game_object, const char* name);
	~GOMaterial();
	void LoadThisTex(const char* texture_path);

	uint texture_id;
	std::string name;

};

#endif
