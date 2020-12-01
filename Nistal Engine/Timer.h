#ifndef __TIMER_H__
#define __TIMER_H__

#include "Globals.h"
#include "SDL\include\SDL.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	void Stop();
	void UpdateTimer();

	Uint32 Read();

	bool	paused = false;
	float	frame_count;
	float	time_scale = 1.0f;
	float	time;
	float	dt;
	float	real_dt;

private:

	bool	running;
	Uint32	started_at;
	Uint32	stopped_at;
};

#endif //__TIMER_H__