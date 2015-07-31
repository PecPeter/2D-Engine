#include "collWorldUnitTest.hpp"

void collWorldUnitTest (void) {
	std::cout << "Testing collWorld constructor:\n";
	cGenBroadphase broadphase;
	cCollWorld world(&broadphase);
	std::cout << "Testing createObject (cVector2, cCollShape&):\n";
	cCollAabb shape(2,2);
	cVector2 pos1(0,0),
			 pos2(2,0),
			 pos3(1,0),
			 pos4(0.5,0.5);
	cCollObj* obj1 = world.createObject(pos1,shape),
		*obj2 = world.createObject(pos2,shape),
		*obj3 = world.createObject(pos3,shape),
		*obj4 = world.createObject(pos4,shape);
	world.checkColls();
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("TEST",SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
	world.drawDebugWorld(renderer);
	SDL_RenderPresent(renderer);
}
