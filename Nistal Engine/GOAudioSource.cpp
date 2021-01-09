#include "GOAudioSource.h"
#include "Application.h"
#include "GOTransform.h"

using namespace WwiseT;

GOAudioSource::GOAudioSource(GameObject* parent) : GOComponent(parent)
{
	this->type = GOCOMPONENT_TYPE::AUDIO_SOURCE;

	source = App->audio->CreateSoundSource("MyAudioSource");

	App->audio->audio_sources.push_back(this);

	timer.Start();
}

GOAudioSource::~GOAudioSource()
{
}

void GOAudioSource::Update(float dt)
{
	if(is_music)
		SwapMusic(swap_time);

	AudioSourcePosition();
}

bool GOAudioSource::AudioSourcePosition()
{  
	bool ret;

	if (parent != nullptr) 
	{
		math::Quat rotation = parent->transform->rotation;
		math::float3 position = parent->transform->position;
		math::float3 front = rotation.Transform(math::float3(0, 0, 1));
		math::float3 up = rotation.Transform(math::float3(0, 1, 0));

		source->SetSourcePos(-position.x, position.y, -position.z, front.x, front.y, front.z, up.x, up.y, up.z);

		ret = true;
	}
	else
	{
		ret = false;
	}

	return ret;
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

void GOAudioSource::SaveSceneAudioSource(JSON_Array* componentsObj)
{
	JSON_Value* component = json_value_init_object();
	JSON_Object* componentObj = json_value_get_object(component);

	json_object_set_number(componentObj, "Type:", this->type);
	json_object_set_number(componentObj, "Volume", volume);
	json_object_set_boolean(componentObj, "Muted", muted);
	json_object_set_boolean(componentObj, "IsMusic", is_music);
	json_object_set_number(componentObj, "SwapTime", swap_time);

	json_array_append_value(componentsObj, component);

}

void GOAudioSource::LoadSceneAudioSource(JSON_Object* componentsObj, GameObject* go)
{
	App->scene_intro->sound_go = nullptr;
	App->scene_intro->moving_sound_go = nullptr;
	go->audio_source->volume = json_object_get_number(componentsObj, "Volume");
	go->audio_source->muted = json_object_get_boolean(componentsObj, "Muted");
	go->audio_source->is_music = json_object_get_boolean(componentsObj, "IsMusic");
	go->audio_source->swap_time = json_object_get_number(componentsObj, "SwapTime");
}
