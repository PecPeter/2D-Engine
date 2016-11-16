#include "collWorldUnitTest.hpp"

void collWorldUnitTest (void) {
	setSettings(600,600,60,100,10);
	std::cout << "Testing collWorld constructor:\n";
	cCollWorld world(eBroadphaseType::GRID);
	static_cast<cGridBroadphase*>(world.getBroadphase())->setCellSize(100,100);
	cCollDebugDrawer* drawer = new cCollDebugDrawer;
	world.setDebugDraw(drawer);
	std::cout << "Testing createObject (cVector2, cCollShape&):\n";
	cCollAabb shape(2,10),
			  shape2(10,2),
			  shape3(25,25);
	cVector2 pos1(20,20),
			 pos2(20,25),
			 pos3(100,75),
			 pos4(101,100);
	cCollComp coll1(shape),
			  coll2(shape3);
	cEntityNode node1(0,cPosComp(0,0,0),coll1),
				node2(0,cPosComp(0,0,0),coll2);
	std::vector<cEntityNode> nodeList;
	nodeList.push_back(node2);
	nodeList.push_back(cEntityNode(1,cPosComp(20,0,0),cCollComp(shape3)));
/*	cEntity* ent2 = world.createEntity(0,cPosComp(pos2,0),
					nodeList,eEntityType::DYNAMIC),
		   * ent3 = world.createEntity(1,cPosComp(pos3,0),
					nodeList,eEntityType::KINEMATIC);
	cEntity* ent1 = world.createEntity(2,cPosComp(pos1,0),node1);
*/	cEntity* ent = world.createEntity(0,cPosComp(pos4,0),node2),
		   * ent1 = world.createEntity(1,cPosComp(pos3,0),nodeList);
/*	ent1->translate(1,0);
	ent2->translate(1,0);
	ent3->translate(1,0);
	*/
	world.checkColls();
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("TEST",SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,600,600,SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
	world.drawDebugWorld(renderer);
	SDL_RenderPresent(renderer);
}
