#include "collObject.hpp"

cCollObject2D::cCollObject2D (const cVector2& pos, int collShapeIndex, eObjectType objectType):
	pos_(pos),collShapeIndex_(collShapeIndex),objectType_(objectType) {}

cCollObject2D::~cCollObject2D (void) {}

void cCollObject2D::translate (double dx, double dy) {
	cVector2 dv(dx,dy);
	pos_ += dv;
}

void cCollObject2D::translate (const cVector2& dv) {
	pos_ += dv;
}
