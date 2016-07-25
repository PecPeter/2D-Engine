#include "collPairUnitTest.hpp"

void collPairUnitTest (void) {
	cCollAabb shape1(10,20),
			  shape2(20,200);
	cVector2 pos1(40,100), pos2(0,0);
	cEntityNode node1(0,cPosComp(0,0,0),cCollComp(shape1)),
				node2(0,cPosComp(0,0,0),cCollComp(shape2));
	cEntity ent1(0,eEntityType::STATIC,cPosComp(pos1,0),node1),
			ent2(1,eEntityType::DYNAMIC,cPosComp(pos2,0),node2);
	cCollPair collPair(ent1,ent2);
	const cEntity& ent1Ref = collPair.ent1(),
		  		 & ent2Ref = collPair.ent2();
	ent1Ref.getId();
	ent2Ref.getId();

/*	collPair.setOverlap(cVector2(2,-0.4444));
	std::cout << "\nOverlap:\n" << collPair.getOverlap();
	collPair.setCollType(eCollType::CONTACT);
	collPair.getCollType();
*/
}
