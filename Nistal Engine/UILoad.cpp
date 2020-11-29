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
		App->file_system->DiscoverFiles("Library/Scenes/", files_list, dir_list);
		files_checked = true;
	}

	if (Button("Load Scene")) 
	{
		App->serialization->LoadScene("Library/Scenes/testscene.json");
		is_on = false;
	}

	End();
}

void UILoad::SetPos()
{
	SetWindowPos(ImVec2(App->window->width / 2 - GetWindowSize().x / 2, (App->window->height / 20.0f) * 4.6f), ImGuiCond_Always);
	SetWindowSize(ImVec2(App->window->width / 4, 100), ImGuiCond_Always);
	SDL_GetWindowSize(App->window->window, &App->window->width, &App->window->height);
}
