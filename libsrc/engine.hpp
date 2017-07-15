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
#include "timer.hpp"

#include "renderFunctions.hpp"

typedef void (*stateChangeCallback) (int stateChange, cGameState** statePntr,
		void** interStateInfo);

class cEngine {
	public:
		cEngine (void);

		bool init (int screenWidth, int screenHeight,
				const char* winTitle, stateChangeCallback callback,
				cGameState** statePntr);
		bool init (int screenWidth, int screenHeight,
				std::string winTitle, stateChangeCallback callback,
				cGameState** statePntr);
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

		cGameState** statePntr_;
		void** interStateInfo_;
		stateChangeCallback stateChange_;

		// Move these to some debug render state thing
		TTF_Font* debugInfoFont_;
};

#endif
