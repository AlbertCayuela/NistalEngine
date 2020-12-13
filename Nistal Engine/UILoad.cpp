#include "Application.h"
#include "Globals.h"
#include "UIWindow.h"
#include "UILoad.h"
#include "ModuleUI.h"
#include "ImGui/imgui.h"

using namespace ImGui;

UILoad::UILoad() : UIWindow()
{
	is_on = false;
}

UILoad::~UILoad()
{}

bool UILoad::Start()
{
	bool ret = true;

	return ret;
}

bool UILoad::CleanUp()
{
	bool ret = true;

	return ret;
}

void UILoad::Draw()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

	Begin("Load Scene", &is_on, flags);

	SetPos();

	if (!files_checked) 
	{
		App->file_system->DiscoverFiles(LIBRARY_SCENE_FOLDER, files_list, dir_list);
		files_checked = true;
	}

	if (CollapsingHeader("Scenes"))
	{
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Selected;
		for (std::vector<std::string>::iterator i = files_list.begin(); i != files_list.end(); i++) 
		{
			if (TreeNodeEx((*i).c_str()))
			{
				if (IsItemHovered())
				{
					if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
					{
						scene_selected = (*i);
						scene_select = true;
					}
				}
				if (scene_selected == (*i))
				{
					if (Button("Selected"))
					{
						scene_selected = nullptr;
						scene_select = false;
						LOG("NO SCENE SELECTED");
					}
				}
				if (scene_selected != (*i))
				{
					if (Button("Select"))
					{
						scene_selected = (*i);
						scene_select = true;
						LOG("SCENE SELECTED: %s", (*i).c_str());
					}
				}

				TreePop();
			}
		}
	}


	if (Button("Load Scene")) 
	{
		if (scene_select) 
		{
			scene_selected = LIBRARY_SCENE_FOLDER + scene_selected;
			App->serialization->LoadScene(scene_selected.c_str());
			is_on = false;
		}	
	}

	End();
}

void UILoad::SetPos()
{
	SetWindowPos(ImVec2(App->window->width / 2 - GetWindowSize().x / 2, (App->window->height / 20.0f) * 4.6f), ImGuiCond_Always);
	SetWindowSize(ImVec2(App->window->width / 4, 250), ImGuiCond_Always);
	SDL_GetWindowSize(App->window->window, &App->window->width, &App->window->height);
}
