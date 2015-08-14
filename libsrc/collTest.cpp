#include "collTest.hpp"

cCollTest::cCollTest (void): noColl_(std::nan(""),std::nan("")), contactColl_(0,0) {
	collTestMap_[collTestMapKey(eShapeType::POLY,eShapeType::POLY)] =
		&cCollTest::collTestPolyPoly;
	collTestMap_[collTestMapKey(eShapeType::POLY,eShapeType::CIRCLE)] = 
		&cCollTest::collTestPolyCircle;
	collTestMap_[collTestMapKey(eShapeType::CIRCLE,eShapeType::POLY)] = 
		&cCollTest::collTestCirclePoly;
	collTestMap_[collTestMapKey(eShapeType::CIRCLE,eShapeType::CIRCLE)] =
		&cCollTest::collTestCircleCircle;
}

void cCollTest::testPair (cCollPair& collPair) {
	const cCollObj* obj1 = collPair.obj1(),
		  *obj2 = collPair.obj2();
	eShapeType shape1 = obj1->getCollShape()->getShapeType(),
			   shape2 = obj2->getCollShape()->getShapeType();
	auto& function = collTestMap_.at(collTestMapKey(shape1,shape2));
	cVector2 collVector = (this->*function)(*obj1,*obj2);

	if (collVector == noColl_)
		collPair.setCollType(eCollType::NO_COLLISION);
	else if (collVector == contactColl_)
		collPair.setCollType(eCollType::CONTACT);
	else
		collPair.setCollType(eCollType::COLLISION);
	collPair.setObjOverlap(collVector);
}

