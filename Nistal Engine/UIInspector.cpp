#include "Application.h"
#include "Globals.h"
#include "UIInspector.h"
#include "UIWindow.h"
#include "GameObject.h"
#include "GOTransform.h"
#include "GOMesh.h"
#include "GOMaterial.h"
#include "GOCamera.h"
#include "GOAudioSource.h"
#include "GOAudioListener.h"
#include "ModuleSceneIntro.h"

#include "ImGui/imconfig.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/ImGuizmo.h"
#include "Glew/include/glew.h"


using namespace ImGui;

UIInspector::UIInspector() : UIWindow()
{
	is_on = true;
}

UIInspector::~UIInspector()
{}

bool UIInspector::Start()
{
	bool ret = true;


	return ret;
}

bool UIInspector::CleanUp()
{
	return true;
}

void UIInspector::Draw()
{
	if (App->scene_intro->selected_go != nullptr)
	{
		LoadInspectoData(App->scene_intro->selected_go);
		mesh_exists = true;

	}
	else
	{
		LoadInspectoData(App->scene_intro->root);
	}

	
}

void UIInspector::LoadInspectoData(GameObject* GO)
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	if (App->scene_intro->selected_go != nullptr)
		inspector_name = ("Inspector: %s", App->scene_intro->selected_go->ui_name.c_str());
	else
		inspector_name = "Inspector";
	if (Begin(inspector_name, &is_on, flags))
	{
		SetPos();
		
		if (App->scene_intro->selected_go != nullptr)
		{
			Checkbox("Active Texture", &App->scene_intro->selected_go->has_material); SameLine();
			Checkbox("Active Mesh", &App->scene_intro->selected_go->active);
		}

		if (CollapsingHeader("Transform"))
		{
			if (App->scene_intro->selected_go != nullptr) 
			{
				/*static float col1[3] = { 1.0f, 0.0f, 0.2f };
				static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
				ImGui::ColorEdit3("color 1", col1);
				ImGui::ColorEdit4("color 2", col2);	*/

				Text("Game Object name: %s", GO->ui_name.c_str());
				Separator();

				rot = GO->transform->rotation.ToEulerXYZ() * RADTODEG;

				if (DragFloat3("Position", &GO->transform->position[0], 0.1f, 0.0f, 0.0f, "%.3f"))
				{
					GO->transform->NewPosition(GO->transform->position);
					GO->AddBoundingBox();
				}

				if (DragFloat3("Rotation", &rot[0], 0.1f, 0.0f, 0.0f, "%.3f"))
				{
					GO->transform->NewRotation(rot);
					GO->AddBoundingBox();
				}

				if (DragFloat3("Scale", &GO->transform->scale[0], 0.1f, 0.0f, 0.0f, "%.3f"))
				{
					GO->transform->NewScale(GO->transform->scale);
					GO->AddBoundingBox();
				}

				/*static int world = 0;
				RadioButton("world", &world, 2); ImGui::SameLine();
				static int local = 0;
				RadioButton("local", &local, 2);*/

				UseGuizmo(GO);
			}
		}

		if (CollapsingHeader("Geometry Mesh"))
		{
			if (App->scene_intro->selected_go != nullptr)
			{
				//show normals
				if (Checkbox("Normals: Vertex", &App->ui->render_vertex_normals))
				{
					App->load_fbx->DrawVertexNormals(GO->mesh->mesh_info);
				}

				if (Checkbox("Normals: Face", &App->ui->render_face_normals))
				{
					App->load_fbx->DrawNormals(GO->mesh->mesh_info);
				}
			}

			Separator();

			if (mesh_exists || GO != App->scene_intro->root)
			{
				Text("Number of vertices: %i", GO->mesh->mesh_info.num_vertex);
				Text("Number of indices: %i", GO->mesh->mesh_info.num_index);
				Text("Number of faces: %i", GO->mesh->mesh_info.num_vertex / 3);
				Text("Number of normals: %i", App->load_fbx->model.num_normals);
				Text("Number of UVs: %i", GO->mesh->mesh_info.num_uvs);
			}
		}
		if (CollapsingHeader("Texture"))
		{
			if (App->scene_intro->selected_go != nullptr)
			{
				Text("Path: %s", App->load_fbx->texture_path);
				Separator();
				Text("Width: %ipx", App->load_fbx->texture_width);
				Text("Height: %ipx", App->load_fbx->texture_height);
			}

			Separator();

			//SHOW 2D TEXTURE
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImVec2 uv_min = ImVec2(1.0f, 1.0f);                 // Top-left
			ImVec2 uv_max = ImVec2(0.0f, 0.0f);                 // Lower-right
			ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
			ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
			if (App->scene_intro->selected_go != nullptr)
				Image((ImTextureID)GO->material->texture_id, ImVec2(100.0f, 100.0f), uv_min, uv_max, tint_col, border_col);
		}
		if (GO->has_camera)
		{
			if (CollapsingHeader("Camera")) 
			{
				Checkbox("Use this camera", &App->ui->use_camera);
				float near_plane = GO->camera->frustum.nearPlaneDistance;
				float far_plane = GO->camera->frustum.farPlaneDistance;
				float fov = GO->camera->frustum.verticalFov * RADTODEG;
				if (SliderFloat("Near Plane", &near_plane, 0.1f, far_plane))
				{
					GO->camera->SetNearPlane(near_plane);
				}

				if (SliderFloat("Far Plane", &far_plane, 1.0f, 1000.0f))
				{
					GO->camera->SetFarPlane(far_plane);
				}

				if (SliderFloat("Field of view (FOV)", &fov, 1.0f, 179.0f))
				{
					GO->camera->SetFOV(fov);
				}
			}		
		}
		if (GO->has_audio_source)
		{
			if (CollapsingHeader("Audio Source")) 
			{
				float volume = GO->audio_source->volume;
				float swap_secs = GO->audio_source->swap_time;
				if (SliderFloat("Volume", &volume, 0.0f, 100.0f)) 
				{
					GO->audio_source->SetVolume(volume);
				}
				if (Checkbox("Mute", &GO->audio_source->muted)) 
				{
					GO->audio_source->MuteSound();
				}
				if (SliderFloat("Time to swap songs", &swap_secs, 2.0f, 35.0f))
				{
					GO->audio_source->swap_time = swap_secs;
				}
			}
		}

	}
	End();
}

