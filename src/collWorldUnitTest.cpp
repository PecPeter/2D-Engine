#include "collWorldUnitTest.hpp"

void collWorldUnitTest (void) {
	std::cout << "Testing collWorld constructor:\n";
	cGenBroadphase broadphase;
	cCollWorld world(&broadphase);
	cCollDebugDrawer drawer;
	world.setDebugDraw(&drawer);
	std::cout << "Testing createObject (cVector2, cCollShape&):\n";
	cCollAabb shape(2,10),
			  shape2(10,2);
	cVector2 pos1(20,20),
			 pos2(20,25),
			 pos3(0,0);
	cCollObj* obj1 = world.createObject(pos1,shape),
		*obj2 = world.createObject(pos2,shape2),
		*obj3 = world.createObject(pos3,shape);
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
