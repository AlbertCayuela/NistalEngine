#include "GOTransform.h"

GOTransform::GOTransform(GameObject* game_object, const char* name):GOComponent(game_object)
{
	this->name = name;
}

GOTransform::~GOTransform()
{
}
