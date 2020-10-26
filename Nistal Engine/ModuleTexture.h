#pragma once

#include "Module.h"
#include "Globals.h"

#include "Glew/include/glew.h"

class ModuleTexture : public Module
{
public:

	ModuleTexture(Application* app, bool start_enabled = true);
	~ModuleTexture();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void DrawTexture();
	bool LoadTexture(modelData model, const char* path);

public:
	JSON_Object* texture_node = nullptr;
	const char* texture_path = nullptr;

};