// ----------------------------------------------------
// Timer.cpp
// Body for CPU Tick Timer class
// ----------------------------------------------------

#include "Timer.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

// ---------------------------------------------
Timer::Timer()
{
	//Start();
}

// ---------------------------------------------
void Timer::Start()
{
	running = true;
	started_at = SDL_GetTicks();
}

// ---------------------------------------------
void Timer::Stop()
{
	running = false;
	stopped_at = SDL_GetTicks();
}

// ---------------------------------------------
Uint32 Timer::Read()
{
	if(running == true)
	{
		return SDL_GetTicks() - started_at;
	}
	else
	{
		return stopped_at - started_at;
	}
}

void Timer::UpdateTimer()
{
	frame_count++;
	real_dt = App->GetDT();
	//realTimeSinceStartup += realTimeDeltaTime;

	if (App->scene_intro->playing == false) {
		time = 0.0f;
	}
	else if (App->scene_intro->playing == true && App->playing_timer.paused == false) {
		time += real_dt * time_scale;
		dt = real_dt * time_scale;
	}

	if (App->playing_timer.paused == true)
	{
		time = time;
	}
}


