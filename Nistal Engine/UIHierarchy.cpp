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
	if (Begin("GameObjects Hierarchy")) 
	{
		SetHierarchy(App->scene_intro->root);
	}
	End();
}

void UIHierarchy::SetHierarchy(GameObject* root)
{
	if (TreeNode(root->ui_name.c_str()))
	{
		if (IsItemClicked()) 
		{
			LOG("CLICKED! %s", root->ui_name.c_str());
			App->scene_intro->selected_go = root;
		}
		if (Checkbox("Active", &root->active))
		{

		}
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