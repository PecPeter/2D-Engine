#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "gameState.hpp"
#include "stateHandler.hpp"


class cEngine {
	public:
		cEngine (void);
		~cEngine (void);

		bool init (int screenWidth, int screenHeight, char* winTitle, cStateHandler* stateHandler);
		void quit (void);

		void mainLoop (void);
	private:
		void handleEvents (void);
		void updateState (void);
		void renderState (double timeLag);

		SDL_Window* window_;
		SDL_Renderer* renderer_;
		SDL_Event event_;

		const double MS_PER_UPDATE,
			  MS_PER_RENDER;
		const short MAX_UPDATE_COUNT;

		cStateHandler* stateHandler_;
};

#endif
