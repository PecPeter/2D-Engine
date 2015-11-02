#include "collWorld.hpp"

cCollWorld::cCollWorld (cCollBroadphase* broadphase):
		broadphase_(broadphase), testHandler_(new cCollTest()),
		debugDrawer_(nullptr) {
	assert((broadphase != nullptr || broadphase != NULL) && "Broadphase is not set.");
}

cCollWorld::~cCollWorld (void) {
	for (auto itr : collObjListStatic_)
		delete itr;
	for (auto itr : collObjListDyn_)
		delete itr;
	collObjListStatic_.clear();
	collObjListDyn_.clear();
	collPairList_.clear();
	delete testHandler_;
}

cCollObj* cCollWorld::createObject (const cVector2& pos,
		const cCollShape& shape, eObjType objType) {
	cCollObj* collObject = new cCollObj(pos,&shape,objType);
	if (objType == eObjType::STATIC)
		collObjListStatic_.push_back(collObject);
	else if (objType == eObjType::DYNAMIC)
		collObjListDyn_.push_back(collObject);
	return collObject;
}
/*
void cCollWorld::removeObject (void) {

}
*/
std::forward_list<cCollPair>* cCollWorld::checkColls (void) {
	collPairList_.empty();
	// Run broadphase
	broadphase_->genList(collPairList_,collObjListDyn_,collObjListStatic_);
	// Run narrow phase
	for (auto& qItr : collPairList_)
		testHandler_->testPair(qItr);
	collPairList_.remove_if([](const cCollPair& pair) {
			return pair.getCollType() == eCollType::NO_COLLISION ? true : false;
			});
	return &collPairList_;
}

void cCollWorld::setDebugDraw (cCollDebugDrawer* debugDrawer) {
	debugDrawer_ = debugDrawer;
}

void cCollWorld::drawDebugWorld (SDL_Renderer* renderer) {
	if (debugDrawer_ != nullptr) {
		for (auto& itr : collObjListStatic_) {
			debugDrawer_->drawObj(renderer,*itr);
		}
		for (auto& itr : collObjListDyn_) {
			debugDrawer_->drawObj(renderer,*itr);
		}
	}
}

void cCollWorld::addCollMask (int objMask, int collMask) {
	broadphase_->addCollMask(objMask,collMask);
}
