#ifndef __GOAUDIOLISTENER_H__
#define __GOAUDIOLISTENER_H__

#include "GOComponent.h"
#include "WwiseT.h"

using namespace WwiseT;

class GOAudioListener : public GOComponent
{
public:

	GOAudioListener(GameObject* parent);
	~GOAudioListener();

public:

	AudioSource* listener = nullptr;

};

#endif
