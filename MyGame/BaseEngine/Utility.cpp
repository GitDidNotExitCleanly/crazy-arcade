#include "Utility.h"
#include "SDL.h"

Timer::Timer()
	:timer_status_(TimerStatus::TIMER_STOP),
	total_time_(0),
	last_time_(0),
	delta_time_(0)
{
}

Timer::~Timer()
{
}

void Timer::start()
{
	timer_status_ = TimerStatus::TIMER_START;
	total_time_ = 0;
	last_time_ = SDL_GetTicks();
	delta_time_ = 0;
}

void Timer::stop()
{
	if (timer_status_ == TimerStatus::TIMER_START) {
		timer_status_ = TimerStatus::TIMER_STOP;
		delta_time_ = SDL_GetTicks() - last_time_;
		total_time_ += delta_time_;
		last_time_ = 0;
	}
	else {
		timer_status_ = TimerStatus::TIMER_STOP;
	}
}

void Timer::pause()
{
	if (timer_status_ == TimerStatus::TIMER_START) {
		timer_status_ = TimerStatus::TIMER_PAUSE;
		delta_time_ = SDL_GetTicks() - last_time_;
		total_time_ += delta_time_;
		last_time_ = 0;
	}
}

void Timer::unpause()
{
	if (timer_status_ == TimerStatus::TIMER_PAUSE) {
		timer_status_ = TimerStatus::TIMER_START;
		last_time_ = SDL_GetTicks();
		delta_time_ = 0;
	}
}

Uint32 Timer::getTotalTicks()
{
	Uint32 totalTicks;
	if (timer_status_ == TimerStatus::TIMER_START) {
		totalTicks = SDL_GetTicks() - last_time_ + total_time_;
	}
	else {
		totalTicks = total_time_;
	}
	return totalTicks;
}

Uint32 Timer::getDeltaTicks()
{
	Uint32 deltaTicks;
	if (timer_status_ == TimerStatus::TIMER_START) {
		deltaTicks = SDL_GetTicks() - last_time_ ;
	}
	else {
		deltaTicks = delta_time_;
	}
	return deltaTicks;
}