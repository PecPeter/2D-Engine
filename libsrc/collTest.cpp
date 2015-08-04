#include "collTest.hpp"

cCollTest::cCollTest (void): noColl_(1,1), contactColl_(0,0) {
	collTestMap_[collTestMapKey(eShapeType::AABB,eShapeType::AABB)] =
		&cCollTest::collTestAabbAabb;
	collTestMap_[collTestMapKey(eShapeType::AABB,eShapeType::LINE)] = 
		&cCollTest::collTestAabbLine;
	collTestMap_[collTestMapKey(eShapeType::LINE,eShapeType::AABB)] = 
		&cCollTest::collTestLineAabb;
}

void cCollTest::testPair (cCollPair& collPair) {
	const cCollObj* obj1 = collPair.object1(),
		  *obj2 = collPair.object2();
	eShapeType shape1 = obj1->getCollShape()->getShapeType(),
			   shape2 = obj2->getCollShape()->getShapeType();
	auto function = collTestMap_.at(collTestMapKey(shape1,shape2));
	cVector2 collVector = (this->*function)(*obj1,*obj2);

	if (collVector == noColl_)
		collPair.setCollType(eCollType::NO_COLLISION);
	else if (collVector == contactColl_)
		collPair.setCollType(eCollType::CONTACT);
	else
		collPair.setCollType(eCollType::COLLISION);
	collPair.setObjOverlap(collVector);
}

cVector2 cCollTest::collTestAabbAabb (const cCollObj& obj1,
		const cCollObj& obj2) {
	cVector2 dv(obj2.getObjPos()-obj1.getObjPos());
	const cCollAabb* shapeAabb1 = static_cast<const cCollAabb*>(obj1.getCollShape());
	const cCollAabb* shapeAabb2 = static_cast<const cCollAabb*>(obj2.getCollShape());
	double dHalfWidth = shapeAabb1->getHW()+shapeAabb2->getHW(),
		   xOverlap = std::abs(dv.getX())-dHalfWidth,
		   dHalfHeight = shapeAabb1->getHH()+shapeAabb2->getHH(),
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

cVector2 cCollTest::collTestAabbLine (const cCollObj& aabb,
		const cCollObj& line) {
	//Determine the angle
	cVector2 lineDir =
		static_cast<const cCollLine*>(line.getCollShape())->getDir();
	double trigVal = std::cos(vAngleRad(lineDir,cVector2(1,0)));
//	double angleRad = vAngleRad(lineDir,cVector2(1,0));
	//Determine the length of the rotated half width
	const cCollAabb* shapeAabb =
		static_cast<const cCollAabb*>(aabb.getCollShape());
//	double trigVal = std::cos(angleRad
	double rotHw = shapeAabb->getHW()*trigVal+shapeAabb->getHH()*trigVal;
	
	//Determine distance between points
	cVector2 intrsctPt = intersctPt(aabb.getObjPos(),vNormal(lineDir),
			line.getObjPos(),lineDir),
			 dv = intrsctPt-aabb.getObjPos();
	if (vMagnitude(dv) < rotHw)
		return cVector2(dv-vUnitVector(dv)*rotHw);
	else if (vMagnitude(dv) == rotHw)
		return contactColl_;
	return noColl_;
}

cVector2 cCollTest::collTestLineAabb (const cCollObj& line,
		const cCollObj& aabb) {
	return collTestAabbLine(aabb,line);
}

cVector2 cCollTest::collTestLineLine (const cCollObj& line1,
		const cCollObj& line2) {
	return noColl_;
}
