#ifndef UTILFUNC_HPP
#define UTILFUNC_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

void initEnvironment (void) {
	if (SDL_WasInit(0) == 0)
		SDL_Init(SDL_INIT_EVERYTHING);
	if (TTF_WasInit() == 0)
		TTF_Init();
	SDL_Window* window = SDL_CreateWindow("Test Environment",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			640,480,SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
}

#endif
