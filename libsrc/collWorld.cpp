#include "collWorld.hpp"

cCollWorld::cCollWorld (const cCollBroadphase* broadphase):
	broadphase_(broadphase), testHandler_(new cCollTestHandler()),
	debugDrawer_(nullptr) {}

cCollWorld::~cCollWorld (void) {
	collObjList_.clear();
	collPairList_.clear();
	delete testHandler_;
}

cCollObject2D* cCollWorld::createObject (const cVector2& pos,
		const cCollShape& shape, eObjectType objectType) {
	cCollObject2D* collObject = new cCollObject2D(pos,&shape,objectType);
	collObjList_.push_back(collObject);
	return collObject;
}
/*
void cCollWorld::removeObject (void) {

}
*/
void cCollWorld::checkColls (void) {
	// Run broadphase
	broadphase_->genList(collPairList_,collObjList_);
	// Run narrow phase
	for (auto qItr : collPairList_)
		testHandler_->testPair(qItr);
}

void cCollWorld::setDebugDraw (cCollDebugDrawer* debugDrawer) {
	debugDrawer_ = debugDrawer;
}

void cCollWorld::drawDebugWorld (void) {
	if (debugDrawer_ != nullptr) {
		for (auto& itr : collObjList_) {
			cVector3 colour;
			if (itr->getObjectType() == eObjectType::STATIC) {
				colour.set(0,0) = 0;
				colour.set(1,0) = 1;
				colour.set(2,0) = 0;
			}
			else {
				colour.set(0,0) = 0;
				colour.set(1,0) = 0;
				colour.set(2,0) = 1;
			}
			debugDrawer_->drawShape(*(itr->getCollShape()),colour);
		}
	}
}
