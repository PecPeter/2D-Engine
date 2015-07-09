#include "collTest2D.hpp"

cCollTestHandler::cCollTestHandler (void): noColl_(-1,-1), contactColl_(0,0) {}

void cCollTestHandler::operator() (cCollPair& collPair) {
	const cCollObject2D* obj1 = collPair.object1(),
		  *obj2 = collPair.object2();
	eShapeType shape1 = obj1->getCollShape()->getShapeType(),
			   shape2 = obj2->getCollShape()->getShapeType();
	cVector2 collVector;
	if (shape1 == eShapeType::AABB && shape2 == eShapeType::AABB)
		collVector = collTestAabbAabb(*obj1,*obj2);
	if (collVector == noColl_)
		collPair.setCollType(eCollType::NO_COLLISION);
	else if (collVector == contactColl_)
		collPair.setCollType(eCollType::CONTACT);
	else
		collPair.setCollType(eCollType::COLLISION);
	collPair.setObjOverlap(collVector);
}

cVector2 cCollTestHandler::collTestAabbAabb (const cCollObject2D& obj1,
		const cCollObject2D& obj2) {
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
			return contactColl_;
		return noColl_;
	}
	else if (xOverlap == 0) {
		if (yOverlap <= 0)
			return contactColl_;
	}
	return noColl_;
}
