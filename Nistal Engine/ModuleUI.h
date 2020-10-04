#pragma once
#include "Module.h"
#include "Globals.h"

//#include "imgui/imgui.h"
//#include "imgui/examples/imgui_impl_sdl.h"
//#include "imgui/examples/imgui_impl_opengl2.h"

class ModuleUI : public Module
{
public:
	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	bool show_demo = false;
	bool show_configuration = false;
	bool show_about = false;

	char fps_accumulated[100];

	//Configuration Window bool
	bool configuration_window = false;
	bool fullScreen = false;
	bool resizable = false;
	bool borderless = false;
	bool fullDesktop = false;

	//hardware
	bool hardwareActive = false;
	char* RDTSC = nullptr;
	int cpu_cache = 0;
	int cpu_count = 0;
	int ram = 0;
	SDL_version version;

	std::vector<float> vector_ms;
	std::vector<float> vector_fps;

private:
	//UI functions
};