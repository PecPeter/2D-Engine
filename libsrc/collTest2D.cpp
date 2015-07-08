#include "collTest2D.hpp"

void collTestHandler (cCollPair& collPair) {

}

cVector2 collTestAabbAabb (const cCollObject2D& obj1, const cCollObject2D& obj2) {
	cVector2 dv(obj2.getPosition()-obj1.getPosition());
	const cCollAabb* shapeAabb1 = dynamic_cast<const cCollAabb*>(obj1.getCollShape());
	const cCollAabb* shapeAabb2 = dynamic_cast<const cCollAabb*>(obj2.getCollShape());
	double dHalfWidth = shapeAabb1->getHalfWidth()+shapeAabb2->getHalfWidth(),
		   xOverlap = std::abs(dv.getX())-dHalfWidth,
		   dHalfHeight = shapeAabb1->getHalfHeight()+shapeAabb2->getHalfHeight(),
		   yOverlap = std::abs(dv.getY())-dHalfHeight;
	if (dv.getX() < 0)
		dHalfWidth *= -1.0;
	if (dv.getY() < 0)
		dHalfHeight *= -1.0;
	if (xOverlap < 0) {
		if (yOverlap < 0)
			return cVector2(dv-cVector2(dHalfWidth,dHalfHeight));
		else if (yOverlap == 0)
			return cVector2(0,0);
		return cVector2(-1,-1);
	}
	else if (xOverlap == 0) {
		if (yOverlap <= 0)
			return cVector2(0,0);
	}
	return cVector2(-1,-1);
}
