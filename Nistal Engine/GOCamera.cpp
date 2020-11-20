#include "GOCamera.h"
#include "Application.h"

GOCamera::GOCamera(GameObject* parent) : GOComponent(parent)
{
	aspect_ratio = 1.7778f;

	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 1.0f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = DEGTORAD * 60;
	frustum.horizontalFov = 2.0f * atanf(aspect_ratio * tanf(frustum.verticalFov * 0.5f));
}

GOCamera::~GOCamera()
{
}

void GOCamera::DrawFrustum()
{
}
