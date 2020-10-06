#pragma once
#include "Module.h"
#include "Globals.h"
#include "UIWindow.h"
#include "ImGui/imgui.h"

class UIWindow;
class UIConfiguration;
class UIAbout;
class UIConsole;

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
	std::vector<UIWindow*> ui_windows;
	ImGuiTextBuffer debug_console_buff;

private:

	UIConfiguration* ui_configuration = nullptr;
	UIAbout* ui_about = nullptr;
	UIConsole* ui_console = nullptr;

};