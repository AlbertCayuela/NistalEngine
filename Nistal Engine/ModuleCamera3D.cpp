#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "GameObject.h"
#include "GOCamera.h"
#include "GOTransform.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//CalculateViewMatrix();

	//X = vec3(1.0f, 0.0f, 0.0f);
	//Y = vec3(0.0f, 1.0f, 0.0f);
	//Z = vec3(0.0f, 0.0f, 1.0f);

	//Position = vec3(0.0f, 0.0f, 5.0f);
	//Reference = vec3(0.0f, 0.0f, 0.0f);

	camera = new GOCamera(nullptr);
	camera->SetNearPlane(0.1f);
	camera->SetFarPlane(1000.0f);
	Move({ 5.0f,5.0f,5.0f });
	LookAt({ 0.0f,0.0f,0.0f });

}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!

	float3 newPos(0,0,0);
	float speed = 4.0f * dt;
	float sensitivity = 0.25f * dt;

	if(App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 8.0f * dt;

	if(App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) newPos.y += speed;
	if(App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) newPos.y -= speed;

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) newPos += camera->frustum.front * speed;
	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) newPos -= camera->frustum.front * speed;

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) newPos -= camera->frustum.WorldRight() * speed;
	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) newPos += camera->frustum.WorldRight() * speed;

	Move(newPos);

	// Mouse motion ----------------

	if(App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{
		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		if(dx != 0)
		{
			Quat quat = Quat::RotateY(dx * sensitivity);

			camera->frustum.up = quat.Mul(camera->frustum.up).Normalized();
			camera->frustum.front = quat.Mul(camera->frustum.front).Normalized();
		}

		if(dy != 0)
		{
			Quat quat = Quat::RotateAxisAngle(camera->frustum.WorldRight(), dy * sensitivity);
			float3 up = quat.Mul(camera->frustum.up).Normalized();

			if(up.y < 0.0f)
			{
				camera->frustum.up = up;
				camera->frustum.front = quat.Mul(camera->frustum.front).Normalized();
			}
		}
	}

	//CAMERA ZOOM
	if (App->input->GetMouseZ())
	{
		newPos += camera->frustum.front * App->input->GetMouseZ();
		Move(newPos);
	}

	//FOCUS CAMERA ON OBJECT WHEN PRESSING F
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) 
	{
		if (App->scene_intro->selected_go != nullptr)
			FocusOnTarget(App->scene_intro->selected_go->transform->position, 7.0f);
		else if (App->scene_intro->selected_go == nullptr)
			FocusOnTarget(float3(0.0f, 0.0f, 0.0f), 7.0f);
	}

	//ROTATE AROUND OBJECT
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT)
	{
		RotateAroundTarget();
	}

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const float3 &Position, const float3 &Reference, bool RotateAroundReference)
{
	camera->frustum.pos = Position;
	LookAt(Reference);
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt(const float3& Spot)
{
	math::float3 Z = -(camera->frustum.pos - Spot).Normalized();
	math::float3 X = math::Cross(math::float3(0.0f, 1.0f, 0.0f), Z).Normalized();
	math::float3 Y = math::Cross(Z, X);

	camera->frustum.front = Z;
	camera->frustum.up = Y;
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const float3 &Movement)
{
	camera->frustum.Translate(Movement);
}

void ModuleCamera3D::FocusOnTarget(const float3& focus, const float& distance)
{
		float3 direction = camera->frustum.pos - focus;
		camera->frustum.pos = direction.Normalized() * distance;
		LookAt(focus);
}

void ModuleCamera3D::RotateAroundTarget()
{
	float sensitivity = 0.25f;
	int dx = -App->input->GetMouseXMotion();
	int dy = -App->input->GetMouseYMotion();

	if (dx != 0)
	{
		Quat quat = Quat::RotateY(dx * sensitivity);
		camera->frustum.up = quat.Mul(camera->frustum.up).Normalized();
		camera->frustum.front = quat.Mul(camera->frustum.front).Normalized();
	}
	if (dy != 0)
	{
		Quat quat = Quat::RotateAxisAngle(camera->frustum.WorldRight(), dy * sensitivity);
		float3 up = quat.Mul(camera->frustum.up).Normalized();
	}
}
