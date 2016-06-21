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

	std::shared_ptr<cCollDebugDrawer> draw = std::make_shared<cCollDebugDrawer>();
	std::shared_ptr<cGenBroadphase> broadphase = std::make_shared<cGenBroadphase>();
	cCollWorld world(broadphase);
	std::shared_ptr<cCollPoint> point = std::make_shared<cCollPoint>();
	std::shared_ptr<cCollLine> line = std::make_shared<cCollLine>(cVector2(0.250,4.0));
	std::shared_ptr<cCollTri> tri = std::make_shared<cCollTri>(5,10,16,2,3,-4);
	std::shared_ptr<cCollAabb> aabb = std::make_shared<cCollAabb>(10,5);
	//Add a poly shape
	std::shared_ptr<cCollCircle> circle = std::make_shared<cCollCircle>(10);
	cVector2 pos1(10,10),
			 pos2(20,20),
			 pos3(30,30),
			 pos4(40,40),
			 pos5(50,50),
			 pos6(60,60);
	std::shared_ptr<cCollObj> obj1 = world.createObject(pos1,point),
		obj2 = world.createObject(pos2,line,eObjType::DYNAMIC),
		obj3 = world.createObject(pos3,tri,eObjType::DYNAMIC),
		obj4 = world.createObject(pos4,aabb,eObjType::DYNAMIC),
//		obj5 = world.createObject(pos5,poly,eObjType::DYNAMIC),
		obj6 = world.createObject(pos6,circle,eObjType::DYNAMIC);
	world.setDebugDraw(draw);
	world.drawDebugWorld(renderer);
	SDL_RenderPresent(renderer);
}
