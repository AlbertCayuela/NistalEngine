#include "Application.h"
#include "Globals.h"
#include "UIInspector.h"
#include "UIWindow.h"
#include "ImGui/imconfig.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Glew/include/glew.h"

using namespace ImGui;

UIInspector::UIInspector() : UIWindow()
{
	is_on = false;
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
	if (Begin("Inspector", &is_on, 0))
	{
		if (CollapsingHeader("Transform"))
		{
			/*static float col1[3] = { 1.0f, 0.0f, 0.2f };
			static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
			ImGui::ColorEdit3("color 1", col1);
			ImGui::ColorEdit4("color 2", col2);	*/	

			Text("Game Object name:");
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
			Text("Number of vertices: %i", App->load_fbx->model.num_vertex);
			Text("Number of indices: %i", App->load_fbx->model.num_index);
			Text("Number of faces: %i", App->load_fbx->model.num_vertex / 3);
			//Text("Number of normals: %i", App->load_fbx->model.num_normals);
			Text("Number of UVs: %i", App->load_fbx->model.num_uvs);
		}
		if (CollapsingHeader("Material"))
		{
			//hellow :)
		}

		//LOG("Hellow");
	}
	End();
}