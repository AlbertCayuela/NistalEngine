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
	if (Begin("Assets"), &is_on, flags)
	{
		SetPos();
	}
	End();
}

void UIResources::SetPos()
{
	SetWindowPos(ImVec2((App->window->width / 8.0f) * 6.0f, 18), ImGuiCond_Always);
	SetWindowSize(ImVec2((App->window->width / 8.0f) * 2.0f, (App->window->height / 0.6f) * 4.5f));
	SDL_GetWindowSize(App->window->window, &App->window->width, &App->window->height);
}
