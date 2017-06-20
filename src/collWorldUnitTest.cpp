#include "collWorldUnitTest.hpp"

/*
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
*//*	cEntity* ent2 = world.createEntity(0,cPosComp(pos2,0),
					nodeList,eEntityType::DYNAMIC),
		   * ent3 = world.createEntity(1,cPosComp(pos3,0),
					nodeList,eEntityType::KINEMATIC);
	cEntity* ent1 = world.createEntity(2,cPosComp(pos1,0),node1);
*//*	cEntity* ent = world.createEntity(0,cPosComp(pos4,0),node2),
		   * ent1 = world.createEntity(1,cPosComp(pos3,0),nodeList);
*//*	ent1->translate(1,0);
	ent2->translate(1,0);
	ent3->translate(1,0);
	*//*
	std::forward_list<cCollPair> pairList = world.checkColls();
	for (auto& itr : pairList)
	{
		cEntity entity1 = itr.ent1(),
				entity2 = itr.ent2();
		std::list<sCollPairInfo> pairInfo = itr.getCollisions();
		for (auto& itr2 : pairInfo)
		{
			int nodeId1 = itr2.entNodeId1_,
				nodeId2 = itr2.entNodeId2_;
			cVector2 overlap = itr2.overlap_;
			std::cout << overlap << std::endl;
		}
	}
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
*/
void collWorldUnitTest (void) {
	cVector2 worldSize(640,480);
	cCollWorld world1(eBroadphaseType::GENERAL),
			   world2(eBroadphaseType::GRID,static_cast<void*>(&worldSize));
	static_cast<cGridBroadphase*>(world2.getBroadphase())->setCellSize(100,100);
/*	cCollAabb shape(2,10),
			  shape2(10,2),
			  shape3(25,25);

	cVector2 pos1(20,20),
			 pos2(20,25),
			 pos3(100,75),
			 pos4(101,100);
	cCollComp coll1(shape),
			  coll2(shape3);
	cEntityNode node1(0,cPosComp(0,0,0),coll1),
				node2(5,cPosComp(0,0,0),coll2);
	std::vector<cEntityNode> nodeList;
	nodeList.push_back(node2);
	nodeList.push_back(cEntityNode(9,cPosComp(40,0,0),cCollComp(shape3)));
	nodeList.push_back(cEntityNode(21,cPosComp(0,-40,0),cCollComp(shape3)));
	cEntity* ent11 = world1.createEntity(0,cPosComp(pos4,0),node2,
			eEntityType::DYNAMIC),
		   * ent21 = world1.createEntity(1,cPosComp(pos3,0),nodeList);
//	cEntity* ent12 = world2.createEntity(2,cPosComp(pos4,0),node2,
//			eEntityType::DYNAMIC),
//		   * ent22 = world2.createEntity(3,cPosComp(pos3,0),nodeList);
*//*	int arraySize = 500;
	cEntity* entArray[arraySize];
	for (int i = 0; i < arraySize; ++i) {
		entArray[i] = world2.createEntity(i,cPosComp(pos4,0),node2);
	}
*/
//	ent11->translate(1,0);
//	ent21->translate(1,0);
//	ent12->translate(1,0);
//	ent22->translate(1,0);
	std::forward_list<cCollPair> pairList1 = world1.checkColls();
	for (auto& itr : pairList1) {
		cEntity entity1 = itr.ent1(),
				entity2 = itr.ent2();
		std::list<sCollPairInfo> pairInfo = itr.getCollisions();
		for (auto& itr2 : pairInfo)
		{
			int nodeId1 = itr2.entNodeId1_,
				nodeId2 = itr2.entNodeId2_;
			cVector2 overlap = itr2.overlap_;
			int entId1 = entity1.getId(),
				entId2 = entity2.getId();
			std::cout << "PairList1\n";
			std::cout << "Ent " << std::to_string(entId1) << " Node: " <<
				std::to_string(nodeId1) << " collided with " <<
				"Ent " << std::to_string(entId2) << " Node: " <<
				std::to_string(nodeId2) << std::endl;
			std::cout << overlap << std::endl;
		}
	}








	// Create the ship entity
	cPosComp shipPos(0,0,0);

	cCollAabb shipShape(100,100);

	cEntityNode shipNode(0,shipPos,cCollComp(shipShape));

	cEntity* ship_ = world2.createEntity(0,cPosComp(320,200,0),shipNode,
			eEntityType::DYNAMIC);
	
	// Create the walls
	int wallHW = 200, wallHH = 100;
	cPosComp wallPos1(-wallHW,0,0),
			 wallPos2(wallHW,0,0),
			 wallPos3(0,-wallHH,0),
			 wallPos4(0,wallHH,0);

	cCollAabb vertWall(5,wallHH),
			  horzWall(wallHW,5);

	std::vector<cEntityNode> walls;
	walls.push_back(cEntityNode(0,wallPos1,cCollComp(vertWall)));
	walls.push_back(cEntityNode(1,wallPos2,cCollComp(vertWall)));
	walls.push_back(cEntityNode(2,wallPos3,cCollComp(horzWall)));
	walls.push_back(cEntityNode(3,wallPos4,cCollComp(horzWall)));

	cEntity* walls_ = world2.createEntity(1,cPosComp(320,240,0),walls,
			eEntityType::STATIC);

	// Create the shields
	cCollAabb shieldShape(2.5,2.5);

	cPosComp posUL(-2.5,-2.5,0),
			 posUR(2.5,-2.5,0),
			 posLL(-2.5,2.5,0),
			 posLR(2.5,2.5,0);

	std::vector<cEntityNode> shieldNodes;
	shieldNodes.push_back(cEntityNode(0,posUL,cCollComp(shieldShape)));
	shieldNodes.push_back(cEntityNode(1,posUR,cCollComp(shieldShape)));
	shieldNodes.push_back(cEntityNode(2,posLL,cCollComp(shieldShape)));
	shieldNodes.push_back(cEntityNode(3,posLR,cCollComp(shieldShape)));

	cPosComp posShield1(282.5,300,0),
			 posShield2(307.5,300,0),
			 posShield3(332.5,300,0),
			 posShield4(357.5,300,0);

	cEntity* shield1_ = world2.createEntity(2,posShield1,shieldNodes,
			eEntityType::STATIC);
	cEntity* shield2_ = world2.createEntity(3,posShield2,shieldNodes,
			eEntityType::STATIC);
	cEntity* shield3_ = world2.createEntity(4,posShield3,shieldNodes,
			eEntityType::STATIC);
	cEntity* shield4_ = world2.createEntity(5,posShield4,shieldNodes,
			eEntityType::STATIC);

	// Create the alien array (11x5)
	int nodeIndexHW = 6, nodeIndexHH = 3;
	double hw = 4.0,
		   hh = 4.0,
		   space = 10.0;

	cCollAabb alienShape(hw,hh);
	cCollComp alienCollComp(alienShape);

	std::vector<cEntityNode> alienNodes;

	alienNodes.push_back(cEntityNode(0,cPosComp(0,0,0),alienCollComp));
	for (int i = 1; i < nodeIndexHW; ++i)
	{
		double x = i;
		cPosComp pos1(x*(2.0*hw+space),0,0),
				 pos2(-x*(2.0*hw+space),0,0);
		int nodeId1 = (i*2)-1,
			nodeId2 = i*2;
		alienNodes.push_back(cEntityNode(nodeId1,pos1,alienCollComp));
		alienNodes.push_back(cEntityNode(nodeId2,pos2,alienCollComp));
	}
	for (int i = 1; i < nodeIndexHH; ++i)
	{
		double y = i;
		cPosComp pos1(0,y*(2.0*hw+space),0),
				 pos2(0,-y*(2.0*hw+space),0);
		int nodeId1 = (i*2)+9,
			nodeId2 = i*2+10;
		alienNodes.push_back(cEntityNode(nodeId1,pos1,alienCollComp));
		alienNodes.push_back(cEntityNode(nodeId2,pos2,alienCollComp));

	}
	for (int i = 1; i < nodeIndexHW; ++i)
	{
		for (int j = 1; j < nodeIndexHH; ++j)
		{
			double x = i,
				   y = j;
			cPosComp pos1(x*(2.0*hw+space),y*(2.0*hh+space),0),
					 pos2(-x*(2.0*hw+space),y*(2.0*hh+space),0),
					 pos3(-x*(2.0*hw+space),-y*(2.0*hh+space),0),
					 pos4(x*(2.0*hw+space),-y*(2.0*hh+space),0);
			int nodeId1 = 7+(2*i+j-1)*4,
				nodeId2 = 8+(2*i+j-1)*4,
				nodeId3 = 9+(2*i+j-1)*4,
				nodeId4 = 10+(2*i+j-1)*4;
			alienNodes.push_back(cEntityNode(nodeId1,pos1,alienCollComp));
			alienNodes.push_back(cEntityNode(nodeId2,pos2,alienCollComp));
			alienNodes.push_back(cEntityNode(nodeId3,pos3,alienCollComp));
			alienNodes.push_back(cEntityNode(nodeId4,pos4,alienCollComp));
		}
	}

	cPosComp alienPos(320,240,0);
	cEntity* aliens_ = world2.createEntity(6,alienPos,alienNodes,
			eEntityType::DYNAMIC);

	// Create the bullets
	cCollAabb bulletShape(1.0,1.0);

	cPosComp bulletPos(0.0,0.0,0);
	cPosComp bulletPos1(300,100,0);

	cCollComp bulletCollComp(bulletShape);
	
	cEntityNode bulletNode(0,bulletPos,bulletCollComp);






	std::forward_list<cCollPair> pairList2 = world2.checkColls();
	int i = 0;
	for (auto& itr : pairList2)
	{
		cEntity entity1 = itr.ent1(),
				entity2 = itr.ent2();
		std::list<sCollPairInfo> pairInfo = itr.getCollisions();
		for (auto& itr2 : pairInfo)
		{
			int nodeId1 = itr2.entNodeId1_,
				nodeId2 = itr2.entNodeId2_;
			cVector2 overlap = itr2.overlap_;
			int entId1 = entity1.getId(),
				entId2 = entity2.getId();
			std::cout << "PairList2\n";
			std::cout << "Ent " << std::to_string(entId1) << " Node: " <<
				std::to_string(nodeId1) << " collided with " <<
				"Ent " << std::to_string(entId2) << " Node: " <<
				std::to_string(nodeId2) << std::endl;
			std::cout << overlap << std::endl;
			++i;
		}
	}
	std::cout << i << std::endl;
	bool renderDebug = true;
	if (renderDebug == true) {
		cCollDebugDrawer* drawer = new cCollDebugDrawer;
		world2.setDebugDraw(drawer);
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_Window* window = SDL_CreateWindow("TEST",SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN);
		SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);
		world2.drawDebugWorld(renderer);
		SDL_RenderPresent(renderer);
		int x;
		std::cin >> x;
	}
}
