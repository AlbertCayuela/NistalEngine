#include "Application.h"
#include "Globals.h"
#include "ModuleSceneIntro.h"
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
	if (Begin("GameObjects Hierarchy")) 
	{
		SetHierarchy(App->scene_intro->root);
	}
	End();
}

void UIHierarchy::SetHierarchy(GameObject* root)
{
	if (root->ui_name == "root")
	{
		for (std::vector<GameObject*>::iterator i = root->children.begin(); i < root->children.end(); ++i)
		{
			SetHierarchy((*i));
		}
	}
	else
	{
		if (TreeNode(root->ui_name.c_str()))
		{
			if (IsItemHovered())
			{
				if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
				{
					LOG("CLICKED! %s", root->ui_name.c_str());
					App->scene_intro->selected_go = root;
				}

			}
			if (Checkbox("Active", &root->active)){}
			SameLine();
			if (Checkbox("Selected", &root->selected)){}
			if (!root->children.empty())
			{
				for (std::vector<GameObject*>::iterator i = root->children.begin(); i < root->children.end(); ++i)
				{
					SetHierarchy((*i));
				}
			}
			TreePop();
		}
	}	
}