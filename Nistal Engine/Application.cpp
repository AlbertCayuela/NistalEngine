#include "Application.h"
#include "Parson/parson.h"

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	scene_intro = new ModuleSceneIntro(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	ui = new ModuleUI(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	
	// Scenes
	AddModule(scene_intro);
	AddModule(ui);

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	std::list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end())
	{
		delete* item;
		item++;
	}
}

bool Application::Init()
{
	bool ret = true;

	JSON_Value* config_file = nullptr;
	JSON_Object* config = nullptr;
	JSON_Object* config_node = nullptr;

	//config_file = json_parse_file("config.json");

	// Call Init() in all modules
	//std::list<Module*>::iterator item = list_modules.begin();

	if (config_file)
	{
		ret = true;

	}

	//FIX THIS ERRORS:
		//config = json_value_get_object(config_file);
		//app_config = json_object_dotget_object(config, "Application");
		//engine_title = json_object_get_string(app_config, "Engine Name");

		// Call Init() in all modules
	std::list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end() && ret == true)
	{
		ret = (*item)->Init(config_node);
		item++;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.begin();

	while (item != list_modules.end() && ret == true)
	{
		ret = (*item)->Start();
		item++;
	}

	startup_time.Start();

	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	last_FPS = 1.0f / dt;
	last_ms = (float)ms_timer.Read();
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();

	std::list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->PreUpdate(dt);
		item++;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->Update(dt);
		item++;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->PostUpdate(dt);
		item++;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	std::list<Module*>::iterator item = list_modules.end();

	while (item != list_modules.end() && ret == true)
	{
		ret = (*item)->CleanUp();
		item--;
	}

	//TODO1

	return ret;
}

void Application::RequestBrowser(const char* url)
{
	ShellExecute(GetActiveWindow(), "open", url, nullptr, nullptr, SW_NORMAL);
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

float Application::GetMS() 
{
	return last_ms;
}

float Application::GetFPS()
{
	return last_FPS;
}