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
	std::shared_ptr<cCollAabb> shape1 = std::make_shared<cCollAabb>(5,20),
		shape2 = std::make_shared<cCollAabb>(50,5);
	std::shared_ptr<cCollCircle> shape3 = std::make_shared<cCollCircle>(5),
		shape4 = std::make_shared<cCollCircle>(50);
	std::vector<cVector2> polyPtList = {cVector2(0,50),cVector2(-25,25),cVector2(-15,-25),cVector2(15,-25),
		cVector2(25,25),cVector2(0,50)};
	std::shared_ptr<cCollPoly> shape5 = std::make_shared<cCollPoly>(polyPtList);
	std::shared_ptr<cCollObj> obj1 = std::make_shared<cCollObj>(pos1,shape1),
		obj2 = std::make_shared<cCollObj>(pos2,shape2);
	cCollPair pair(obj1,obj2);
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
		obj1->translate(dx,dy);
//		obj2.rotate(0.005);
		std::cout << "Obj1 Pos:\n" << obj1->getObjPos() <<
			"\nObj2 Pos:\n" << obj2->getObjPos();
		testHandler.testPair(pair);
		if (pair.getCollType() == eCollType::COLLISION) {
			std::cout << "\nCollision Overlap:\n" << pair.getObjOverlap() << "\n";
		}
		if (dx == -0.1 && dy == -0.1)
			runLoop = false;

		// Render shapes
		drawer.drawObj(renderer,*obj1,red);
		drawer.drawObj(renderer,*obj2,green);
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
