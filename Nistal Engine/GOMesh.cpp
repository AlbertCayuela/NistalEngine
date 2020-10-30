#include "GOMesh.h"
#include "Application.h"

GOMesh::GOMesh(GameObject* game_object) : GOComponent(game_object)
{
	LOG("Mesh added to gameobject: %s", game_object->name.c_str());
}

GOMesh::~GOMesh()
{
}
