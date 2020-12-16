#pragma once
#include "Module.h"
#include "Globals.h"


class ModuleAudio : public Module
{
public:
	ModuleAudio(Application* app, bool start_enabled = true);
	~ModuleAudio();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
};
