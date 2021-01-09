#ifndef __GOAUDIOLISTENER_H__
#define __GOAUDIOLISTENER_H__

#include "GOComponent.h"
#include "WwiseT.h"
#include "MathGeoLib/include/Geometry/Polyhedron.h"

using namespace WwiseT;

class GOAudioListener : public GOComponent
{
public:

	GOAudioListener(GameObject* parent);
	~GOAudioListener();

	void Update(float dt);
	bool AudioListenerPosition();

	void SaveSceneAudioListener(JSON_Array* componentsObj);

public:

	AudioSource* listener = nullptr;

};

#endif
