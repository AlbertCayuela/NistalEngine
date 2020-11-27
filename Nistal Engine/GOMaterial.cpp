#include "GOMaterial.h"
#include "Application.h"

GOMaterial::GOMaterial(GameObject* game_object, const char* name) : GOComponent(game_object)
{
	this->name = name;
	this->type = GOCOMPONENT_TYPE::MATERIAL;
}

GOMaterial::~GOMaterial()
{
	if (parent != nullptr) 
	{
		parent->has_material = false;
		parent->material = nullptr;
	}
}

void GOMaterial::LoadThisTex(const char* texture_path)
{
	App->load_fbx->LoadTexture(texture_path);
	texture_id = App->load_fbx->texture_id;
}

void GOMaterial::GetNewMaterial(std::string new_material_path)
{
	std::string dest_folder = "Library/Textures/";

	int p = new_material_path.find_last_of('.');

	if (p <= 15)
	{
		new_material_path = new_material_path.substr(0, p);
	}
	else
	{
		new_material_path = new_material_path.substr(new_material_path.find_last_of("\\") + 1);
		std::string::size_type const j(new_material_path.find_last_of('.'));
		new_material_path = new_material_path.substr(0, j);
	}

	std::string extension = ".dds";
	std::string path = (new_material_path + extension).c_str();
	std::string final_path = (dest_folder + path).c_str();
	LoadThisTex(final_path.c_str());
}

void GOMaterial::SaveSceneMaterial(JSON_Array* componentsObj)
{

	JSON_Value* component = json_value_init_object();
	JSON_Object* componentObj = json_value_get_object(component);

	json_object_set_number(componentObj, "Type:", this->type);
	json_object_set_number(componentObj, "TextureID", texture_id);
	json_object_set_string(componentObj, "TexturePath", this->name.c_str());

	json_array_append_value(componentsObj, component);
}

