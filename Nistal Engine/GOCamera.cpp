#include "GOCamera.h"
#include "GOTransform.h"
#include "Application.h"

GOCamera::GOCamera(GameObject* parent) : GOComponent(parent)
{
	this->type = GOCOMPONENT_TYPE::CAMERA;
	
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
	if (parent != nullptr) 
	{
		parent->has_camera = false;
		parent->camera = nullptr;
	}

}

void GOCamera::Update(float dt)
{
	if (App->scene_intro->root)
		FrustumCulling(App->scene_intro->root);

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

int GOCamera::ContainsAABB(const AABB& box)
{
	math::float3 vCorner[8];
	int iTotalIn = 0;
	box.GetCornerPoints(vCorner); // get the corners of the box into the vCorner array
									 // test all 8 corners against the 6 sides
									 // if all points are behind 1 specific plane, we are out
									 // if we are in with all points, then we are fully in
	math::Plane m_plane[6];
	frustum.GetPlanes(m_plane); //{ near, far, left, right, top, bottom }.

	for (int p = 0; p < 6; ++p)
	{
		int iInCount = 8;
		int iPtIn = 1;
		for (int i = 0; i < 8; ++i)
		{
			// test this point against the planes

			if (m_plane[p].IsOnPositiveSide(vCorner[i]))
			{
				iPtIn = 0;
				--iInCount;
			}
		}
		// were all the points outside of plane p?
		if (iInCount == 0)
			return(OUTSIDE);
		// check if they were all on the right side of the plane
		iTotalIn += iPtIn;
	}
	// so if iTotalIn is 6, then all are inside the view
	if (iTotalIn == 6)
		return(INSIDE);
	// we must be partly in then otherwise
	return(INTERSECT);
}

void GOCamera::FrustumCulling(GameObject* game_object)
{
	if (!game_object->has_camera)
	{
		for (std::vector<GameObject*>::iterator i = game_object->children.begin(); i < game_object->children.end(); i++)
		{
			AABB box = (*i)->bbox;

			if (box.IsFinite() && (*i)->has_mesh)
			{
				if (ContainsAABB(box) == OUTSIDE)
					(*i)->active = false;
				else
					(*i)->active = true;
			}
			FrustumCulling(*i);
		}

	}
}

float4x4 GOCamera::GetViewMatrix() const
{
	math::float4x4 view_matrix = frustum.ViewMatrix();
	return view_matrix.Transposed();
}

float4x4 GOCamera::GetProjectionMatrix() const
{
	return frustum.ProjectionMatrix().Transposed();
}

void GOCamera::SaveSceneCamera(JSON_Array* componentsObj)
{
	JSON_Value* component = json_value_init_object();
	JSON_Object* componentObj = json_value_get_object(component);

	json_object_set_number(componentObj, "Type:", this->type);
	json_object_set_number(componentObj, "NearDistance", frustum.nearPlaneDistance);
	json_object_set_number(componentObj, "FarDistance", frustum.farPlaneDistance);
	json_object_set_number(componentObj, "FrustumVerticalFOV", frustum.verticalFov);
	json_object_set_number(componentObj, "FrustumHorizontalFOV", frustum.horizontalFov);

	json_array_append_value(componentsObj, component);
}

void GOCamera::LoadSceneCamera(JSON_Object* obj, GameObject* game_object)
{
	game_object->camera->frustum.nearPlaneDistance = json_object_get_number(obj, "NearDistance");
	game_object->camera->frustum.farPlaneDistance = json_object_get_number(obj, "FarDistance");
	game_object->camera->frustum.verticalFov = json_object_get_number(obj, "FrustumVerticalFOV");
	game_object->camera->frustum.horizontalFov = json_object_get_number(obj, "FrustumHorizontalFOV");
	game_object->transform->NewPosition(game_object->transform->position);
}
