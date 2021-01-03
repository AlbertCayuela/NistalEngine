#include "GOReverbZone.h"
#include "Application.h"
#include "GOAudioSource.h"

GOReverbZone::GOReverbZone(GameObject* game_object) : GOComponent(game_object)
{
}

GOReverbZone::~GOReverbZone()
{
}

void GOReverbZone::Update(float dt)
{
	for (std::vector<GOAudioSource*>::iterator i = App->audio->audio_sources.begin(); i != App->audio->audio_sources.end(); i++) 
	{
		if ((*i)->source != nullptr) 
		{
			(*i)->source->ApplyEnvReverb(12, "reverb");
		}
	}
}

