#include "GOAudioSource.h"
#include "Application.h"

using namespace WwiseT;

GOAudioSource::GOAudioSource(GameObject* parent) : GOComponent(parent)
{
	source = App->audio->CreateSoundSource("MyAudioSource");
	PlayEvent("PlaySong1");

	App->audio->audio_sources.push_back(this);

	timer.Start();
}

GOAudioSource::~GOAudioSource()
{
}

void GOAudioSource::Update(float dt)
{
	SwapMusic(swap_time);
}

void GOAudioSource::PlayEvent(const char* event_name)
{
	current_event = event_name;
	source->PlayEventByName(event_name);
}

void GOAudioSource::PlayASound(const char* event_name)
{
	if (current_event.c_str() != nullptr)
	{
		source->StopEventByName(current_event.c_str());
	}
	PlayEvent(event_name);
}

void GOAudioSource::PauseASound(const char* event_name)
{
	if (current_event.c_str() != nullptr) 
	{
		source->StopEventByName(event_name);
		LOG("Pausing event %s", event_name);
	}
	else 
	{
		LOG("Couldn't pause the event, current event is nullptr");
	}
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
	PlayEvent(play_event);
}
