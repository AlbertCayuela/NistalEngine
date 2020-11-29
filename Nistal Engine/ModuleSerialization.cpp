#include "Application.h"
#include "ModuleSerialization.h"
#include "GOTransform.h"
#include "GOMesh.h"

ModuleSerialization::ModuleSerialization(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleSerialization::~ModuleSerialization()
{}

update_status ModuleSerialization::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleSerialization::SaveScene(const char* scene_name)
{
	bool ret = false;
	json_value = json_value_init_array();
	json_array = json_value_get_array(json_value);

	SaveGameObjects(json_array);

	std::string extension = ".json";
	std::string final_name = scene_name + extension;
	std::string path = LIBRARY_SCENE_FOLDER + final_name;

	LOG("Saving scene %s in %s", final_name.c_str(), path.c_str());

	json_serialize_to_file_pretty(json_value, path.c_str());
	return ret;
}

bool ModuleSerialization::LoadScene(const char* name_scene)
{

	App->scene_intro->root->DeleteGameObjects();

	JSON_Value* scene = json_parse_file(name_scene);
	JSON_Array* Array = json_value_get_array(scene);
	JSON_Object* obj = nullptr;

	App->scene_intro->root = App->scene_intro->CreateGameObject(nullptr, "root");

	int size = json_array_get_count(Array);

	for (uint i = 0; i < size; i++)
	{
		obj = json_array_get_object(Array, i);
		GameObject* new_go = App->scene_intro->CreateGameObject(App->scene_intro->root, nullptr);	
		new_go->LoadInfoGameObject(new_go, obj);
	}

	for (std::vector<GameObject* >::iterator i = App->scene_intro->game_objects.begin(); i != App->scene_intro->game_objects.end(); i++) 
	{
		SetChildren((*i));
		if ((*i)->name.compare("root") == false)
			App->scene_intro->root = (*i);
	}

	return true;
}

bool ModuleSerialization::SaveGameObjects(JSON_Array* json_array)
{
	for (std::vector<GameObject*>::const_iterator iterator = App->scene_intro->game_objects.begin() + 1; iterator != App->scene_intro->game_objects.end(); iterator++)
	{
		(*iterator)->SaveInfoGameObject((*iterator), json_array);
	}
	return true;
}

void ModuleSerialization::SetChildren(GameObject* game_object) const
{
	for (std::vector<GameObject*>::iterator i = App->scene_intro->game_objects.begin() + 1; i != App->scene_intro->game_objects.end(); i++)
	{
		if ((*i)->parent_uuid == 0) 
		{
			(*i)->parent = nullptr;
		}
		else if ((*i)->parent_uuid == game_object->uuid)
		{
			(*i)->parent = game_object;
			game_object->children.push_back((*i));
		}
	}
}
