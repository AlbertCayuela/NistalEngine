#include "Application.h"
#include "Globals.h"
#include "ModuleSceneIntro.h"
#include "UIResources.h"
#include "UIWindow.h"
#include "ImGui/imgui.h"

using namespace ImGui;

UIResources::UIResources() : UIWindow()
{
	is_on = false;
}

UIResources::~UIResources()
{}

bool UIResources::Start()
{
	bool ret = true;


	return ret;
}

bool UIResources::CleanUp()
{
	return true;
}



void UIResources::Draw()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	if (Begin("Resources"), &is_on, flags)
	{
		SetPos();

		if (CollapsingHeader("Meshes")) 
		{
			for (std::vector<std::string>::iterator i = App->resource_manager->library_mesh_files.begin(); i != App->resource_manager->library_mesh_files.end(); i++) 
			{
				Text((*i).c_str());
			}
		}
		if (CollapsingHeader("Textures")) 
		{
			for (std::vector<std::string>::iterator i = App->resource_manager->library_material_files.begin(); i != App->resource_manager->library_material_files.end(); i++)
			{
				Text((*i).c_str());
			}
		}
	}
	End();
}

void UIResources::SetPos()
{
	SetWindowPos(ImVec2((App->window->width / 8.0f) * 6.0f, 18), ImGuiCond_Always);
	SetWindowSize(ImVec2((App->window->width / 8.0f) * 2.0f, (App->window->height / 0.6f) * 4.5f));
	SDL_GetWindowSize(App->window->window, &App->window->width, &App->window->height);
}
