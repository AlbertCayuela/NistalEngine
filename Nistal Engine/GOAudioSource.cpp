#include "GOAudioSource.h"
#include "Application.h"

using namespace WwiseT;

GOAudioSource::GOAudioSource(GameObject* parent) : GOComponent(parent)
{
	source = App->audio->CreateSoundSource("MyAudioSource");
	source->PlayEventByName("PlaySong1");
}

GOAudioSource::~GOAudioSource()
{
}

void GOAudioSource::Update(float dt)
{
}
