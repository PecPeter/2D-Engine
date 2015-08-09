#include "collTest.hpp"

cCollTest::cCollTest (void): noColl_(std::nan(""),std::nan("")), contactColl_(0,0) {
/*	collTestMap_[collTestMapKey(eShapeType::AABB,eShapeType::AABB)] =
		&cCollTest::collTestAabbAabb;
	collTestMap_[collTestMapKey(eShapeType::AABB,eShapeType::LINE)] = 
		&cCollTest::collTestAabbLine;
	collTestMap_[collTestMapKey(eShapeType::LINE,eShapeType::AABB)] = 
		&cCollTest::collTestLineAabb;
		*/
	collTestMap_[collTestMapKey(eShapeType::POLY,eShapeType::POLY)] =
		&cCollTest::collTestPolyPoly;
}

void cCollTest::testPair (cCollPair& collPair) {
	const cCollObj* obj1 = collPair.obj1(),
		  *obj2 = collPair.obj2();
	eShapeType shape1 = obj1->getCollShape()->getShapeType(),
			   shape2 = obj2->getCollShape()->getShapeType();
	auto& function = collTestMap_.at(collTestMapKey(shape1,shape2));
/*	collTestMapPtr function;
	if (shape1 != eShapteType::POLY
	if ((shape1 == eShapeType::LINE) || (shape1 == eShapeType::CIRCLE) ||
				(shape2 == eShapeType::LINE) || (shape2 == eShapeType::CIRCLE))
		function = collTestMap_.at(collTestMapKey(shape1,shape2));
	else
		function = &cCollTest::collTestPolyPoly;
*/	cVector2 collVector = (this->*function)(*obj1,*obj2);

	if (collVector == noColl_)
		collPair.setCollType(eCollType::NO_COLLISION);
	else if (collVector == contactColl_)
		collPair.setCollType(eCollType::CONTACT);
	else
		collPair.setCollType(eCollType::COLLISION);
	collPair.setObjOverlap(collVector);
}

cVector2 cCollTest::collTestPolyPoly (const cCollObj& obj1, const cCollObj& obj2) {
	std::vector<cVector2> normList;
	const cCollShape* shape1 = obj1.getCollShape(),
		  *shape2 = obj2.getCollShape();
	genNormList(shape1->getNormList(),shape2->getNormList(),&normList);
	std::vector<cVector2> overlapList;
	for (auto& normListItr : normList) {
		double obj1Min, obj1Max, obj2Min, obj2Max;
		obj1Min = obj2Min = 99999999.0;
		obj1Max = obj2Max = -9999999.0;
		cVector2 obj1Pos = obj1.getObjPos(),
				 obj2Pos = obj2.getObjPos();
		for (auto& obj1PtItr : shape1->getData()) {
			cVector2 ptPos = obj1PtItr+obj1Pos;
			double projValue = vScalProj(ptPos,normListItr);
			if (projValue < obj1Min)
				obj1Min = projValue;
			if (projValue > obj1Max)
				obj1Max = projValue;
		}
		for (auto& obj2PtItr : shape2->getData()) {
			cVector2 ptPos = obj2PtItr+obj2Pos;
			double projValue = vScalProj(ptPos,normListItr);
			if (projValue < obj2Min)
				obj2Min = projValue;
			if (projValue > obj2Max)
				obj2Max = projValue;
		}
		if (obj1Max > obj2Max) {
			if (obj1Min > obj2Max)
				return noColl_;
			overlapList.push_back(cVector2((obj2Max-obj1Min)*normListItr));
		}
		else if (obj2Max > obj1Max) {
			if (obj2Min > obj1Max)
				return noColl_;
			overlapList.push_back(cVector2((obj1Max-obj2Min)*normListItr));
		}
	}
	cVector2 collVector = *overlapList.begin();
	double collVectorMag = vSqMagnitude(collVector);
	for (std::size_t i = 1; i < overlapList.size(); ++i) {
		if (vSqMagnitude(overlapList.at(i)) < collVectorMag) {
			collVector = overlapList.at(i);
			collVectorMag = vSqMagnitude(overlapList.at(i));
		}
	}
	return collVector;
}

void genNormList (const std::vector<cVector2>& nList1,
		const std::vector<cVector2>& nList2, std::vector<cVector2>* finNList) {
	if (nList1.size() == 0 && nList2.size() != 0) {
		*finNList = nList2;
		return;
	}
	else if (nList1.size() != 0 && nList2.size() == 0) {
		*finNList = nList1;
		return;
	}
	*finNList = nList1;
	for (auto& nList2Itr : nList2) {
		bool uniqueNorm = true;
		for (auto& nList1Itr :nList1) {
			if (nList1Itr == nList2Itr)
				uniqueNorm = false;
		}
		if (uniqueNorm == true)
			finNList->push_back(nList2Itr);
	}
}



/*
cVector2 cCollTest::collTestAabbAabb (const cCollObj& obj1,
		const cCollObj& obj2) {
	const cCollAabb* shapeAabb1 = static_cast<const cCollAabb*>(obj1.getCollShape());
	const cCollAabb* shapeAabb2 = static_cast<const cCollAabb*>(obj2.getCollShape());

	std::vector<cVector2> normList = {cVector2(1,0),cVector2(0,1)};
}
*/




/*
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
	cVector2 intrsctPt = intersectionLineLine(aabb.getObjPos(),vNormal(lineDir),
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
	return cVector2(-1*collTestAabbLine(aabb,line));
}

cVector2 cCollTest::collTestLineLine (const cCollObj& line1,
		const cCollObj& line2) {
	return noColl_;
}
*/
