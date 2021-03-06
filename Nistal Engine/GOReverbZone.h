#ifndef __GOREVERBZONE_H__
#define __GOREVERBZONE_H__

#include "GOComponent.h"
#include "GameObject.h"
#include <DirectXMath.h>

class GOReverbZone : public GOComponent 
{
public:

	GOReverbZone(GameObject* game_object);
	~GOReverbZone();

	void Update(float dt);
	bool CheckIntersection(GOAudioSource* source);
	void ZoneSphere();
	void DrawZone();
	void NewRadius(float new_radius);

	void SaveSceneReverbZone(JSON_Array* componentsObj);

public:
	
	math::Sphere reverb_sphere;
	math::AABB box;

	float reverb_radius = 5.0f;
};

#endif
