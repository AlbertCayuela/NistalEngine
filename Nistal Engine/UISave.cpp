#include "Application.h"
#include "Globals.h"
#include "UIWindow.h"
#include "UISave.h"
#include "ModuleUI.h"
#include "ImGui/imgui.h"

using namespace ImGui;

UISave::UISave() : UIWindow()
{
	is_on = false;
}

UISave::~UISave()
{}

bool UISave::Start()
{
	bool ret = true;

	return ret;
}

bool UISave::CleanUp()
{
	bool ret = true;

	return ret;
}

void UISave::Draw()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

	if (Begin("Save Scene", &is_on, flags)) 
	{
		SetPos();
		static char name[30] = "Scene Name";
		InputText("Scene Name", name, ARRAYSIZE(name));
		if(Button("Save"))
		{

		}
	}

	End();
}

void UISave::SetPos()
{
	SetWindowPos(ImVec2(App->window->width/2 - GetWindowSize().x /2, (App->window->height / 20.0f) * 4.6f), ImGuiCond_Always);
	SetWindowSize(ImVec2(App->window->width/4, 100), ImGuiCond_Always);
	SDL_GetWindowSize(App->window->window, &App->window->width, &App->window->height);
}
