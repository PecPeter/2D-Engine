#include "collTestHandlerUnitTest.hpp"

void collTestHandlerUnitTest (void) {
	cCollDebugDrawer drawer;
	if (SDL_WasInit(0) == 0)
		SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("TEST",SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	cVector4 red(255,255,0,0),
			 green(255,0,255,0),
			 blue(255,0,0,255);

	cVector2 pos1(150,200), pos2(200,200);
	cCollAabb shape1(5,20),
			  shape2(50,5);
	cCollCircle shape3(5),
				shape4(50);
	std::vector<cVector2> polyPtList = 
		{cVector2(0,50),cVector2(-25,25),cVector2(-15,-25),cVector2(15,-25),
		 cVector2(25,25),cVector2(0,50)};
	cCollPoly shape5(polyPtList);

	cEntityNode node1(0,cPosComp(0,0,0),cCollComp(shape1)),
				node2(0,cPosComp(0,0,0),cCollComp(shape4));
	cEntity ent1(0,eEntityType::STATIC,cPosComp(pos1,0),node1),
			ent2(1,eEntityType::DYNAMIC,cPosComp(pos2,0),node2);
	cCollPair pair(ent1,ent2);
	cCollTest testHandler;

	bool runLoop = true;
	while (runLoop == true) {
		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);

		double dx = 2, dy = 0;
		std::cout << "To exit, enter '-0.1' for dx and dy...\n";
		std::cout << "dx: ";
		std::cin >> dx;
		std::cout << "dy: ";
		std::cin >> dy;
		ent1.translate(dx,dy);
//		obj2.rotate(0.005);
		std::cout << "Ent1 Pos:\n" << ent1.getPos() <<
			"\nEnt2 Pos:\n" << ent2.getPos();
		testHandler.testPair(pair);
		if (pair.getCollType() == eCollType::COLLISION) {
			std::cout << "\nCollision Overlap:\n" << pair.getOverlap() << "\n";
		}
		if (dx == -0.1 && dy == -0.1)
			runLoop = false;

		// Render shapes
		drawer.drawEnt(renderer,ent1,red);
		drawer.drawEnt(renderer,ent2,green);
		SDL_RenderPresent(renderer);
	}
}
/*
void drawPoly (SDL_Renderer* rend, const cCollObj& obj, const cVector3& col) {
	std::vector<cVector2> ptList = obj.getGenCollShape().lock()->getData();
	ptList.push_back(*ptList.begin());
	Sint16* vx = new Sint16[ptList.size()],
		*vy = new Sint16[ptList.size()];
	cVector2 objPos = obj.getObjPos();
	for (std::size_t i = 0; i < ptList.size(); ++i) {
		vx[i] = ptList.at(i).getX()+objPos.getX();
		vy[i] = ptList.at(i).getY()+objPos.getY();
	}
	filledPolygonRGBA(rend,vx,vy,ptList.size(),col.getX(),col.getY(),col.getZ(),255);
}

void drawCircle (SDL_Renderer* rend, const cCollObj& obj, const cVector3& col) {
	filledCircleRGBA(rend,obj.getObjPos().getX(),obj.getObjPos().getY(),
			obj.getGenCollShape().lock()->getData().at(0).getX(),col.getX(),col.getY(),col.getZ(),255);
}
*/
