#pragma once
#include "Module.h"
#include "Globals.h"
#include "WwiseT.h"
#include "GOAudioSource.h"

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

	void PlayAudio(GOAudioSource* audio_source);
	void PauseAudio(GOAudioSource* audio_source);
	void StopAudio(GOAudioSource* audio_source);

protected:

	AudioSource* listener;
	AudioSource* source;
};
