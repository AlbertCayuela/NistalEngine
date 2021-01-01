#ifndef __GOAUDIOSOURCE_H__
#define __GOAUDIOSOURCE_H__

#include "GOComponent.h"
#include "WwiseT.h"

using namespace WwiseT;

class GOAudioSource : public GOComponent 
{
public:

	GOAudioSource(GameObject* parent);
	~GOAudioSource();

	void Update(float dt);
	float SetVolume(float volume);
	bool MuteSound();
	

public:

	float volume = 50.0f;
	bool muted = false;

	AudioSource* source = nullptr;
};

#endif
