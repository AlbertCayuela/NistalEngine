#include "Application.h"
#include "Globals.h"
#include "UIInspector.h"
#include "UIWindow.h"
#include "GameObject.h"
#include "GOTransform.h"
#include "GOMesh.h"
#include "GOMaterial.h"
#include "ModuleSceneIntro.h"

#include "ImGui/imconfig.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"
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
		//mesh_exists = false;
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
		if (CollapsingHeader("Transform"))
		{
			/*static float col1[3] = { 1.0f, 0.0f, 0.2f };
			static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
			ImGui::ColorEdit3("color 1", col1);
			ImGui::ColorEdit4("color 2", col2);	*/

			Text("Game Object name: %s", GO->name.c_str());
			Separator();

			Text("Position:"); SameLine();
			static float position[4] = { GO->transform->position.x , GO->transform->position.y, GO->transform->position.z };
			InputFloat3("", position);

			Text("Rotation:"); SameLine();
			static float rotation[4] = { GO->transform->rotation.x, GO->transform->rotation.y, GO->transform->rotation.z };
			InputFloat3("", rotation);

			Text("Scale:"); SameLine();
			static float scale[4] = { GO->transform->scale.x, GO->transform->scale.y, GO->transform->scale.z };
			InputFloat3("", scale);

			static int world = 0;
			RadioButton("world", &world, 2); ImGui::SameLine();
			static int local = 0;
			RadioButton("local", &local, 2);
		}
		if (CollapsingHeader("Geometry Mesh"))
		{
			if (App->scene_intro->selected_go != nullptr) 
			{
				if (Checkbox("Active", &App->scene_intro->selected_go->active)) {}
			}
			//show normals
			if (App->scene_intro->selected_go != nullptr) 
			{
				if (Checkbox("Normals: Vertex", &App->ui->render_vertex_normals))
				{
					/*for (std::vector<modelData>::iterator i = App->load_fbx->meshes.begin(); i != App->load_fbx->meshes.end(); ++i)
					{
						App->load_fbx->DrawVertexNormals(*i);
					}*/
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
				if (Checkbox("Active", &App->scene_intro->selected_go->has_material)) {}
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
			if(App->scene_intro->selected_go!=nullptr)
				Image((ImTextureID)GO->material->texture_id, ImVec2(100.0f, 100.0f), uv_min, uv_max, tint_col, border_col);

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
