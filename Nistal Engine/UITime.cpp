#include "Application.h"
#include "Globals.h"
#include "UIWindow.h"
#include "UITime.h"
#include "ModuleUI.h"
#include "ImGui/imgui.h"

using namespace ImGui;

UITime::UITime() : UIWindow()
{
	is_on = false;
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
}
