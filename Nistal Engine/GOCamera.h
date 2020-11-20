#ifndef __GOCAMERA_H__
#define __GOCAMERA_H__

#include "GOComponent.h"
#include "Globals.h"
#include "MathGeoLib/include/Geometry/Frustum.h"

class GOCamera : public GOComponent
{
public:

	GOCamera(GameObject* parent);
	~GOCamera();

	void Update(float dt);

	void DrawFrustum();

public:

	math::Frustum frustum;
	float aspect_ratio = 0.0f;

};

#endif
