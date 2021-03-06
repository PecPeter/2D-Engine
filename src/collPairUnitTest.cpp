#include "collPairUnitTest.hpp"

void collPairUnitTest (void) {
	cCollAabb* shape1 = new cCollAabb(10,20),
		*shape2 = new cCollAabb(20,200);
	cVector2 pos1(40,100), pos2(0,0);
	cCollObj obj1(pos1,shape1), obj2(pos2,shape2,eObjType::DYNAMIC);
	cCollPair collPair(&obj1,&obj2);
	const cCollObj* tmp1 = collPair.obj1(),
		  *tmp2 = collPair.obj2();
	collPair.setObjOverlap(cVector2(2,-0.4444));
	std::cout << "\nOverlap:\n" << collPair.getObjOverlap();
	collPair.setCollType(eCollType::CONTACT);
	collPair.getCollType();
	delete shape1;
	delete shape2;
}
