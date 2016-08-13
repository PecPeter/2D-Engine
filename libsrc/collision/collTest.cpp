#include "collTest.hpp"

sCollShapeInfo::sCollShapeInfo (const cPosComp& parentPosComp,
		const cPosComp& shapePosComp, const cCollComp& collComp):
		parentPosComp_(parentPosComp), shapePosComp_(shapePosComp),
		collComp_(collComp) {}

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

bool cCollTest::testPair (cCollPair& collPair) {
	// Clear the previous collisions
	collPair.resetCollisions();

	cVector2 collVector(noColl_);
	const cEntity* ent1 = &collPair.ent1(),
				 * ent2 = &collPair.ent2();
	bool isCollision = false;
	if (ent1 != nullptr && ent2 != nullptr) {
		const std::vector<cEntityNode>& nodesList1 = ent1->getNodes(),
									  & nodesList2 = ent2->getNodes();

		// Calculate the node offsets for collision testing
		std::map<int, cPosComp> nodeOffset1 = getNodeOffset(nodesList1),
								nodeOffset2 = getNodeOffset(nodesList2);
		// Iterate through the lists and test each node
		for (const auto& itr1 : nodesList1) {
			for (const auto& itr2 : nodesList2) {
				// Check if there was a collision
				// TODO: Once implemented, check if the node is active or not...
				sCollShapeInfo shapeInfo1(ent1->getPosComp(),
										  nodeOffset1.at(itr1.getId()),
										  itr1.getCollComp()),
							   shapeInfo2(ent2->getPosComp(),
										  nodeOffset2.at(itr2.getId()),
				 						  itr2.getCollComp());
				eShapeType shapeType1 =
						shapeInfo1.collComp_.getCollShape().getShapeType(),
						   shapeType2 = 
						shapeInfo2.collComp_.getCollShape().getShapeType();
				auto& collFunc = collTestMap_.at(collTestMapKey(shapeType1,
							shapeType2));
				collVector = ((this->*collFunc)(shapeInfo1,shapeInfo2));

				if (collVector != noColl_) {
					// Collision detected, add it to the pair's list
					isCollision = true;
					eCollType collType;
					if (collVector == contactColl_)
						collType = eCollType::CONTACT;
					else
						collType = eCollType::COLLISION;
					collPair.addCollision(itr1.getId(),itr2.getId(),collVector,
							collType);
				}
			}
		}
	}
	return isCollision;
}

cVector2 cCollTest::collTestPolyPoly (const sCollShapeInfo& objPoly1,
		const sCollShapeInfo& objPoly2) {
	std::vector<cVector2> normList;
	const cCollShape& shape1 = objPoly1.collComp_.getCollShape(),
			   		& shape2 = objPoly2.collComp_.getCollShape();
	genNormList(shape1.getNormList(),shape2.getNormList(),&normList);

	//Update shape data to account for obj position and rotation
	std::vector<cVector2> ptList1 = shape1.getData(),
						  ptList2 = shape2.getData();
	cPosComp objPos1 = objPoly1.parentPosComp_ + objPoly1.shapePosComp_,
			 objPos2 = objPoly2.parentPosComp_ + objPoly2.shapePosComp_;
	if (objPos1.getRotn() != 0) {
		cMatrix rotnMatrix = rotnTransform(objPos1.getRotn());
		for (auto& ptListItr : ptList1)
			ptListItr = rotnMatrix*ptListItr+objPos1.getPos();
	}
	else
		for (auto& ptListItr : ptList1)
			ptListItr += objPos1.getPos();
	if (objPos2.getRotn() != 0) {
		cMatrix rotnMatrix = rotnTransform(objPos2.getRotn());
		for (auto& ptListItr : ptList2)
			ptListItr = rotnMatrix*ptListItr+objPos2.getPos();
	}
	else
		for (auto& ptListItr : ptList2)
			ptListItr += objPos2.getPos();

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
	const cCollShape& poly = objPoly.collComp_.getCollShape(),
			   		& circle = objCircle.collComp_.getCollShape();
	// Create norm list
	// Find the closest poly vertex to the centroid of a circle,
	// add the centroid->vertex as an axis to test for collision
	std::vector<cVector2> normList = poly.getNormList();

	//Update shape data to account for obj position and rotation
	std::vector<cVector2> polyPtList = poly.getData();
	cPosComp polyPos = objPoly.parentPosComp_ + objPoly.shapePosComp_;
	if (polyPos.getRotn() != 0) {
		cMatrix rotnMatrix = rotnTransform(polyPos.getRotn());
		for (auto& ptListItr : polyPtList)
			ptListItr = rotnMatrix*ptListItr+polyPos.getPos();
	}
	else
		for (auto& ptListItr : polyPtList)
			ptListItr += polyPos.getPos();

	//Test distance to each poly point
	cVector2 satAxis;
	cPosComp circlePos = objCircle.parentPosComp_ + objCircle.shapePosComp_;
	double ptDistance = std::numeric_limits<double>::max();
	for (auto& polyPtItr : polyPtList) {
		cVector2 tempAxis = circlePos.getPos()-polyPtItr;
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
		double radius = circle.getData().at(0).getX();
		double pos = vScalProj(circlePos.getPos(),normListItr);
		circleMin = pos-radius;
		circleMax = pos+radius;
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
	const cCollShape& circle1 = objCircle1.collComp_.getCollShape(),
			   		& circle2 = objCircle2.collComp_.getCollShape();

	cPosComp obj1Pos = objCircle1.parentPosComp_ + objCircle1.shapePosComp_,
			 obj2Pos = objCircle2.parentPosComp_ + objCircle2.shapePosComp_;
	double obj1Rad = circle1.getData().at(0).getX(),
		   obj2Rad = circle2.getData().at(0).getX();
	cVector2 satAxis = vUnitVector((obj2Pos-obj1Pos).getPos());
	double obj1Min = vScalProj(obj1Pos.getPos(),satAxis)-obj1Rad,
		   obj1Max = vScalProj(obj1Pos.getPos(),satAxis)+obj1Rad,
		   obj2Min = vScalProj(obj2Pos.getPos(),satAxis)-obj2Rad,
		   obj2Max = vScalProj(obj2Pos.getPos(),satAxis)+obj2Rad;

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
