#include "collDebugDrawerUnitTest.hpp"

void collDebugDrawerUnitTest (void) {
	if (SDL_WasInit(0) == 0)
		SDL_Init(SDL_INIT_EVERYTHING);
	if (TTF_WasInit() == 0)
		TTF_Init();
	SDL_Window* window = SDL_CreateWindow("TEST",SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);

	cCollDebugDrawer draw;
	cGenBroadphase broadphase;
	cCollWorld world(&broadphase);
	cCollPoint point;
	cCollLine line(cVector2(0.250,4.0));
	cCollTri tri(5,10,16,2,3,-4);
	cCollAabb aabb(10,5);
	//Add a poly shape
	cCollCircle circle(10);
	cVector2 pos1(10,10),
			 pos2(20,20),
			 pos3(30,30),
			 pos4(40,40),
			 pos5(50,50),
			 pos6(60,60);
	cCollObj* obj1 = world.createObject(pos1,point),
		*obj2 = world.createObject(pos2,line,eObjType::DYNAMIC),
		*obj3 = world.createObject(pos3,tri,eObjType::DYNAMIC),
		*obj4 = world.createObject(pos4,aabb,eObjType::DYNAMIC),
//		*obj5 = world.createObject(pos5,poly,eObjType::DYNAMIC),
		*obj6 = world.createObject(pos6,circle,eObjType::DYNAMIC);
	world.setDebugDraw(&draw);
	world.drawDebugWorld(renderer);
	SDL_RenderPresent(renderer);
}
