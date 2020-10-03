#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"

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
				//TODO ABOUT TEXT
			}
			ImGui::EndMenu();
		}

		if (ImGui::Begin("Configuration"), &show_configuration)
		{
			show_configuration = !show_configuration;

			if (TreeNode("Options"))
			{
				TreePop();
			}

			if (CollapsingHeader("Application"))
			{
				//static char str0[128] = "Nistal Engine";
				ImGui::InputText("App Name", "Nistal Engine", NULL);
				InputText("Organization", "UPC CITM", NULL);
				//Change int to real PC values
				int zero = 0;
				//PROFRESS BAR FPS
				SliderInt("Max FPS", &zero, 0, 100, "0");
				Text("Limit Framerate: %d", zero);

				struct Funcs
				{
					static float Sin(void*, int i) { return sinf(i * 0.1f); }
					static float Saw(void*, int i) { return (i & 1) ? 1.0f : -1.0f; }
				};
				static int func_type = 0, display_count = 70;

				float (*func)(void*, int) = (func_type == 0) ? Funcs::Sin : Funcs::Saw;
				ImGui::PlotHistogram("", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, ImVec2(0, 80));
				//ImGui::Separator();


			}

			if (CollapsingHeader("Window"))
			{
				//hello
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
				//hello
			}

		}
		ImGui::End();		

		//show demo window
		if (show_demo)
			ShowDemoWindow(&show_demo);

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