void UIInspector::SetPos()
{
	SetWindowPos(ImVec2((App->window->width / 8.0f) * 6.0f, 18), ImGuiCond_Always);
	SetWindowSize(ImVec2((App->window->width / 8.0f) * 2.0f, (App->window->height / 0.6f) * 4.5f));
	SDL_GetWindowSize(App->window->window, &App->window->width, &App->window->height);
}

void UIInspector::UseGuizmo(GameObject* selected_go)
{
	ImGuizmo::Enable(true);

	static ImGuizmo::OPERATION operation(ImGuizmo::TRANSLATE);
	static ImGuizmo::MODE mode(ImGuizmo::WORLD);

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		operation = ImGuizmo::TRANSLATE;

	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
		operation = ImGuizmo::ROTATE;

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
		operation = ImGuizmo::SCALE;

	if (RadioButton("Translate", operation == ImGuizmo::TRANSLATE))
		operation = ImGuizmo::TRANSLATE;

	SameLine();

	if (RadioButton("Rotate", operation == ImGuizmo::ROTATE))
		operation = ImGuizmo::ROTATE;

	SameLine();

	if (RadioButton("Scale", operation == ImGuizmo::SCALE))
		operation = ImGuizmo::SCALE;

	ImGuiIO& io = GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
	float4x4 mat = selected_go->transform->GlobalMatrix().Transposed();
	ImGuizmo::Manipulate(App->camera->camera->GetViewMatrix().ptr(), App->camera->camera->GetProjectionMatrix().ptr(), operation, mode, mat.ptr());

	if (ImGuizmo::IsUsing()) 
	{
		mat = mat.Transposed();
		selected_go->transform->NewMatrix(mat);
		selected_go->AddBoundingBox();
	}

}
