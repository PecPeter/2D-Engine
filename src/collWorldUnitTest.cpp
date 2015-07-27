#include "collWorldUnitTest.hpp"

void collWorldUnitTest (void) {
	std::cout << "Testing collWorld constructor:\n";
	cGenBroadphase broadphase;
	cCollWorld world(&broadphase);
	std::cout << "Testing createObject (cVector2, cCollShape&):\n";
	cCollAabb shape(2,2);
	cVector2 pos1(0,0),
			 pos2(2,0),
			 pos3(1,0),
			 pos4(0.5,0.5);
	cCollObject2D* obj1 = world.createObject(pos1,shape),
		*obj2 = world.createObject(pos2,shape),
		*obj3 = world.createObject(pos3,shape),
		*obj4 = world.createObject(pos4,shape);
	world.checkColls();
}