cVector2 cCollTest::collTestPolyPoly (const cCollObj& objPoly1, const cCollObj& objPoly2) {
	std::vector<cVector2> normList;
	const cCollShape* polyShape1 = objPoly1.getCollShape(),
		  *polyShape2 = objPoly2.getCollShape();
	genNormList(polyShape1->getNormList(),polyShape2->getNormList(),&normList);

	//Update shape data to account for obj position and rotation
	std::vector<cVector2> ptList1 = objPoly1.getCollShape()->getData(),
		ptList2 = objPoly2.getCollShape()->getData();
	cVector2 obj1Pos = objPoly1.getObjPos(),
			 obj2Pos = objPoly2.getObjPos();
	if (objPoly1.getRotation() != 0) {
		cMatrix rotnMatrix = solveRotationMatrix(objPoly1.getRotation());
		for (auto& ptListItr : ptList1)
			ptListItr = rotnMatrix*ptListItr+obj1Pos;
	}
	else
		for (auto& ptListItr : ptList1)
			ptListItr += obj1Pos;
	if (objPoly2.getRotation() != 0) {
		cMatrix rotnMatrix = solveRotationMatrix(objPoly2.getRotation());
		for (auto& ptListItr : ptList2)
			ptListItr = rotnMatrix*ptListItr+obj2Pos;
	}
	else
		for (auto& ptListItr : ptList2)
			ptListItr += obj2Pos;

	//Test for overlap
	std::vector<cVector2> overlapList;
	for (auto& normListItr : normList) {
		double obj1Min, obj1Max, obj2Min, obj2Max;
		obj1Min = obj2Min = std::numeric_limits<double>::max();
		obj1Max = obj2Max = -obj1Min;
		for (auto& ptListItr : ptList1) {
			double projValue = vScalProj(ptListItr,normListItr);
			if (projValue < obj1Min)
				obj1Min = projValue;
			if (projValue > obj1Max)
				obj1Max = projValue;
		}
		for (auto& ptListItr: ptList2) {
			double projValue = vScalProj(ptListItr,normListItr);
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

	//If no SA found, return that which has the smallest displacement
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

cVector2 cCollTest::collTestPolyCircle (const cCollObj& objPoly, const cCollObj& objCircle) {
	// Create norm list
	// Find the closest poly vertex to the centroid of a circle,
	// add the centroid->vertex as an axis to test for collision
	std::vector<cVector2> normList = objPoly.getCollShape()->getNormList();
	const cCollShape* circleShape = objCircle.getCollShape();

	//Update shape data to account for obj position and rotation
	std::vector<cVector2> polyPtList = objPoly.getCollShape()->getData();
	cVector2 polyPos = objPoly.getObjPos();
	if (objPoly.getRotation() != 0) {
		cMatrix rotnMatrix = solveRotationMatrix(objPoly.getRotation());
		for (auto& ptListItr : polyPtList)
			ptListItr = rotnMatrix*ptListItr+polyPos;
	}
	else
		for (auto& ptListItr : polyPtList)
			ptListItr += polyPos;

	//Test distance to each poly point
	cVector2 satAxis;
	double ptDistance = std::numeric_limits<double>::max();
	for (auto& polyPtItr : polyPtList) {
		cVector2 tempAxis = objCircle.getObjPos()-polyPtItr;
		double distance = vSqMagnitude(tempAxis);
		if (distance < ptDistance) {
			ptDistance = distance;
			satAxis = tempAxis;
		}
	}
	normList.push_back(vUnitVector(satAxis));

	// Test each norm
	std::vector<cVector2> overlapList;
	for (auto& normListItr : normList) {
		double polyMin, polyMax, circleMin, circleMax;
		polyMin = circleMin = std::numeric_limits<double>::max();
		polyMax = circleMax = -polyMin;
		for (auto& polyPtItr : polyPtList) {
			double projValue = vScalProj(polyPtItr,normListItr);
			if (projValue < polyMin)
				polyMin = projValue;
			if (projValue > polyMax)
				polyMax = projValue;
		}
		double circleRadius = circleShape->getData().at(0).getX();
		double circlePos = vScalProj(objCircle.getObjPos(),normListItr);
		circleMin = circlePos-circleRadius;
		circleMax = circlePos+circleRadius;
		if (circleMin > circleMax)
			std::swap(circleMin,circleMax);

		if (polyMax > circleMax) {
			if (polyMin > circleMax)
				return noColl_;
			overlapList.push_back(cVector2((circleMax-polyMin)*normListItr));
		}
		else if (circleMax > polyMax) {
			if (circleMin > polyMax)
				return noColl_;
			overlapList.push_back(cVector2((circleMin-polyMax)*normListItr));
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

cVector2 cCollTest::collTestCirclePoly (const cCollObj& objCircle, const cCollObj& objPoly) {
	cVector2 collVector = collTestPolyCircle(objPoly,objCircle);
	if (collVector == noColl_ || collVector == contactColl_)
		return collVector;
	return (-1*collVector);
}

cVector2 cCollTest::collTestCircleCircle (const cCollObj& objCircle1, const cCollObj& objCircle2) {
	cVector2 obj1Pos = objCircle1.getObjPos(),
			 obj2Pos = objCircle2.getObjPos();
	double obj1Rad = objCircle1.getCollShape()->getData().at(0).getX(),
		   obj2Rad = objCircle2.getCollShape()->getData().at(0).getX();
	cVector2 satAxis = vUnitVector(obj2Pos-obj1Pos);
	double obj1Min = vScalProj(obj1Pos,satAxis)-obj1Rad,
		   obj1Max = vScalProj(obj1Pos,satAxis)+obj1Rad,
		   obj2Min = vScalProj(obj2Pos,satAxis)-obj2Rad,
		   obj2Max = vScalProj(obj2Pos,satAxis)+obj2Rad;

	if (obj1Min > obj1Max)
		std::swap(obj1Min,obj1Max);
	if (obj2Min > obj2Max)
		std::swap(obj2Min,obj2Max);

	cVector2 collVector;
	if (obj1Max > obj2Max) {
		if (obj1Min > obj2Max)
			return noColl_;
		collVector = cVector2((obj2Max-obj1Min)*satAxis);
	}
	else if (obj2Max > obj1Max) {
		if (obj2Min > obj1Max)
			return noColl_;
		collVector = cVector2((obj2Min-obj1Max)*satAxis);
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
