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
	Begin("Save", &is_on, flags);

	End();
}
