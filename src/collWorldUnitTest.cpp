#include "collWorldUnitTest.hpp"

void collWorldUnitTest (void) {
	std::cout << "Testing collWorld constructor:\n";
	std::shared_ptr<cGenBroadphase> broadphase = std::make_shared<cGenBroadphase>();
	cCollWorld world(broadphase);
	std::shared_ptr<cCollDebugDrawer> drawer;
	world.setDebugDraw(drawer);
	std::cout << "Testing createObject (cVector2, cCollShape&):\n";
	cCollAabb shape(2,10),
			  shape2(10,2);
	cVector2 pos1(20,20),
			 pos2(20,25),
			 pos3(0,0);
	cCollComp coll1(shape);
	cEntityNode node1(0,cPosComp(0,0,0),coll1);
	std::vector<cEntityNode> nodeList;
	nodeList.push_back(node1);
	nodeList.push_back(cEntityNode(1,cPosComp(1,2,3),cCollComp(shape2)));
	const cEntity& ent2 = world.createEntity(eEntityType::DYNAMIC,cPosComp(pos2,0),
					nodeList),
		&	ent3 = world.createEntity(eEntityType::KINEMATIC,cPosComp(pos3,0),
					nodeList);
	const cEntity& ent1 = world.createEntity(eEntityType::STATIC,cPosComp(pos1,0),node1);
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
