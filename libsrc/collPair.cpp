#include "collPair.hpp"

cCollPair::cCollPair (cCollObj* object1, cCollObj* object2):
	object1_(object1), object2_(object2), collType_(eCollType::NO_COLLISION) {}

cCollPair::~cCollPair (void) {}

const cCollObj* cCollPair::object1 (void) const {
	return object1_;
}

const cCollObj* cCollPair::object2 (void) const {
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
