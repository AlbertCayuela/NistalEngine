#include "Application.h"
#include "Globals.h"
#include "UIWindow.h"
#include "ImGui/imconfig.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Glew/include/glew.h"
#include "UIConsole.h"
#include "ModuleUI.h"

using namespace ImGui;

UIConsole::UIConsole() : UIWindow()
{
	is_on = false;
}

UIConsole::~UIConsole()
{}

bool UIConsole::Start()
{
	bool ret = true;

	return ret;
}

bool UIConsole::CleanUp()
{
	bool ret = true;

	return ret;
}

void UIConsole::Draw()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	Begin("Console", &is_on, flags);

	SetPos();

	App->ui->DebugConsole();

	End();
}


void UIConsole::SetPos()
{
	SetWindowPos(ImVec2(0, (App->window->height / 6.0f) * 4.6f), ImGuiCond_Always);
	SetWindowSize(ImVec2(App->window->width, (App->window->height / 6.0f) * 1.4f), ImGuiCond_Always);
	SDL_GetWindowSize(App->window->window, &App->window->width, &App->window->height);
	
}
