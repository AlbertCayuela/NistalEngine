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
	

public:

	float volume = 0.0f;

	AudioSource* source = nullptr;
};

#endif
