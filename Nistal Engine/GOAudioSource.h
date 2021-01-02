#ifndef __GOAUDIOSOURCE_H__
#define __GOAUDIOSOURCE_H__

#include "GOComponent.h"
#include "WwiseT.h"
#include "Timer.h"

using namespace WwiseT;

class GOAudioSource : public GOComponent 
{
public:

	GOAudioSource(GameObject* parent);
	~GOAudioSource();

	void Update(float dt);
	void PlayEvent(const char* event_name);
	void PlaySound(const char* event_name);
	float SetVolume(float volume);
	bool MuteSound();
	void SwapMusic(float swap_time);
	void HandleEvents(const char* stop_event, const char* play_event);
	

public:

	float volume = 50.0f;
	bool muted = false;
	float swap_time = 30.0f;
	uint current_song = 1;

	std::string current_event;
	AudioSource* source = nullptr;
	Timer timer;
};

#endif
