#include "collPairUnitTest.hpp"

void collPairUnitTest (void) {
	std::shared_ptr<cCollAabb> shape1 = std::make_shared<cCollAabb>(10,20),
		shape2 = std::make_shared<cCollAabb>(20,200);
	cVector2 pos1(40,100), pos2(0,0);
	std::shared_ptr<cCollObj> obj1 = std::make_shared<cCollObj>(pos1,shape1),
		obj2 = std::make_shared<cCollObj>(pos2,shape2,eObjType::DYNAMIC);
	cCollPair collPair(obj1,obj2);
	std::weak_ptr<cCollObj> tmp1 = collPair.obj1(),
		  tmp2 = collPair.obj2();
	collPair.setObjOverlap(cVector2(2,-0.4444));
	std::cout << "\nOverlap:\n" << collPair.getObjOverlap();
	collPair.setCollType(eCollType::CONTACT);
	collPair.getCollType();
}
