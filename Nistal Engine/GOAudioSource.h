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
	float SetVolume(float volume);
	bool MuteSound();
	void SwapMusic(float swap_time);
	

public:

	float volume = 50.0f;
	bool muted = false;
	float swap_time = 30.0f;
	uint current_song = 1;

	AudioSource* source = nullptr;
	Timer timer;
};

#endif
