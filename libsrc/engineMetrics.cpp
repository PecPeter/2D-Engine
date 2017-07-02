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
int RENDER_SETTINGS = 0;

void setSettings (double tickRate, double maxUpdateCount) {
	TICK_RATE = tickRate;
	MAX_UPDATE_COUNT = maxUpdateCount;
	MS_PER_UPDATE = 1000.0/TICK_RATE;
}

void toggleRenderSettings (int toggledSetting) {
	// Check if the toggledSetting is correct
	bool foundSetting = false;
	if (toggledSetting == RENDER_FPS || toggledSetting == RENDER_TPS)
		foundSetting = true;
	if (foundSetting == false) {
		std::string errorString = "toggleRenderSettings: toggledSetting " +
			std::to_string(toggledSetting) + " is not valid";
		throw std::invalid_argument(errorString);
	}
	RENDER_SETTINGS = RENDER_SETTINGS ^ toggledSetting;
}
