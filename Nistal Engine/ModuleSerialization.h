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
	bool SaveGameObjects(JSON_Array* json_array);
};