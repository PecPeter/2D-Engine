#include "engineMetrics.hpp"

double TICK_RATE = 0,
	   FRAME_RATE = 0,
	   MS_PER_UPDATE = 0,
	   MS_PER_RENDER = 0,
	   CALCED_TICK_RATE = 0,
	   CALCED_FRAME_RATE = 0;
int SCREEN_WIDTH = 0,
	SCREEN_HEIGHT = 0,
	MAX_UPDATE_COUNT = 0;

void setSettings (int screenWidth, int screenHeight, double tickRate,
		double frameRate, double maxUpdateCount)
{
	TICK_RATE = tickRate;
	FRAME_RATE = frameRate;
	MAX_UPDATE_COUNT = maxUpdateCount;

	MS_PER_UPDATE = 1000.0/TICK_RATE;
	MS_PER_RENDER = 1000.0/FRAME_RATE;

	SCREEN_WIDTH = screenWidth;
	SCREEN_HEIGHT = screenHeight;
}
