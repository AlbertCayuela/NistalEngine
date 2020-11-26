#include "Application.h"
#include "ModuleSerialization.h"
#include "GOTransform.h"

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

	json_serialize_to_file_pretty(json_value, final_name.c_str());
	return ret;
}

bool ModuleSerialization::LoadScene(string file_name)
{
	bool ret = true;

	new_go = App->scene_intro->CreateSavedGameObject(App->scene_intro->root, "hullo");;

	JSON_Value* component = json_value_init_object();
	JSON_Object* componentObj = json_value_get_object(component);
	
	new_go->uuid = json_object_get_number(componentObj, "UID");
	new_go->transform->position.y = json_object_get_number(componentObj, "PositionY");

	//Before the next lines, save new game objects into new vector<GameObject*> list that I created

	LoadSceneGameObjects();

	return ret;
}

bool ModuleSerialization::SaveGameObjects(JSON_Array* json_array)
{
	for (std::vector<GameObject*>::const_iterator iterator = App->scene_intro->game_objects.begin() + 1; iterator != App->scene_intro->game_objects.end(); iterator++)
	{
		(*iterator)->SaveInfoGameObject((*iterator), json_array);

	}

	//TODO: Save vector list OwnGameObjects
	return true;
}

bool ModuleSerialization::LoadSceneGameObjects()
{
	for (std::vector<GameObject*>::const_iterator iterator = App->scene_intro->saved_scene_game_object.begin(); iterator != App->scene_intro->saved_scene_game_object.end(); iterator++)
	{
		(*iterator)->LoadInfoGameObject((*iterator));
	}

	return true;
}
