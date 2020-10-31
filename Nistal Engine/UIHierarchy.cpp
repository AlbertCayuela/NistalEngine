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

void UIHierarchy::SetHierarchy()
{
}

void UIHierarchy::Draw()
{
	if (Begin("GameObjects Hierarchy")) 
	{

		//for (std::vector<GameObject*>::iterator i = App->scene_intro->game_objects.begin(); i < App->scene_intro->game_objects.end(); ++i) 
		//{
		//	static ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		//	PushID((*i)->name.c_str());
		//	PopID();
		//}
	/*	ImGuiTreeNodeFlags flag = 1;
		flag += ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Leaf;*/
		for (std::vector<GameObject*>::iterator i = App->scene_intro->game_objects.begin(); i < App->scene_intro->game_objects.end(); ++i) 
		{
			if (TreeNode((*i)->name.c_str()))
			{

			}
		}

	}
	End();
}

