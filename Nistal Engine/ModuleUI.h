#pragma once
#include "Module.h"
#include "Globals.h"
#include "UIWindow.h"
#include "ImGui/imgui.h"

class UIWindow;
class UIConfiguration;
class UIAbout;
class UIConsole;
class UIInspector;
class UIHierarchy;

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

	void ConsoleLog(const char* text);
	void DebugConsole();

	bool show_demo = false;
	bool render_cube_direct_mode = false;
	bool render_cube_vertex = false;
	bool render_cube_indices = false;
	bool render_sphere = false;
	std::vector<UIWindow*> ui_windows;
	ImGuiTextBuffer debug_console_buff;

	bool render_vertex_normals = false;
	bool render_face_normals = false;
	bool render_all_vertex_normals = false;
	bool render_all_face_normals = false;


	bool render_texture = false;

private:

	UIConfiguration* ui_configuration = nullptr;
	UIAbout* ui_about = nullptr;
	UIConsole* ui_console = nullptr;
	UIInspector* ui_inspector = nullptr;
	UIHierarchy* ui_hierarchy = nullptr;
	

	JSON_Object* UI_node = nullptr;

};