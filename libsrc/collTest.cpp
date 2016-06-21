#include "collTest.hpp"

cCollTest::cCollTest (void) {
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
	cVector2 collVector(noColl_);
	const cCollObj* obj1 = collPair.obj1(),
				   *obj2 = collPair.obj2();
	std::shared_ptr<const cCollShape> genShape1,
									  genShape2;
	if (obj1->getGenCollShape().expired() == false && 
				obj2->getGenCollShape().expired() == false) {
			genShape1 = obj1->getGenCollShape().lock();
			genShape2 = obj2->getGenCollShape().lock();
		sCollShapeInfo shapeInfo1 = {obj1->getRotation(),
									 obj1->getObjPos(),
									 genShape1},
					   shapeInfo2 = {obj2->getRotation(),
									 obj2->getObjPos(),
									 genShape2};
		eShapeType shape1 = genShape1->getShapeType(),
				   shape2 = genShape2->getShapeType();
		auto& function = collTestMap_.at(collTestMapKey(shape1,shape2));
		collVector = ((this->*function)(shapeInfo1,shapeInfo2));
	}
	if (collVector != noColl_) {
		std::shared_ptr<const sCollShapeNode> accShape1,
											  accShape2;
		if (obj1->getAccCollShape().expired() == false &&
				obj2->getAccCollShape().expired() == false) {
			accShape1 = obj1->getAccCollShape().lock();
			accShape2 = obj2->getAccCollShape().lock();
			if (accShape1 != nullptr) {
				if (accShape2 != nullptr)
					collVector = collTestComplexComplex(*obj1,*obj2,collVector);
				else
					collVector = collTestComplexSimple(*obj1,*obj2,collVector);
			}
			else {
				if (accShape2 != nullptr)
					collVector = collTestSimpleComplex(*obj1,*obj2,collVector);
			}
		}
	}
	if (collVector == noColl_)
		collPair.setCollType(eCollType::NO_COLLISION);
	else if (collVector == contactColl_)
		collPair.setCollType(eCollType::CONTACT);
	else
		collPair.setCollType(eCollType::COLLISION);
	collPair.setObjOverlap(collVector);
}

cVector2 cCollTest::collTestComplexComplex (const cCollObj& objComplex1,
		const cCollObj& objComplex2, const cVector2& collVector) {
	return noColl_;
}

cVector2 cCollTest::collTestSimpleComplex (const cCollObj& objComplex1,
		const cCollObj& objComplex2, const cVector2& collVector) {
	return noColl_;
}

cVector2 cCollTest::collTestComplexSimple (const cCollObj& objComplex1,
		const cCollObj& objComplex2, const cVector2& collVector) {
	return noColl_;
}

