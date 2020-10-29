#include "Application.h"
#include "Globals.h"
#include "UIInspector.h"
#include "UIWindow.h"
#include "ImGui/imconfig.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Glew/include/glew.h"

using namespace ImGui;

UIInspector::UIInspector() : UIWindow()
{
	is_on = false;
}

UIInspector::~UIInspector()
{}

bool UIInspector::Start()
{
	bool ret = true;


	return ret;
}

bool UIInspector::CleanUp()
{
	return true;
}

void UIInspector::Draw()
{
}