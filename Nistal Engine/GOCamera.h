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
	void SetFOV(float fov);
	void SetNearPlane(float near_plane);
	void SetFarPlane(float far_plane);
	void SetAspectRatio(float aspect_ratio);

public:

	math::Frustum frustum;
	float aspect_ratio = 0.0f;

};

#endif
