#include "collWorld.hpp"

cCollWorld::cCollWorld (double worldMinX, double worldMinY, double worldMaxX, double worldMaxY):
	worldDimMin_(worldMinX,worldMinY),worldDimMax_(worldMaxX,worldMaxY) {}

cCollWorld::cCollWorld (const cVector2& worldDimMin, const cVector2& worldDimMax):
	worldDimMin_(worldDimMin),worldDimMax_(worldDimMax) {}

cCollWorld::~cCollWorld (void) {
	shapeList_.clear();
	collObjList_.clear();
}

cCollObject2D* cCollWorld::createObject (const cVector2& pos, const cCollShape& shape,
		eObjectType objectType) {
	int shapeIndex = -1, 
		listSize = shapeList_.size();
	for (int i = 0; i < listSize; ++i) {
		if (shape == shapeList_.at(i)) {
			shapeIndex = i;
			break;
		}
	}
	if (shapeIndex == -1) {
		shapeList_.push_back(shape);
		shapeIndex += shapeList_.size();
	}
	cCollObject2D* collObject = new cCollObject2D(pos,shapeIndex,objectType);
	collObjList_.push_back(collObject);
	return collObject;
}

const cCollShape& cCollWorld::getShape (int shapeIndex) const {
	return shapeList_.at(shapeIndex);
}
