#include "Application.h"
#include "ModuleSerialization.h"

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
	JSON_Value* json_value = json_value_init_array();
	JSON_Array* json_array = json_value_get_array(json_value);

	SaveGameObjects(json_array);

	std::string extension = ".json";
	std::string final_name = scene_name + extension;

	json_serialize_to_file_pretty(json_value, final_name.c_str());
	return ret;
}

bool ModuleSerialization::SaveGameObjects(JSON_Array* json_array)
{
	for (std::vector<GameObject*>::const_iterator iterator = App->scene_intro->game_objects.begin() + 1; iterator != App->scene_intro->game_objects.end(); iterator++)
	{
		(*iterator)->SaveInfoGameObject((*iterator), json_array);

	}
	return true;
}