	#include "Timer.h"

void Timer::updateTicks(LARGE_INTEGER _ticks)
{
	if (!paused)
		counter.QuadPart += (_ticks.QuadPart * scaleFactor);
}

void Timer::updateSeconds(double _secs)
{
	if (!paused)
		counter.QuadPart += Clock::secondsToTicks((_secs * scaleFactor)).QuadPart;
}



void Timer::set(LARGE_INTEGER ticks)
{
	if (!paused)
		counter = ticks;
}

double Timer::getSeconds() const
{
	return Clock::ticksToSeconds(counter);
}


double Timer::calculateDelta(Timer& _other)
{
	LARGE_INTEGER v;
	v.QuadPart = counter.QuadPart - _other.counter.QuadPart;
	return Clock::ticksToSeconds(v);
}