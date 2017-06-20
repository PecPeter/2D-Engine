#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_framerate.h>

#include "mathLib/mathVector.hpp" // maybe get rid of this when making some debug info state thing...

#include "engineMetrics.hpp"
#include "gameState.hpp"
#include "stateHandler.hpp"
#include "timer.hpp"

#include "renderFunctions.hpp"

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

		int  screenWidth_,
			 screenHeight_;
		SDL_Window* window_;
		SDL_Renderer* renderer_;
		SDL_Event event_;

		cStateHandler* stateHandler_;

		// Move these to some debug render state thing
		TTF_Font* debugInfoFont_;
};

#endif
