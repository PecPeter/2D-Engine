#include "collTestHandlerUnitTest.hpp"

void collTestHandlerUnitTest (void) {
	cVector2 pos1(0,0), pos2(16,0);
	cCollAabb shape1(5,5), shape2(10,10);
	cCollObj obj1(pos1,&shape1), obj2(pos2,&shape2);
	cCollPair pair(&obj1,&obj2);
	cCollTest testHandler;

	bool runLoop = true;
	while (runLoop == true) {
		double dx = 0, dy = 0;
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
	}
}
