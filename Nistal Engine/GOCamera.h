#ifndef __GOCAMERA_H__
#define __GOCAMERA_H__

#include "GOComponent.h"
#include "Globals.h"
#include "MathGeoLib/include/Geometry/Frustum.h"

class GameObject;

enum Intersection {
	INSIDE = 0,
	INTERSECT = 1,
	OUTSIDE = 2
};

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

	int ContainsAABB(const AABB& box);
	void FrustumCulling(GameObject* game_object);

	float4x4 GetViewMatrix() const;
	float4x4 GetProjectionMatrix() const;

public:

	math::Frustum frustum;
	float aspect_ratio = 0.0f;

};

#endif
