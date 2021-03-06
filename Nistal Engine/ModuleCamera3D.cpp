#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "GameObject.h"
#include "GOCamera.h"
#include "GOTransform.h"
#include "GOMesh.h"
#include "GOCamera.h"

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
	Move({ 50.0f,50.0f,100.0f });
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

	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) newPos.y += speed;
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

			Quat quatX = Quat::RotateX(dy * sensitivity);
			camera->frustum.up = quat.Mul(camera->frustum.up).Normalized();
			camera->frustum.front = quat.Mul(camera->frustum.front).Normalized();

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

	//MOUSE PICKING
	if (!ImGui::GetIO().WantCaptureMouse) 
	{
		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_LALT) == KEY_IDLE)
		{
			LOG("Mouse Picking");

			

			int mouse_x = App->input->GetMouseX(); //mouse position
			int mouse_y = App->input->GetMouseY();
			float screen_w = App->window->width; // window size
			float screen_h = App->window->height;

			float n_mouse_x = -(1.0f - 2.0f * ((float)mouse_x) / (screen_w)); //normalized mouse positions
			float n_mouse_y = 1.0f - (2.0f * ((float)mouse_y) / (screen_h));

			LOG("mouse x: %i mouse y: %i screen w: %.2f screen h: %.2f norm mouse x: %.2f norm mouse y: %.2f", mouse_x, mouse_y, screen_w, screen_h, n_mouse_x, n_mouse_y);

			LineSegment picking = camera->frustum.UnProjectLineSegment(n_mouse_x, n_mouse_y);

			GameObject* closest_object = nullptr;

			//for (std::vector<GameObject*>::iterator i = App->scene_intro->game_objects.begin(); i != App->scene_intro->game_objects.end(); ++i)
			for(int i=0; i < App->scene_intro->game_objects.size() - 1; ++i)
			{
				//TestAABBIntersection(picking, (*i), intersected_objects); //check intersections and store objects in a map
				TestAABBIntersection(picking, App->scene_intro->game_objects[i], intersected_objects);
			}

			if(!intersected_objects.empty())
				closest_object = intersected_objects.begin()->first;

			if (closest_object != nullptr)
			{
				if (TestTriIntersection(picking, closest_object, intersected_objects))
				{
					App->scene_intro->selected_go = closest_object;
					LOG("Selected GameObject: %s, uuid: %i", closest_object->ui_name.c_str(), closest_object->uuid);
				}
				else 
				{
					App->scene_intro->selected_go = nullptr;
					LOG("No GameObject selected now!");
				}
			}
			else if (closest_object == nullptr)
			{
				App->scene_intro->selected_go = nullptr;
				LOG("No GameObject selected now!");
			}

			DebugPickingRay(picking);
		}
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

void ModuleCamera3D::TestAABBIntersection(LineSegment ray, GameObject* game_object, map<GameObject*, float> &intersected_objects)
{
	if (game_object->bbox.IsFinite() && game_object->has_bbox)
	{
		if (ray.Intersects(game_object->bbox)) 
		{
			float distance;
			distance = game_object->bbox.Distance(ray.a);
			LOG("GameObject: %s intersected, distance: %f", game_object->ui_name.c_str(), distance);
			intersected_objects.insert({ game_object, distance });
			LOG("map size: %i", intersected_objects.size());
		}
	}
}

bool ModuleCamera3D::TestTriIntersection(LineSegment ray, GameObject *& game_object, map<GameObject*, float>& intersected_objects)
{
	bool ret = false;

	modelData mesh_info = modelData();
	GOMesh* mesh = nullptr;
	float min_distance = FLOAT_INF;

	for (map<GameObject*, float>::iterator i = intersected_objects.begin(); i != intersected_objects.end(); ++i)
	{
		Triangle tri;
		LineSegment local_ray = ray;
		local_ray.Transform((i)->first->transform->GlobalMatrix().Inverted());
		mesh = (i)->first->mesh;

		if (mesh != nullptr) 
		{
			mesh_info = mesh->mesh_info;

			for (int j = 0; j < mesh_info.num_index; ++j)
			{

				tri.a = { mesh_info.vertices[mesh_info.indices[j] * 3], mesh_info.vertices[mesh_info.indices[j] * 3 + 1], mesh_info.vertices[mesh_info.indices[j] * 3 + 2] };
				tri.b = { mesh_info.vertices[mesh_info.indices[j] * 3 + 2], mesh_info.vertices[mesh_info.indices[j] * 3 + 3], mesh_info.vertices[mesh_info.indices[j] * 3 + 4] };
				tri.c = { mesh_info.vertices[mesh_info.indices[j] * 3 + 3], mesh_info.vertices[mesh_info.indices[j] * 3 + 4], mesh_info.vertices[mesh_info.indices[j] * 3 + 5] };

				float distance;
				float3 hit_point;

				if (local_ray.Intersects(tri, &distance, &hit_point)) 
				{
					ret = true;

					if (distance < min_distance)
					{
						min_distance = distance;
						game_object = (i)->first;
					}
				}
			}
		}	
	}

	return ret;
}

void ModuleCamera3D::DebugPickingRay(LineSegment ray)
{
	glColor4f(255, 20, 147, 1);

	GLfloat a[3] = { ray.a.x, ray.a.y, ray.a.z };
	GLfloat b[3] = { ray.b.x, ray.b.y, ray.b.z };

	glBegin(GL_LINES);
	glVertex3fv(a);
	glVertex3fv(b);
	glEnd();

	glColor4f(1, 1, 1, 1);
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

GOCamera* ModuleCamera3D::GetCurrentCamera() const
{
	return camera;
}
