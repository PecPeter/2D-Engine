#include "collObject.hpp"

cCollObject2D::cCollObject2D (const cVector2& pos, const cCollShape* shape, eObjectType objectType):
	pos_(pos),shape_(shape),objectType_(objectType) {}

cCollObject2D::~cCollObject2D (void) {}

void cCollObject2D::translate (double dx, double dy) {
	cVector2 dv(dx,dy);
	pos_ += dv;
}

void cCollObject2D::translate (const cVector2& dv) {
	pos_ += dv;
}
