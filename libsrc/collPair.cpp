#include "collPair.hpp"

cCollPair::cCollPair (std::shared_ptr<cCollObj> object1,
		std::shared_ptr<cCollObj> object2) : collType_(eCollType::NO_COLLISION) {
	eObjType obj1Type = object1->getObjType(),
			 obj2Type = object2->getObjType();
	if (obj1Type == eObjType::STATIC && obj2Type == eObjType::DYNAMIC) {
		object1_ = object2;
		object2_ = object1;
	}
	else {
		object1_ = object1;
		object2_ = object2;
	}
}

/*	WHEN YOU CAN GUARANTEE THAT OBJ1 WONT BE STATIC, REMOVE THE COMMENTS AND
 *	THE ABOVE VERSION OF THE CONSTRUCTOR
cCollPair::cCollPair (cCollObj* object1, cCollObj* object2):
		object1_(object1), object2_(object2), collType_(eCollType::NO_COLLISION) {}
*/

cCollPair::~cCollPair (void) {}

std::weak_ptr<cCollObj> cCollPair::obj1 (void) const {
	return object1_;
}

std::weak_ptr<cCollObj> cCollPair::obj2 (void) const {
	return object2_;
}

void cCollPair::setObjOverlap (const cVector2& overlap) {
	overlap_ = overlap;
}

const cVector2& cCollPair::getObjOverlap (void) const {
	return overlap_;
}

void cCollPair::setCollType (const eCollType& collType) {
	collType_ = collType;
}

eCollType cCollPair::getCollType (void) const {
	return collType_;
}
