#ifndef ENGINEMETRICS_HPP
#define ENGINEMETRICS_HPP

extern double TICK_RATE,
	   FRAME_RATE,
	   MS_PER_UPDATE,
	   MS_PER_RENDER,
	   CALCED_TICK_RATE,
	   CALCED_FRAME_RATE;
extern int SCREEN_WIDTH,
	   SCREEN_HEIGHT,
	   MAX_UPDATE_COUNT;

void setSettings (int screenWidth, int screenHeight, double tickRate,
		double frameRate, double maxUpdateCount);

#endif
