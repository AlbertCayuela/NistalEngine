#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleUI.h"
#include "ModuleLoadFBX.h"
#include "ModuleFS.h"
#include "ModuleImporter.h"
#include "ModuleSerialization.h"
#include "ModuleResourceManager.h"
#include <list>

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleUI* ui;
	ModuleLoadFBX* load_fbx;
	ModuleFS* file_system;
	ModuleImporter* importer;
	ModuleSerialization* serialization;
	ModuleResourceManager* resource_manager;

	std::string engine_title;

	JSON_Value* config_file = nullptr;
	JSON_Object* config = nullptr;
	JSON_Object* config_node = nullptr;

	Timer startup_time;

	uint total_frames = 0;
	Timer playing_timer;
	float time_scale = 1.0f;
	float mydt;
	float newdt = 0.0f;

private:

	Timer	ms_timer;

	float dt;
	float last_FPS = 0.0f;
	float last_ms = 0.0f;
	std::list<Module*> list_modules;

	bool showConfig = false;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	void RequestBrowser(const char* url);
	float GetMS();
	float GetFPS();

	void TimeManager();
	float GetDT() const;

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};
extern Application* App;