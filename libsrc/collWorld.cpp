#include "collWorld.hpp"

cCollWorld::cCollWorld (const cCollBroadphase* broadphase):
	broadphase_(broadphase), testHandler_(new cCollTest()),
	debugDrawer_(nullptr) {}

cCollWorld::~cCollWorld (void) {
	for (auto itr : collObjList_)
		delete itr;
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
std::deque<cCollPair>* cCollWorld::checkColls (void) {
	collPairList_.empty();
	// Run broadphase
	broadphase_->genList(collPairList_,collObjList_);
	// Run narrow phase
	for (auto qItr : collPairList_)
		testHandler_->testPair(qItr);
	for (auto qItr : collPairList_)
		if (qItr.getCollType() == eCollType::NO_COLLISION)
			collPairList_.pop_front();
	return &collPairList_;
}

void cCollWorld::setDebugDraw (cCollDebugDrawer* debugDrawer) {
	debugDrawer_ = debugDrawer;
}

void cCollWorld::drawDebugWorld (SDL_Renderer* renderer) {
	if (debugDrawer_ != nullptr) {
		for (auto& itr : collObjList_) {
			debugDrawer_->drawObj(renderer,*itr);
		}
	}
}
