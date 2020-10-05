#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "UIConfiguration.h"

#include "ImGui/imconfig.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Glew/include/glew.h"

#include "SDL/include/SDL.h"
#include "SDL/include/SDL_opengl.h"

#pragma comment (lib, "Glew/lib/glew32.lib")
#ifdef NDEBUG
#pragma comment (lib, "MathGeoLib/libx86/Release/MathGeoLib.lib") 
#else
#pragma comment (lib, "MathGeoLib/libx86/Debug/MathGeoLib.lib") 
#endif

using namespace ImGui;

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ui_windows.push_back(ui_configuration = new UIConfiguration());
}

ModuleUI::~ModuleUI()
{}

bool ModuleUI::Start()
{
	LOG("Setting up the UI");
	bool ret = true;

	glewInit();
	CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();
	StyleColorsDark();

	//SDL_VERSION(&version);
	//cpu_cache = SDL_GetCPUCacheLineSize();
	//cpu_count = SDL_GetCPUCount();
	//ram = SDL_GetSystemRAM() / 1000;

	//ui_windows.push_back(ui_configuration = new UIConfiguration());

	ui_configuration->Start();

	return ret;
}

update_status ModuleUI::PreUpdate(float dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	NewFrame();

	//ImGui::ShowDemoWindow(&show_window);


	return UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{
	//show demo window
	if (show_demo)
		ShowDemoWindow(&show_demo);

	if (BeginMainMenuBar())
	{
		if (BeginMenu("File"))
		{
			if (MenuItem("Exit", "Alt+F4"))
			{
				return UPDATE_STOP;
			}
			ImGui::EndMenu();
		}
		if (BeginMenu("View"))
		{
			if (MenuItem("Console"))
			{
				//TODO SHOW/HIDE CONSOLE PANEL
			}
			if (MenuItem("Configuration"))
			{
				ui_configuration->is_on = !ui_configuration->is_on;
			}
			ImGui::EndMenu();
		}
		if (BeginMenu("Help"))
		{
			if (MenuItem("ImGui Demo"))
			{
				show_demo = !show_demo;
			}
			if (MenuItem("Documentation"))
			{
				App->RequestBrowser("https://github.com/AlbertCayuela/NistalEngine/wiki");
			}
			if (MenuItem("Download latest"))
			{
				App->RequestBrowser("https://github.com/AlbertCayuela/NistalEngine/releases");
			}
			if (MenuItem("Report a bug"))
			{
				App->RequestBrowser("https://github.com/AlbertCayuela/NistalEngine/issues");
			}
			if (MenuItem("About"))
			{
				show_about = !show_about;
			}
			ImGui::EndMenu();
		}

		EndMainMenuBar();
		//show about window
	}

	if (show_about)
	{
		if (Begin("About Nistal Engine"))
		{
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
		}
		ImGui::End();
	}

	for (int i = 0; i < ui_windows.capacity(); i++)
	{
		if (ui_windows[i]->IsActive())
			ui_windows[i]->Draw();
	}


	return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{
	Render();
	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	DestroyContext();

	SDL_GL_DeleteContext(App->renderer3D->context);
	SDL_DestroyWindow(App->window->window);
	SDL_Quit();

	return true;
}