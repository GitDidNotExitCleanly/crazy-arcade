#pragma once
#include "SDL.h"
#include "ResourceManager.h"

enum class TimerStatus
{
	TIMER_START,
	TIMER_PAUSE,
	TIMER_STOP
};

class Timer 
{
private:
	TimerStatus timer_status_;
	Uint32 total_time_;
	Uint32 last_time_;
	Uint32 delta_time_;

public:
	Timer();
	~Timer();
	Timer(const Timer &) = delete;
	Timer & operator=(const Timer &) = delete;
	void start();
	void stop();
	void pause();
	void unpause();
	Uint32 getTotalTicks();
	Uint32 getDeltaTicks();
};
