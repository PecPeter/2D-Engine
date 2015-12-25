#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "gameState.hpp"
#include "stateHandler.hpp"
#include "timer.hpp"

const double TICK_RATE = 120;
const double FRAME_RATE = 250;
const double MS_PER_UPDATE = (1.0/TICK_RATE)*1000.0;
const double MS_PER_RENDER = (1.0/FRAME_RATE)*1000.0;
const short MAX_UPDATE_COUNT = 10;

class cEngine {
	public:
		cEngine (void);

		bool init (int screenWidth, int screenHeight, const char* winTitle,
				cStateHandler* stateHandler);
		bool init (int screenWidth, int screenHeight, std::string winTitle,
				cStateHandler* stateHandler);
		void quit (void);

		void mainLoop (void);
	private:
		void handleEvents (void);
		void updateState (double tickRate);
		void renderState (double timeLag);

		SDL_Window* window_;
		SDL_Renderer* renderer_;
		SDL_Event event_;

		cStateHandler* stateHandler_;
};

#endif
