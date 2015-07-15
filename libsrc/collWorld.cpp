#include "collWorld.hpp"

cCollWorld::cCollWorld (const cCollBroadphase* broadphase): broadphase_(broadphase) {
	testHandler_ = new cCollTestHandler();
}

cCollWorld::~cCollWorld (void) {
	delete testHandler_;
	shapeList_.clear();
	collObjList_.clear();
}

cCollObject2D* cCollWorld::createObject (const cVector2& pos, const cCollShape& shape,
		eObjectType objectType) {
	cCollShape* objectShape = nullptr;
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
	collObjList_.push_back(collObject);
	return collObject;
}

void cCollWorld::checkColls (void) {
	// Run broadphase
	broadphase_->genList(collPairList_,collObjList_);
	// Run narrow phase
	for (auto qItr : collPairList_)
		testHandler_->testPair(qItr);
}
