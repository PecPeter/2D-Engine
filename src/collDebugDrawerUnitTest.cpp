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
	std::shared_ptr<cGenBroadphase> broadphase = 
		std::make_shared<cGenBroadphase>();
	cCollWorld world(broadphase);
	cCollPoint point;
	cCollLine line(cVector2(0.250,4.0));
	cCollTri tri(5,10,16,2,3,-4);
	cCollAabb aabb(10,5);
	//Add a poly shape
	cCollCircle circle(10);
	cPosComp pos1(100,300,0),
			 pos2(20,20,0),
			 pos3(30,30,0),
			 pos4(40,40,0),
			 pos5(50,50,0),
			 pos6(60,60,0);
	cCollComp coll1(point),
			  coll2(line),
			  coll3(tri),
			  coll4(aabb),
//			  coll5(poly),
			  coll6(circle);
	cEntityNode node1(0,cPosComp(0,0,0),coll4),
				node2(0,cPosComp(100,0,0),coll3);
	std::vector<cEntityNode> nodeList1;
	nodeList1.push_back(node1);
	nodeList1.push_back(cEntityNode(1,cPosComp(50,0,0),coll4,0));
	cEntity* ent1 = world.createEntity(eEntityType::STATIC,pos1,nodeList1),
		   * ent2 = world.createEntity(eEntityType::DYNAMIC,pos2,node1),
		   * ent3 = world.createEntity(eEntityType::DYNAMIC,pos3,node2);
//			ent4 = world.createEntity(eEntityType::DYNAMIC,pos4,),
//			ent5 = world.createEntity(eEntityType::DYNAMIC,pos5,),
//			ent6 = world.createEntity(eEntityType::KINEMATIC,pos6,);
	for (int i = 0; i < 1000; ++i) {
		ent1->rotate(0.007);
		ent2->translate(1,1);
		ent3->translate(2,2);

		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);
		world.setDebugDraw(draw);
		world.drawDebugWorld(renderer);
		SDL_RenderPresent(renderer);
	}
}
