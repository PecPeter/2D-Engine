#include "collPair.hpp"

cCollPair::cCollPair (cCollObject2D* object1, cCollObject2D* object2):
	object1_(object1), object2_(object2), overlap_(2,1),
	collType_(eCollType::NO_COLLISION) {}

cCollPair::~cCollPair (void) {}

const cCollObject2D* cCollPair::object1 (void) const {
	return object1_;
}

const cCollObject2D* cCollPair::object2 (void) const {
	return object2_;
}

void cCollPair::setObjOverlap (const cVector2& overlap) {
	overlap_ = overlap;
}

cVector2& cCollPair::getObjOverlap (void) {
	return overlap_;
}

void cCollPair::setCollType (const eCollType& collType) {
	collType_ = collType;
}

eCollType cCollPair::getCollType (void) {
	return collType_;
}
