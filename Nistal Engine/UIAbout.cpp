#include "Application.h"
#include "Globals.h"
#include "UIAbout.h"
#include "UIWindow.h"
#include "ImGui/imconfig.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Glew/include/glew.h"

using namespace ImGui;

UIAbout::UIAbout() : UIWindow()
{
	is_on = false;
}

UIAbout::~UIAbout()
{}

bool UIAbout::Start()
{
	bool ret = true;


	return ret;
}

bool UIAbout::CleanUp()
{
	return true;
}

void UIAbout::Draw()
{
	Begin("About Nistal Engine", &is_on);
	
		//TODO ADD LIBRARY VERSIONS
		Separator();

		TextWrapped("Nistal Engine");

		Separator();

		TextWrapped("3D Game Engine");

		Separator();

		TextWrapped("By Albert Cayuela and Nadine Gutierrez");

		Separator();

		TextWrapped("Libraries used:");

		Separator();

		TextWrapped("MIT License Copyright (c) 2020 Albert Cayuela and Nadine"
			"Permission is hereby granted, free of charge, to any person obtaining a copy of this software"
			"and associated documentation files (the 'Software'), to deal in the Software without restriction, including without limitation the rights to use, copy, modify,"
			"merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:");

		NewLine();

		TextWrapped("The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.");

		NewLine();

		TextWrapped("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A"
			"PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,"
			"WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");


	ImGui::End();
}