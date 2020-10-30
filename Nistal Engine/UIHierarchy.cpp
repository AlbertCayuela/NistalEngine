#include "Application.h"
#include "Globals.h"
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
}