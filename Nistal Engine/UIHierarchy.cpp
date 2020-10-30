#include "Application.h"
#include "Globals.h"
#include "UIHierarchy.h"
#include "UIWindow.h"

#include "ImGui/imconfig.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Glew/include/glew.h"

using namespace ImGui;

UIHierarchy::UIHierarchy() : UIWindow()
{
	is_on = false;
}

UIHierarchy::~UIHierarchy()
{}

bool UIHierarchy::Start()
{
	bool ret = true;

	return ret;
}

bool UIHierarchy::CleanUp()
{
	return true;
}

void UIHierarchy::Draw()
{
	if (Begin("Inspector", &is_on, 0))
	{
		if (CollapsingHeader("Transform"))
		{
			/*static float col1[3] = { 1.0f, 0.0f, 0.2f };
			static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
			ImGui::ColorEdit3("color 1", col1);
			ImGui::ColorEdit4("color 2", col2);	*/

			Text("Game Object name: %s", App->load_fbx->new_go->name.c_str());
			Separator();

			Text("Position:"); SameLine();
			static float position[4] = { 0.0f, 0.0f, 0.0f };
			ImGui::InputFloat3("", position);

			Text("Rotation:"); SameLine();
			static float rotation[4] = { 0.0f, 0.0f, 0.0f };
			ImGui::InputFloat3("", rotation);

			Text("Scale:"); SameLine();
			static float scale[4] = { 1.0f, 1.0f, 1.0f };
			ImGui::InputFloat3("", scale);

			static int world = 0;
			ImGui::RadioButton("world", &world, 2); ImGui::SameLine();
			static int local = 0;
			ImGui::RadioButton("local", &local, 2);
		}
		if (CollapsingHeader("Geometry Mesh"))
		{
			//show normals
			if (ImGui::Checkbox("Normals: Vertex", &App->ui->render_vertex_normals))
			{
				/*for (std::vector<modelData>::iterator i = App->load_fbx->meshes.begin(); i != App->load_fbx->meshes.end(); ++i)
				{
					App->load_fbx->DrawVertexNormals(*i);
				}*/
			}

			if (ImGui::Checkbox("Normals: Face", &App->ui->render_face_normals))
			{
				App->load_fbx->DrawNormals(App->load_fbx->model);
			}

			Separator();

			Text("Number of vertices: %i", App->load_fbx->model.num_vertex);
			Text("Number of indices: %i", App->load_fbx->model.num_index);
			Text("Number of faces: %i", App->load_fbx->model.num_vertex / 3);
			//Text("Number of normals: %i", App->load_fbx->model.num_normals);
			Text("Number of UVs: %i", App->load_fbx->model.num_uvs);
		}
		if (CollapsingHeader("Texture"))
		{
			Text("Path: %s", App->load_fbx->texture_path);
			Separator();
			Text("Width: %ipx", App->load_fbx->texture_width);
			Text("Height: %ipx", App->load_fbx->texture_height);

		}

		//LOG("Hellow");
	}
	End();
}