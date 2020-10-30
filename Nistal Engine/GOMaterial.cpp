#include "GOMaterial.h"
#include "Application.h"

GOMaterial::GOMaterial(GameObject* game_object, const char* name) : GOComponent(game_object)
{
	this->name = name;
	LoadThisTex(name);
}

GOMaterial::~GOMaterial()
{
}

void GOMaterial::LoadThisTex(const char* texture_path)
{
	App->load_fbx->LoadTexture(texture_path);
}

void GOMaterial::GetTexId()
{
	texture_id = App->load_fbx->texture_id;
}
