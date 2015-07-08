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
/*	cCollShape* objectShape = nullptr;
	int listSize = shapeList_.size();
	for (int i = 0; i < listSize; ++i) {
		cCollShape* tmpShape = &(shapeList_.at(i));
		if (shape == *tmpShape) {
			objectShape = tmpShape;
			break;
		}
	}
	if (objectShape == nullptr) {
		shapeList_.push_back(shape);
		objectShape = &(*(shapeList_.rbegin()));
	}
	cCollObject2D* collObject = new cCollObject2D(pos,objectShape,objectType);
	collObjList_.push_back(collObject);*/
	return nullptr;
}

const cCollShape& cCollWorld::getShape (int shapeIndex) const {
	return shapeList_.at(shapeIndex);
}
