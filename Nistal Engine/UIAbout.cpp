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

		if (CollapsingHeader("Libraries used:")) 
		{
			Columns(2, NULL);
			Text("Library");
			SameLine();
			NextColumn();
			Text("Version");
			NextColumn();
			if (MenuItem("SDL"))
				if (IsMouseClicked(0))
					//App->RequestBrowser("https://www.libsdl.org/download-2.0.php");
			SameLine();
			NextColumn();
			Text("2.0.4");

			NextColumn();
			if (MenuItem("OpenGL"))
				if (IsMouseClicked(0))
					//App->RequestBrowser("");
			SameLine();
			NextColumn();
			Text("4.6");

			NextColumn();
			if (MenuItem("ImGui"))
				if (IsMouseClicked(1))
					//App->RequestBrowser("https://github.com/ocornut/imgui/releases/tag/v1.72");
			SameLine();
			NextColumn();
			Text("1.72");

			NextColumn();
			if (MenuItem("Glew"))
				if (IsMouseClicked(0))
					//App->RequestBrowser("http://glew.sourceforge.net/");
			SameLine();
			NextColumn();
			Text("2.1.0");

			NextColumn();
			if (MenuItem("MathGeoLib"))
				if (IsMouseClicked(0))
					//App->RequestBrowser("https://github.com/juj/MathGeoLib/releases/tag/v1.5");
			SameLine();
			NextColumn();
			Text("1.5");

			NextColumn();
			if (MenuItem("DevIL"))
				if (IsMouseClicked(1))
					//App->RequestBrowser("https://github.com/ocornut/imgui/releases/tag/v1.72");
					SameLine();
			NextColumn();
			Text("1.8.0");

			NextColumn();
			if (MenuItem("Assimp"))
				if (IsMouseClicked(1))
					//App->RequestBrowser("https://github.com/ocornut/imgui/releases/tag/v1.72");
					SameLine();
			NextColumn();
			Text("");

			NextColumn();;

			Columns(1, NULL);
		}

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