#include "Application.h"
#include "Globals.h"
#include "ModuleSceneIntro.h"
#include "UIAssets.h"
#include "UIWindow.h"
#include "ImGui/imgui.h"

using namespace ImGui;

UIAssets::UIAssets() : UIWindow()
{
	is_on = false;
}

UIAssets::~UIAssets()
{}

bool UIAssets::Start()
{
	bool ret = true;


	return ret;
}

bool UIAssets::CleanUp()
{
	return true;
}



void UIAssets::Draw()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	if (Begin("Assets"), &is_on, flags)
	{
		SetPos();

		if (CollapsingHeader("Meshes")) 
		{
			for (std::vector<string>::iterator i = App->resource_manager->mesh_files.begin(); i != App->resource_manager->mesh_files.end(); i++)
			{
				Text((*i).c_str());
			}
		}
		if (CollapsingHeader("Textures"))
		{
			for (std::vector<string>::iterator i = App->resource_manager->material_files.begin(); i != App->resource_manager->material_files.end(); i++)
			{
				Text((*i).c_str());
			}
		}
	}
	End();
}

void UIAssets::SetPos()
{
	SetWindowPos(ImVec2(0.f, 18.f), ImGuiCond_Always);
	SetWindowSize(ImVec2((App->window->width / 8.0f) * 1.5f, (App->window->height / 0.6f) * 4.5f), ImGuiCond_Always);
}
