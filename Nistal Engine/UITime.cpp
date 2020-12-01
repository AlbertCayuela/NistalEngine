#include "Application.h"
#include "Globals.h"
#include "UIWindow.h"
#include "UITime.h"
#include "ModuleUI.h"
#include "ImGui/imgui.h"

using namespace ImGui;

UITime::UITime() : UIWindow()
{
	is_on = true;
}

UITime::~UITime()
{}

bool UITime::Start()
{
	bool ret = true;

	return ret;
}

bool UITime::CleanUp()
{
	bool ret = true;

	return ret;
}

void UITime::Draw()
{
	Begin("Time Management", &is_on, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	SetPos();

	if (Button("Play")) 
	{
		LOG("Playing");
		App->serialization->SaveScene("current_scene");
		App->playing_timer.Start();
		App->scene_intro->playing = true;
		App->scene_intro->paused = false;
		App->renderer3D->using_engine_camera = false;
	}
	
	SameLine();

	if (Button("Stop"))
	{
		LOG("Stopping");
		App->serialization->LoadScene("Library/Scenes/current_scene.json");
		App->playing_timer.Stop();
		App->scene_intro->playing = false;
		App->scene_intro->paused = true;
		App->renderer3D->using_engine_camera = true;
	}

	SameLine();

	if (App->scene_intro->playing) 
	{
		if (Button("Change camera"))
		{
			LOG("Changing camera");
			App->renderer3D->using_engine_camera = !App->renderer3D->using_engine_camera;
		}
	}
	
	SameLine();

	float game_seconds;
	game_seconds = App->playing_timer.Read();

	Text("Game Time: %.2f", game_seconds/1000);

	SameLine();

	float engine_seconds;
	engine_seconds = App->startup_time.Read();

	Text("Application Time: %.2f", engine_seconds/1000);

	//SameLine();

	if (SliderFloat("TimeScale", &time_scale, 0.0f, 2.0f)) 
	{

	}

	End();

}

void UITime::SetPos()
{
	SetWindowPos(ImVec2((App->window->width / 8.0f) * 1.5f, 18.0f), ImGuiCond_Always);
	SetWindowSize(ImVec2((App->window->width / 8.0f) * 4.5f, 60), ImGuiCond_Always);
}
