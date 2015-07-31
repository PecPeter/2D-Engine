#include "collWorld.hpp"

cCollWorld::cCollWorld (const cCollBroadphase* broadphase):
	broadphase_(broadphase), testHandler_(new cCollTestHandler()),
	debugDrawer_(nullptr) {}

cCollWorld::~cCollWorld (void) {
	collObjList_.clear();
	collPairList_.clear();
	delete testHandler_;
}

cCollObj* cCollWorld::createObject (const cVector2& pos,
		const cCollShape& shape, eObjType objType) {
	cCollObj* collObject = new cCollObj(pos,&shape,objType);
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

void cCollWorld::drawDebugWorld (SDL_Renderer* renderer) {
	if (debugDrawer_ != nullptr) {
		for (auto& itr : collObjList_) {
			cVector3 colour;
			if (itr->getObjType() == eObjType::STATIC) {
				colour.set(0,0) = 0;
				colour.set(1,0) = 1;
				colour.set(2,0) = 0;
			}
			else {
				colour.set(0,0) = 0;
				colour.set(1,0) = 0;
				colour.set(2,0) = 1;
			}
			eShapeType shapeType = itr->getCollShape()->getShapeType();
			if (shapeType == eShapeType::AABB) {
				const cCollAabb* shape =
					static_cast<const cCollAabb*>(itr->getCollShape());
				debugDrawer_->drawRect(renderer,itr->getObjPos(),
						shape->getHW(),shape->getHH(),colour);
			}
		}
	}
}