cVector2 cCollTest::collTestPolyPoly (const sCollShapeInfo& objPoly1,
		const sCollShapeInfo& objPoly2) {
	std::vector<cVector2> normList;
	genNormList(objPoly1.shape_->getNormList(),objPoly2.shape_->getNormList(),
			&normList);

	//Update shape data to account for obj position and rotation
	std::vector<cVector2> ptList1 = objPoly1.shape_->getData(),
		ptList2 = objPoly2.shape_->getData();
	cVector2 obj1Pos = objPoly1.shapePos_,
			 obj2Pos = objPoly2.shapePos_;
	if (objPoly1.shapeRotn_ != 0) {
		cMatrix rotnMatrix = rotnTransform(objPoly1.shapeRotn_);
		for (auto& ptListItr : ptList1)
			ptListItr = rotnMatrix*ptListItr+obj1Pos;
	}
	else
		for (auto& ptListItr : ptList1)
			ptListItr += obj1Pos;
	if (objPoly2.shapeRotn_ != 0) {
		cMatrix rotnMatrix = rotnTransform(objPoly2.shapeRotn_);
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

		cVector2 dispVector = minDisplacement(obj1Min,obj1Max,
				obj2Min,obj2Max,normListItr);
		if (dispVector == noColl_ || dispVector == contactColl_)
			return dispVector;
		overlapList.push_back(dispVector);
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

cVector2 cCollTest::collTestPolyCircle (const sCollShapeInfo& objPoly,
		const sCollShapeInfo& objCircle) {
	// Create norm list
	// Find the closest poly vertex to the centroid of a circle,
	// add the centroid->vertex as an axis to test for collision
	std::vector<cVector2> normList = objPoly.shape_->getNormList();

	//Update shape data to account for obj position and rotation
	std::vector<cVector2> polyPtList = objPoly.shape_->getData();
	cVector2 polyPos = objPoly.shapePos_;
	if (objPoly.shapeRotn_ != 0) {
		cMatrix rotnMatrix = rotnTransform(objPoly.shapeRotn_);
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
		cVector2 tempAxis = objCircle.shapePos_-polyPtItr;
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
		double circleRadius = objCircle.shape_->getData().at(0).getX();
		double circlePos = vScalProj(objCircle.shapePos_,normListItr);
		circleMin = circlePos-circleRadius;
		circleMax = circlePos+circleRadius;
		if (circleMin > circleMax)
			std::swap(circleMin,circleMax);

		cVector2 dispVector = minDisplacement(polyMin,polyMax,circleMin,
				circleMax,normListItr);
		if (dispVector == noColl_ || dispVector == contactColl_)
			return dispVector;
		overlapList.push_back(dispVector);
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

cVector2 cCollTest::collTestCirclePoly (const sCollShapeInfo& objCircle,
		const sCollShapeInfo& objPoly) {
	cVector2 collVector = collTestPolyCircle(objPoly,objCircle);
	if (collVector == noColl_ || collVector == contactColl_)
		return collVector;
	return (-1*collVector);
}

cVector2 cCollTest::collTestCircleCircle (const sCollShapeInfo& objCircle1,
		const sCollShapeInfo& objCircle2) {
	cVector2 obj1Pos = objCircle1.shapePos_,
			 obj2Pos = objCircle2.shapePos_;
	double obj1Rad = objCircle1.shape_->getData().at(0).getX(),
		   obj2Rad = objCircle2.shape_->getData().at(0).getX();
	cVector2 satAxis = vUnitVector(obj2Pos-obj1Pos);
	double obj1Min = vScalProj(obj1Pos,satAxis)-obj1Rad,
		   obj1Max = vScalProj(obj1Pos,satAxis)+obj1Rad,
		   obj2Min = vScalProj(obj2Pos,satAxis)-obj2Rad,
		   obj2Max = vScalProj(obj2Pos,satAxis)+obj2Rad;

	if (obj1Min > obj1Max)
		std::swap(obj1Min,obj1Max);
	if (obj2Min > obj2Max)
		std::swap(obj2Min,obj2Max);

	return minDisplacement(obj1Min,obj1Max,obj2Min,obj2Max,satAxis);
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
	else if (nList1.size() == 0 && nList2.size() == 0)
		return;
	*finNList = nList1;
	for (auto& nList2Itr : nList2) {
		bool uniqueNorm = true;
		for (auto& nList1Itr : nList1) {
			if (nList1Itr == nList2Itr || -1*nList1Itr == nList2Itr) {
				uniqueNorm = false;
				break;
			}
		}
		if (uniqueNorm == true)
			finNList->push_back(nList2Itr);
	}
}

cVector2 minDisplacement (double obj1Min, double obj1Max, double obj2Min,
		double obj2Max, cVector2 axis) {
	double diff1 = obj2Min-obj1Max,
		   diff2 = obj2Max-obj1Min;
	if (diff1*diff2 < 0) {
		//There's a collision in this state
		if (std::abs(diff1) > std::abs(diff2))
			return cVector2(diff2*axis);
		else
			return cVector2(diff1*axis);
	}
	else if (diff1*diff2 == 0)
		return contactColl_;
	else
		return noColl_;
}
