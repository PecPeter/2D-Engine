#include "collObjectUnitTest.hpp"

void collObjectUnitTest (void) {
	cCollAabb* shape = new cCollAabb(2,2);
	cVector2 pos(20,0);
	cCollObj obj1(pos,shape);

	cVector2 dv(-4.5,99);
	obj1.translate (dv);
	std::cout << "Position after translating:\n" << dv << "\nPosition:\n" << obj1.getObjPos() << "\n";
	obj1.translate(4.5,-99);
	std::cout << "Position after translating using translate (double, double):\n" << obj1.getObjPos() << "\n";
	delete shape;
}
