#include "GOAudioListener.h"
#include "Application.h"
#include "GOTransform.h"

using namespace WwiseT;

GOAudioListener::GOAudioListener(GameObject* parent) : GOComponent(parent)
{
	this->type = GOCOMPONENT_TYPE::AUDIO_LISTENER;

	listener = App->audio->CreateSoundSource("MyAudioListener");
	App->audio->SetListener(listener);
}

GOAudioListener::~GOAudioListener()
{
}

void GOAudioListener::Update(float dt)
{
	AudioListenerPosition();
}

bool GOAudioListener::AudioListenerPosition()
{
	bool ret;

	if (parent != nullptr)
	{
		math::Quat rotation = parent->transform->rotation;
		math::float3 position = parent->transform->position;
		math::float3 front = rotation.Transform(math::float3(0, 0, 1));
		math::float3 up = rotation.Transform(math::float3(0, 1, 0));

		listener->SetSourcePos(-position.x, position.y, -position.z, front.x, front.y, front.z, up.x, up.y, up.z);

		ret = true;
	}
	else
	{
		ret = false;
	}

	return ret;
}

void GOAudioListener::SaveSceneAudioListener(JSON_Array* componentsObj)
{
	JSON_Value* component = json_value_init_object();
	JSON_Object* componentObj = json_value_get_object(component);
	json_object_set_number(componentObj, "Type:", this->type);
	json_array_append_value(componentsObj, component);
}
