#include "GOAudioSource.h"
#include "Application.h"

using namespace WwiseT;

GOAudioSource::GOAudioSource(GameObject* parent) : GOComponent(parent)
{
	source = App->audio->CreateSoundSource("MyAudioSource");
	source->PlayEventByName("PlaySong2");
}

GOAudioSource::~GOAudioSource()
{
}

void GOAudioSource::Update(float dt)
{
}

float GOAudioSource::SetVolume(float volume)
{
	this->volume = volume;

	source->SetVolume(this->volume);

	return this->volume;
}
