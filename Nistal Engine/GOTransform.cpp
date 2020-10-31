#include "GOTransform.h"

GOTransform::GOTransform(GameObject* game_object, const char* name):GOComponent(game_object)
{
	this->name = name;

	position = float3(0.0f, 0.0f, 0.0f);
	rotation = Quat::identity;
	scale = float3(1.0f, 1.0f, 1.0f);
}

GOTransform::~GOTransform()
{
}

void GOTransform::GetGOPosition()
{
	//read original positions
}
