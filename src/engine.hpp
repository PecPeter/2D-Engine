#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "gameState.hpp"
#include "gameStateHeader.hpp"
#include "gameStateTypes.hpp"

class cEngine {
	public:
		cEngine (void);
		~cEngine (void);

		bool init (int screenWidth, int screenHeight, char* winTitle);
		void quit (void);

		void mainLoop (void);
	private:
		void handleEvents (void);
		void updateState (void);
		void renderState (double timeLag);

		SDL_Window* window_;
		SDL_Renderer* renderer_;
		SDL_Event event_;

		const double MS_PER_UPDATE = (1.f/120.f)*1000.f, //60 updates/s
			  MS_PER_RENDER = (1.f/250.f)*1000.f; 		// Max of 250 FPS
		const short MAX_UPDATE_COUNT = 10;

		std::vector<cGameState*> stateList_;
};

#endif
