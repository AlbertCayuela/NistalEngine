#pragma once
#include "Application.h"
#include "Module.h"
#include "Globals.h"

class ModuleSerialization : public Module
{
public:
	ModuleSerialization(Application* app, bool start_enabled = true);
	~ModuleSerialization();

	update_status Update(float dt);

	bool SaveScene(const char* name_scene);
	bool LoadScene(string file_name);
	bool SaveGameObjects(JSON_Array* json_array);
	bool LoadSceneGameObjects();

	GameObject* new_go = nullptr;
	JSON_Value* json_value = nullptr;
	JSON_Array* json_array = nullptr;
};