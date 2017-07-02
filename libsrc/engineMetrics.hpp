#ifndef ENGINEMETRICS_HPP
#define ENGINEMETRICS_HPP

#include <stdexcept>
#include <exception>
#include <string>

extern double TICK_RATE,
	   MS_PER_UPDATE,
	   CALCED_TICK_RATE,
	   CALCED_FRAME_RATE;
extern int SCREEN_WIDTH,
	   SCREEN_HEIGHT,
	   MAX_UPDATE_COUNT;

extern int RENDER_SETTINGS;
const int RENDER_FPS = 1;	// 01
const int RENDER_TPS = 2;	// 10

void setSettings (double tickRate, double maxUpdateCount);

void toggleRenderSettings (int toggledSetting);

#endif
