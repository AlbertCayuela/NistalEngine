#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"

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
{}

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

	SDL_VERSION(&version);
	cpu_cache = SDL_GetCPUCacheLineSize();
	cpu_count = SDL_GetCPUCount();
	ram = SDL_GetSystemRAM() / 1000;

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
	//math::Sphere x({ 0,0,0 }, 4);
	//math::Sphere y({ 0,0,0 }, 7);

	//if (x.Intersects(y))
	//	LOG("BEEP BEEP!!");
	GLint total_memory = 0;
	GLint memory_usage = 0;
	GLint dedicated_memory = 0;
	GLint available_memory = 0;

	//hardaware
	glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &total_memory);
	glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &available_memory);
	glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &dedicated_memory);
	memory_usage = total_memory - available_memory;


	if (BeginMainMenuBar())
	{
		if (BeginMenu("File"))
		{
			if (MenuItem("Exit","Alt+F4"))
			{
				return UPDATE_STOP;
			}
			ImGui::EndMenu();
		}
		if (BeginMenu("View"))
		{
			if (MenuItem("Configuration"))
			{
				//TODO SHOW/HIDE CONFIG PANEL
				show_configuration = !show_configuration;
			}
			if (MenuItem("Console"))
			{
				//TODO SHOW/HIDE CONSOLE PANEL
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

		//show demo window
		if (show_demo)
			ShowDemoWindow(&show_demo);

		//show configuration window
		if (show_configuration)
		{
			if (ImGui::Begin("Configuration"), &show_configuration)
			{
				if (TreeNode("Options"))
				{
					TreePop();
				}

				if (CollapsingHeader("Application"))
				{
					//static char str0[128] = "Nistal Engine";
					InputText("App Name", "Nistal Engine", NULL);
					InputText("Organization", "UPC CITM", NULL);

					if (vector_fps.size() != 100)
					{
						vector_fps.push_back(App->GetFPS());
						vector_ms.push_back(App->GetMS());
					}
					else
					{
						vector_fps.erase(vector_fps.begin());
						vector_fps.push_back(App->GetFPS());

						vector_ms.erase(vector_ms.begin());
						vector_ms.push_back(App->GetMS());
					}

					//Change int to real PC values
					int zero = 0;
					//PROGRESS BAR FPS
				/*	SliderInt("Max FPS", &zero, 0, 100, "0");
					Text("Limit Framerate: %d", zero);

					struct Funcs
					{
						static float Sin(void*, int i) { return sinf(i * 0.1f); }
						static float Saw(void*, int i) { return (i & 1) ? 1.0f : -1.0f; }
					};
					static int func_type = 0, display_count = 70;

					float (*func)(void*, int) = (func_type == 0) ? Funcs::Sin : Funcs::Saw;*/

					//char title_fps[25];
					//title_fps=("Framerate %.1f", vector_fps[vector_fps.size() - 1]);
					Text("Framerate %.1f", vector_fps[vector_fps.size() - 1]);
					PlotHistogram("##framerate", &vector_fps[0], vector_fps.size(), 0, NULL, 0.0f, 100.0f, ImVec2(310, 100));
					Text("Milliseconds %.1f", vector_ms[vector_ms.size() - 1]);
					PlotHistogram("##milliseconds", &vector_ms[0], vector_ms.size(), 0, NULL, 0.0f, 40.0f, ImVec2(310, 100));
					//ImGui::Separator();
					//ImGui::PlotHistogram("Milliseconds", func, 0, display_count, 0, NULL, -1.0f, 1.0f, ImVec2(0, 100));
				}

				if (CollapsingHeader("Window"))
				{
					int values = 1.000;

					Checkbox("Active", &configuration_window);
					Text("Icon: *default*");
					//SliderInt("Brightness", &values, 0, 100, "0");
					if (SliderFloat("Brightness", &App->window->brightness, 0.0f, 1.0f)) 
					{
						int ll = SDL_SetWindowBrightness(App->window->window, App->window->brightness);
						SDL_UpdateWindowSurface(App->window->window);
					}

					SliderInt("Width", &values, 0, 100, "0");
					SliderInt("Height", &values, 0, 100, "0");
					Text("Refresh rate: %d", values);
					SameLine();
					if (Checkbox("Fullscreen", &fullScreen))
						WIN_FULLSCREEN;
					Checkbox("Resizable", &resizable);
					SameLine();
					Checkbox("Borderless", &borderless);
					Checkbox("Full desktop", &fullDesktop);
				}

				if (CollapsingHeader("File System"))
				{
					//hello
				}

				if (CollapsingHeader("Input"))
				{
					//hello
				}

				if (CollapsingHeader("Hardware"))
				{
					Checkbox("Active", &hardwareActive);
					Text("SDL Version: 0");
					Separator();
					Text("CPUs: %d (Cache: %dkb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());
					Text("System RAM: %dGb", SDL_GetSystemRAM());
					if (SDL_HasRDTSC())
						RDTSC = "RDTSC";
					Text("Caps: %s", RDTSC);
					Separator();
					Text("GPU: ");
					Text("Brand: ");
					Text("VRAM Budget: ");
					Text("VRAM Usage: ");
					Text("VRAM Available: ");
					Text("VRAM Reserved: ");
				}

			}
			ImGui::End();
		}

		//show about window
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

		EndMainMenuBar();
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