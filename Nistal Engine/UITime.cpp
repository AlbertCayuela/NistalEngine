#include "Application.h"
#include "Globals.h"
#include "UIWindow.h"
#include "UITime.h"
#include "ModuleUI.h"
#include "ImGui/imgui.h"

using namespace ImGui;

UITime::UITime() : UIWindow()
{
	is_on = true;
}

UITime::~UITime()
{}

bool UITime::Start()
{
	bool ret = true;

	return ret;
}

bool UITime::CleanUp()
{
	bool ret = true;

	return ret;
}

void UITime::Draw()
{
	Begin("Time Management", &is_on, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	SetPos();

	End();

}

void UITime::SetPos()
{
	SetWindowPos(ImVec2((App->window->width / 8.0f) * 1.5f, 18.0f), ImGuiCond_Always);
	SetWindowSize(ImVec2((App->window->width / 8.0f) * 4.5f, 60), ImGuiCond_Always);
}
