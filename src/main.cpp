#include <iostream>

#include "engine.hpp"

int main (void) {
	cEngine engine;
	const int SCREEN_WIDTH = 640,
		  SCREEN_HEIGHT = 480;
	char title[] = "TIK-TAK-TOE";

	if (engine.init (SCREEN_WIDTH,SCREEN_HEIGHT,title) == false) {
		std::cerr << "Could not initialize engine properly. Now exiting." << std::endl;
		return 1;
	}
	engine.mainLoop();
	engine.quit();
	return 0;
}
