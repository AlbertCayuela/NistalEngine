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

void GOCamera::Update(float dt)
{
	DrawFrustum();
}

void GOCamera::DrawFrustum()
{
	glBegin(GL_LINES);
	glLineWidth(2.0f);
	glColor4f(1.0f, 0.5f, 0.0f, 1.0f);

	for (uint i = 0; i < frustum.NumEdges(); i++) 
	{
		glVertex3f(frustum.Edge(i).a.x, frustum.Edge(i).a.y, frustum.Edge(i).a.z);
		glVertex3f(frustum.Edge(i).b.x, frustum.Edge(i).b.y, frustum.Edge(i).b.z);
	}

	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void GOCamera::SetFOV(float fov)
{
	float aspect_ratio = frustum.AspectRatio();
	frustum.verticalFov = DEGTORAD * fov;
	SetAspectRatio(aspect_ratio);
}

void GOCamera::SetNearPlane(float near_plane)
{
	if (near_plane >= frustum.farPlaneDistance)
		near_plane = frustum.farPlaneDistance - 1.0f;

	if (near_plane <= 0.0f)
		near_plane = 0.1f;

	frustum.nearPlaneDistance = near_plane;
}

void GOCamera::SetFarPlane(float far_plane)
{
	if (far_plane <= frustum.nearPlaneDistance)
		far_plane = frustum.nearPlaneDistance + 1.0f;

	frustum.farPlaneDistance = far_plane;
}

void GOCamera::SetAspectRatio(float aspect_ratio)
{
	frustum.horizontalFov = 2.0f * atanf(aspect_ratio * tanf(frustum.verticalFov * 0.5f));
}
