#include <iostream>
#include "Clock.h"
#include "Timer.h"
#include <string>
using namespace std;

void gameTimer(double _fps)
{
	
}
void main()
{
	Clock::init();
	double		prevTime = Clock::getCurrentTime();
	double		currentTime = 0.0f;
	double		framesPerSecond = 0.0f;
	int			seconds = 45;
	int			minutes = 59;
	int			hours = 0;
	string sHours, sMinutes, sSeconds, sTime;
	Timer secsTimer;
	while (true)
	{
		currentTime = Clock::getCurrentTime();
		framesPerSecond = currentTime - prevTime;
		prevTime = currentTime;

		if (framesPerSecond >= 1.0)
		{
			framesPerSecond = 0;
			seconds++;
			if (seconds > 59)
			{
				seconds = 0;
				minutes++;
				if (minutes > 59)
				{
					minutes = 0;
					hours++;
				}
			}
			if (hours < 10)
			{
				sHours = "0";
				sHours.append(to_string(hours));
			}
			else
				sHours = to_string(hours);
			
			if (minutes < 10)
			{
				sMinutes = "0";
				sMinutes.append(to_string(minutes));
			}
			else
				sMinutes = to_string(minutes);
			
			if (seconds < 10)
			{
				sSeconds = "0";
				sSeconds.append(to_string(seconds));
			}
			else
				sSeconds = to_string(seconds);
			
			sTime = sHours + ":" + sMinutes + ":" + sSeconds;
			cout << sTime << endl;
		}
		
	}
	getchar();
}