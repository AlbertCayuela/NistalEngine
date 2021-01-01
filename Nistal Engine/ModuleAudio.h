#pragma once
#include "Module.h"
#include "Globals.h"
#include "WwiseT.h"

using namespace WwiseT;

class ModuleAudio : public Module
{
public:
	ModuleAudio(Application* app, bool start_enabled = true);
	~ModuleAudio();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	AudioSource* CreateSoundSource(const char* source_name);
	bool SetListener(AudioSource* listener);

protected:

	AudioSource* listener;
	AudioSource* source;
};
