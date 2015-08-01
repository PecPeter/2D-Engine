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
	TTF_Font* font = TTF_OpenFont("TerminusTTF-4.39.ttf",20);
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);

	cCollDebugDrawer draw;
	cVector3 red(255,0,0),
			 green(0,255,0),
			 blue(0,0,255);
/*	in collDebugDrawer.hpp, private needs to be commented out for these to work
	draw.drawLine(renderer,cVector2(10,10),cVector2(15,10),blue);
	draw.drawSphere(renderer,cVector2(300,150),15,red);
	draw.drawTriangle(renderer,cVector2(50,50),cVector2(100,30),cVector2(1,1),
			green);
	draw.drawRect(renderer,cVector2(400,400),20,30,blue);
	std::vector<cVector2> pList;
	pList.push_back(cVector2(200,200));
	pList.push_back(cVector2(220,220));
	pList.push_back(cVector2(200,240));
	pList.push_back(cVector2(180,220));
	draw.drawPoly(renderer,pList,red);
	draw.drawPoint(renderer,cVector2(6,400),red);
	draw.drawPoint(renderer,cVector2(500,450),red);
*/
	draw.drawStrL(renderer,font,cVector2(6,400),"Point on the left",
			cVector3(255,255,255));
	draw.drawStrR(renderer,font,cVector2(500,450),"Point on the right",
			cVector3(255,255,255));
	cGenBroadphase broadphase;
	cCollWorld world(&broadphase);
	cCollAabb aabb1(10,5);
	cVector2 pos1(10,10),
			 pos2(20,20);
	cCollObj* obj1 = world.createObject(pos1,aabb1),
		*obj2 = world.createObject(pos2,aabb1,eObjType::DYNAMIC);
	world.setDebugDraw(&draw);
	world.drawDebugWorld(renderer);
	SDL_RenderPresent(renderer);
}
