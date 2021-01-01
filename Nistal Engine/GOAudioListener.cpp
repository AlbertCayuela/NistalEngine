#include "GOAudioListener.h"
#include "Application.h"

using namespace WwiseT;

GOAudioListener::GOAudioListener(GameObject* parent) : GOComponent(parent)
{
	listener = App->audio->CreateSoundSource("MyAudioListener");
	SetDefaultListener(listener->GetID());
}

GOAudioListener::~GOAudioListener()
{
}
