#include "GOAudioSource.h"
#include "Application.h"

using namespace WwiseT;

GOAudioSource::GOAudioSource(GameObject* parent) : GOComponent(parent)
{
	source = App->audio->CreateSoundSource("MyAudioSource");
	source->PlayEventByName("PlaySong1");

	timer.Start();
}

GOAudioSource::~GOAudioSource()
{
}

void GOAudioSource::Update(float dt)
{
	SwapMusic(swap_time);
}

float GOAudioSource::SetVolume(float volume)
{
	if (!muted) 
	{
		this->volume = volume;
		source->SetVolume(this->volume);
	}
	
	return this->volume;
}

bool GOAudioSource::MuteSound()
{

	if (muted) 
	{
		source->SetVolume(0.0f);
		return true;
	}
	else if (!muted) 
	{
		source->SetVolume(volume);
		return false;
	}

}

void GOAudioSource::SwapMusic(float swap_time)
{
	if (timer.Read() / 1000 >= swap_time)
	{
		if (current_song == 1) 
		{
			LOG("Swap to song 2");
			HandleEvents("PlaySong1", "PlaySong2");
			current_song = 2;
		}
		else if (current_song == 2)
		{
			LOG("Swap to song 1");
			HandleEvents("PlaySong2", "PlaySong1");
			current_song = 1;
		}

		timer.Start();
	}
}

void GOAudioSource::HandleEvents(const char* stop_event, const char* play_event)
{
	source->StopEventByName(stop_event);
	source->PlayEventByName(play_event);
}
