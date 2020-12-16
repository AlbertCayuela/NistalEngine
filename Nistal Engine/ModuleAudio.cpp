#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

ModuleAudio::ModuleAudio(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleAudio::~ModuleAudio()
{
}

bool ModuleAudio::Start()
{
	return true;
}

update_status ModuleAudio::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleAudio::CleanUp()
{
	return true;;
}
