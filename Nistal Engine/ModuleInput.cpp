#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "GOMaterial.h"
#include "ImGUi/imgui_impl_sdl.h"
#include <string>

#define MAX_KEYS 300

ModuleInput::ModuleInput(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	keyboard = new KEY_STATE[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(KEY_STATE) * MAX_MOUSE_BUTTONS);
}

// Destructor
ModuleInput::~ModuleInput()
{
	delete[] keyboard;
}

// Called before render is available
bool ModuleInput::Init(JSON_Object* node)
{

	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate(float dt)
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	
	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

	mouse_x /= SCREEN_SIZE;
	mouse_y /= SCREEN_SIZE;
	mouse_z = 0;

	for(int i = 0; i < 5; ++i)
	{
		if(buttons & SDL_BUTTON(i))
		{
			if(mouse_buttons[i] == KEY_IDLE)
				mouse_buttons[i] = KEY_DOWN;
			else
				mouse_buttons[i] = KEY_REPEAT;
		}
		else
		{
			if(mouse_buttons[i] == KEY_REPEAT || mouse_buttons[i] == KEY_DOWN)
				mouse_buttons[i] = KEY_UP;
			else
				mouse_buttons[i] = KEY_IDLE;
		}
	}

	mouse_x_motion = mouse_y_motion = 0;

	bool quit = false;
	SDL_Event e;

	

	while(SDL_PollEvent(&e))
	{

		ImGui_ImplSDL2_ProcessEvent(&e);

		switch(e.type)
		{
			case SDL_MOUSEWHEEL:
			mouse_z = e.wheel.y;
			break;

			case SDL_MOUSEMOTION:
			mouse_x = e.motion.x / SCREEN_SIZE;
			mouse_y = e.motion.y / SCREEN_SIZE;

			mouse_x_motion = e.motion.xrel / SCREEN_SIZE;
			mouse_y_motion = e.motion.yrel / SCREEN_SIZE;
			break;

			case SDL_DROPFILE:
			//LOG("file dropped on screen!");
			dropped_path = e.drop.file;
			extension = App->file_system->GetExtension(dropped_path);
			if (extension == "fbx" || extension == "FBX")
			{
				LOG("dropped file extension:.fbx");
				if (App->scene_intro->selected_go != nullptr) 
				{
					App->load_fbx->LoadFBX(dropped_path, App->scene_intro->selected_go);
					App->importer->SaveOwnFormat(App->load_fbx->model, "mymesh");
				}
				else 
				{
					App->load_fbx->LoadFBX(dropped_path);
					App->importer->SaveOwnFormat(App->load_fbx->model, "mymesh");
				}
					
			}

			if (extension == "mesh")
			{
				LOG("Loading mesh from library");
				App->importer->loadOwnFormat = true;
				App->importer->LoadOwnFormat("mymesh");
			}

			if (extension == "dds" || extension == "DDS" || extension == "png" || extension == "PNG" || extension == "jpg" || extension == "JPG" || extension == "tga") 
			{
				LOG("dropped a texture file");
				if (App->scene_intro->selected_go != nullptr) 
				{
					App->scene_intro->selected_go->AddComponent(GOCOMPONENT_TYPE::MATERIAL, "texture");
					App->scene_intro->selected_go->material->LoadThisTex(dropped_path);
					//custom format
					App->importer->TextureSaving(dropped_path, "textures/");
				}
				else
				{
					App->load_fbx->LoadTexture(dropped_path);
					App->importer->TextureSaving(dropped_path, "textures/");
				}
			}
			break;

			case SDL_QUIT:
			quit = true;
			break;

			case SDL_WINDOWEVENT:
			{
				if(e.window.event == SDL_WINDOWEVENT_RESIZED)
					App->renderer3D->OnResize(e.window.data1, e.window.data2);
			}
		}
	}

	if(quit == true || keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}