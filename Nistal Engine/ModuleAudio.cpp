#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

using namespace WwiseT;

ModuleAudio::ModuleAudio(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleAudio::~ModuleAudio()
{
	CloseSoundEngine();
}

bool ModuleAudio::Start()
{
	InitSoundEngine();

	LoadBank("Engines3.bnk");

	source = CreateSoundSource("mysource");
	SetListener(source);

	return true;
}

update_status ModuleAudio::Update(float dt)
{
	source->PlayEventByName("PlaySong1");

	ProcessAudio();

	return UPDATE_CONTINUE;
}

bool ModuleAudio::CleanUp()
{
	return true;
}

AudioSource* ModuleAudio::CreateSoundSource(const char* source_name)
{
	AudioSource* new_source = CreateAudSource(source_name);

	return new_source;
}

bool ModuleAudio::SetListener(AudioSource* listener)
{
	bool ret = true;

	this->listener = listener;
	SetDefaultListener(listener->GetID());

	return ret;
}
