#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "UIConfiguration.h"
#include "UIAbout.h"
#include "UIConsole.h"

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
	ui_windows.push_back(ui_about = new UIAbout());
	ui_windows.push_back(ui_console = new UIConsole());
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

	ui_configuration->Start();
	ui_about->Start();
	ui_console->Start();

	return ret;
}

update_status ModuleUI::PreUpdate(float dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	NewFrame();
 
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
			if (MenuItem("Load model"))
			{
				App->load_fbx->LoadFBX(App->load_fbx->path);
				App->load_fbx->DrawFBX(App->load_fbx->model);
				App->load_fbx->DrawNormals(App->load_fbx->model);
				//DRAW TEXTURE THROUGH FILE
				App->texture->LoadTexture(App->load_fbx->model, App->texture->texture_path);
				//App->texture->DrawTexture();
			}

			if (MenuItem("Exit", "Alt+F4"))
			{
				return UPDATE_STOP;
			}
			ImGui::EndMenu();
		}
		if (BeginMenu("RenderObject"))
		{
			if (CollapsingHeader("Cubes")) 
			{
				Checkbox("Cube with direct mode", &render_cube_direct_mode); //functionality in sceneintro update
				Checkbox("Cube with vertex", &render_cube_vertex);
				Checkbox("Cube with indices", &render_cube_indices);
			}

			if (CollapsingHeader("Spheres"))
			{
				Checkbox("Sphere", &render_sphere);
			}

			ImGui::EndMenu();
		}
		if (BeginMenu("View"))
		{
			if (CollapsingHeader("Model Properties"))
			{
				Checkbox("Draw normals", &render_normals);
				Checkbox("Draw texture", &render_texture);
			}
			if (MenuItem("Console"))
			{
				ui_console->is_on = !ui_console->is_on;
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
				ui_about->is_on = !ui_about->is_on;
			}
			ImGui::EndMenu();
		}
		EndMainMenuBar();
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

	for (int i = 0; i < ui_windows.capacity(); i++)
	{
		ui_windows[i]->~UIWindow();
	}
	ui_windows.clear();

	SDL_GL_DeleteContext(App->renderer3D->context);
	SDL_DestroyWindow(App->window->window);
	SDL_Quit();

	return true;
}

void ModuleUI::ConsoleLog(const char* text)
{
	debug_console_buff.appendf(text);
}

void ModuleUI::DebugConsole()
{
	BeginChild("Console Log");
	TextUnformatted(debug_console_buff.begin());
	EndChild();
}