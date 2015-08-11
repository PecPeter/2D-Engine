#include "collTestHandlerUnitTest.hpp"

void collTestHandlerUnitTest (void) {
	if (SDL_WasInit(0) == 0)
		SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("TEST",SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	cVector3 red(255,0,0),
			 green(0,255,0),
			 blue(0,0,255);

	// Implement a graphical view for collision detection
	cVector2 pos1(0,0), pos2(200,200);
	cCollAabb shape1(5,5), shape2(10,10);
	cCollCircle shape3(50);
	cCollObj obj1(pos1,&shape1), obj2(pos2,&shape3);
	cCollPair pair(&obj1,&obj2);
	cCollTest testHandler;

	bool runLoop = true;
	while (runLoop == true) {
		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);

		double dx = 2, dy = 0;
		std::cout << "dx: ";
		std::cin >> dx;
		std::cout << "dy: ";
		std::cin >> dy;
		obj1.translate(dx,dy);
		std::cout << "Obj1 Pos:\n" << obj1.getObjPos() <<
			"\nObj2 Pos:\n" << obj2.getObjPos();
		testHandler.testPair(pair);
		if (pair.getCollType() == eCollType::COLLISION) {
			std::cout << "\nCollision Overlap:\n" << pair.getObjOverlap() << "\n";
		}
		else if (pair.getCollType() == eCollType::CONTACT) {
			std::cout << "\nContact\n";
		}
		else if (pair.getCollType() == eCollType::NO_COLLISION)
			std::cout << "\nNO COLLISION\n";
		if (dx == -999 && dy == -999)
			runLoop = false;

		// Render shapes
		eShapeType obj1Shape = obj1.getCollShape()->getShapeType(),
				   obj2Shape = obj2.getCollShape()->getShapeType();
		if (obj1Shape == eShapeType::POLY)
			drawPoly(renderer,obj1,red);
		else if (obj1Shape == eShapeType::CIRCLE)
			drawCircle(renderer,obj1,red);
		if (obj2Shape == eShapeType::POLY)
			drawPoly(renderer,obj2,green);
		else if (obj2Shape == eShapeType::CIRCLE)
			drawCircle(renderer,obj2,green);

		SDL_RenderPresent(renderer);
	}
}

void drawPoly (SDL_Renderer* rend, const cCollObj& obj, const cVector3& col) {
	std::vector<cVector2> ptList = obj.getCollShape()->getData();
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
			obj.getCollShape()->getData().at(0).getX(),col.getX(),col.getY(),col.getZ(),255);
}
