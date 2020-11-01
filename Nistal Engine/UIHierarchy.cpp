#include "Application.h"
#include "Globals.h"
#include "ModuleSceneIntro.h"
#include "UIHierarchy.h"
#include "UIWindow.h"
#include "ImGui/imgui.h"

using namespace ImGui;

UIHierarchy::UIHierarchy() : UIWindow()
{
	is_on = true;
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
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	if (Begin("GameObjects Hierarchy"), &is_on, flags) 
	{
		SetPos();
		SetHierarchy(App->scene_intro->root);
	}
	End();
}

void UIHierarchy::SetHierarchy(GameObject* root)
{
	if (root->ui_name == "root")
	{
		counter = 0;
		for (std::vector<GameObject*>::iterator i = root->children.begin(); i < root->children.end(); ++i)
		{
			counter++;
			SetHierarchy((*i));
		}
	}
	else
	{
		if (TreeNodeEx((root->ui_name + '_' + std::to_string(counter)).c_str()))
		{
			if (IsItemHovered())
			{
				if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
				{
					App->scene_intro->selected_go = root;
				}
			}
			if (App->scene_intro->selected_go == root)
			{
				if (Button("Selected"))
				{
					App->scene_intro->selected_go = root;
					LOG("GO SELECTED: %s", App->scene_intro->selected_go->ui_name.c_str());
				}
			}
			if (App->scene_intro->selected_go != root) 
			{
				if (Button("Select"))
				{
					App->scene_intro->selected_go = root;
					LOG("GO SELECTED: %s", App->scene_intro->selected_go->ui_name.c_str());
				}
			}
			if (!root->children.empty())
			{
				for (std::vector<GameObject*>::iterator i = root->children.begin(); i < root->children.end(); ++i)
				{	
					SetHierarchy((*i));
					counter++;
				}
			}
			TreePop();
		}
	}	
}

void UIHierarchy::SetPos()
{
	SetWindowPos(ImVec2(0.f, 18.f), ImGuiCond_Always);
	SetWindowSize(ImVec2((App->window->width / 8.0f) * 1.5f, (App->window->height / 0.6f) * 4.5f), ImGuiCond_Always);
}
