#ifndef COLLTEST2D_HPP
#define COLLTEST2D_HPP

#include <cMath>
#include "mathVector.hpp"
#include "collShape2D.hpp"
#include "collObject.hpp"
#include "collPair.hpp"

void collTestHandler (cCollPair& collPair) {
}
/*
cVector2 collTestPointPoint (const cCollObject2D& object1, const cCollObject2D& object2) {
	cVector2 obj1Pos(object1.getPosition()), obj2Pos(object2.getPosition());
	if (obj1Pos == objPos2)
		;
	;
}
cVector2 collTestPointCircle (const cCollObject2D& object1, const cCollObject2D& object2) {

}
cVector2 collTestPointAabb (const cCollObject2D& object1, const cCollObject2D& object2) {

}
*/
cVector2 collTestCircleCircle (const cCollObject2D& object1, const cCollObject2D& object2) {
	cVector2 obj1Pos(object1.getPosition()),
			 obj2Pos(object2.getPosition()),
			 dv(obj1Pos-obj2Pos);
	double obj1Rad = object1.getCollShape()->getShapeDim().get(0,0),
		   obj2Rad = object2.getCollShape()->getShapeDim().get(0,0),
		   overlap = dv.magnitude()-(obj1Rad+obj2Rad);
	if (overlap < 0) {
		double radFromAxisX = angleRad(dv.absolute(),cVector2(1,0));
		return cVector2(overlap*std::cos(radFromAxisX),overlap*std::sin(radFromAxisX));
	}
	else if (overlap == 0) {
		return cVector2(0,0);
	}
	return cVector2(-1,-1);
}/*
cVector2 collTestCircleAabb (const cCollObject2D& object1, const cCollObject2D& object2) {

}
cVector2 collTestAabbAabb (const cCollObject2D& object1, const cCollObject2D& object2) {

}
*/
#endif
