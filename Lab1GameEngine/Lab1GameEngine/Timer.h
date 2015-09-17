#ifndef TIMER_H
#define TIMER_H

#include "Clock.h"
class Timer 
{
private:
	LARGE_INTEGER counter;
	double scaleFactor;
	bool paused;
public:

	Timer() : scaleFactor(1.0), paused(false)
	{
		counter.QuadPart = 0L;	
	}

	inline void setPaused(bool _p)
	{
		paused = _p;
	}

	inline bool getPaused()
	{
		return paused;
	}

	inline void setScale(double _s)
	{
		scaleFactor = _s;
	}
	inline double getScale()
	{
		return scaleFactor;
	}

	void updateTicks(LARGE_INTEGER ticks);
	void updateSeconds(double secs);

	void set(LARGE_INTEGER ticks);
	inline LARGE_INTEGER getTicks() const
	{
		return counter;
	}

	double getSeconds() const;


	double calculateDelta(Timer& _other);
};
#endif
