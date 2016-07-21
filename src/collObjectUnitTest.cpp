#include "collObjectUnitTest.hpp"

void collObjectUnitTest (void) {
	cCollAabb shape(2,2);
	cVector2 pos(20,0);
	cEntity ent1(0,eEntityType::DYNAMIC,cPosComp(pos,0),
			cEntityNode(0,cPosComp(0,0,0),cCollComp(shape)));

	cVector2 dv(-4.5,99);
	ent1.translate (dv);
	std::cout << "Position after translating:\n" << dv << "\nPosition:\n" << ent1.getPos() << "\n";
	ent1.translate(4.5,-99);
	std::cout << "Position after translating using translate (double, double):\n" << ent1.getPos() << "\n";
}
