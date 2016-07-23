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

	cEntityNode node1(0,cPosComp(0,0,0),cCollComp(shape3)),
				node2(0,cPosComp(0,0,0),cCollComp(shape4));
	cEntity ent1(0,eEntityType::DYNAMIC,cPosComp(pos1,0),node1),
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

		if (dx == -0.1 && dy == -0.1)
			runLoop = false;
		else {
			for (const auto& listItr : pair.getCollisions()) {
				if (listItr.collType_ == eCollType::COLLISION) {
					std::cout << "\nCollision Overlap:\n" << 
						listItr.overlap_ << "\n";
				}
			}
		}
		// Render shapes
		drawer.drawEnt(renderer,ent1,red);
		drawer.drawEnt(renderer,ent2,green);
		SDL_RenderPresent(renderer);
	}
}
