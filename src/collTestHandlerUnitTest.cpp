#include "collTestHandlerUnitTest.hpp"

void collTestHandlerUnitTest (void) {
	cVector2 pos1(0,0), pos2(50,50);
	cCollAabb shape1(5,5), shape2(10,10);
	cCollObj obj1(pos1,&shape1), obj2(pos2,&shape2);
	cCollPair pair(&obj1,&obj2);
	cCollTestHandler testHandler;
	testHandler.testPair(pair);
	obj1.translate(35,0);
	testHandler.testPair(pair);
	obj1.translate(0,35);
	testHandler.testPair(pair);
	obj1.translate(1,1);
	testHandler.testPair(pair);
	obj1.translate(-1,1);
	testHandler.testPair(pair);
	obj1.translate(-1,1);
	testHandler.testPair(pair);
}
