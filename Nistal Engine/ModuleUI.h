#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2DynArray.h"

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

private:
	//UI functions
};