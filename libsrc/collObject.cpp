#include "collObject.hpp"

cCollObject2D::cCollObject2D (const cVector2& pos, const cCollShape* shape,
		eObjectType objectType): pos_(pos),shape_(shape),
		objectType_(objectType), objPtr_(nullptr) {}

cCollObject2D::~cCollObject2D (void) {}

void cCollObject2D::translate (double dx, double dy) {
	cVector2 dv(dx,dy);
	pos_ += dv;
}

void cCollObject2D::translate (const cVector2& dv) {
	pos_ += dv;
}

const cVector2& cCollObject2D::getPosition (void) const {
	return pos_;
}

const cCollShape* cCollObject2D::getCollShape (void) const {
	return shape_;
}

eObjectType cCollObject2D::getObjectType (void) const {
	return objectType_;
}

void cCollObject2D::setObjPtr (void* objPtr) {
	objPtr_ = objPtr;
}

void* cCollObject2D::getObjPtr (void) {
	return objPtr_;
}
