#include "collWorld.hpp"

cCollWorld::cCollWorld (const std::shared_ptr<cCollBroadphase>& broadphase) :
		broadphase_(broadphase) {
	assert((broadphase != nullptr || broadphase != NULL) && "Broadphase is not set.");
}

cCollWorld::~cCollWorld (void) {
/*	for (auto itr : collObjListStatic_)
		delete itr;
	for (auto itr : collObjListDyn_)
		delete itr;
	collObjListStatic_.clear();
	collObjListDyn_.clear();
	collPairList_.clear();
	delete testHandler_;
*/
}

std::shared_ptr<cCollObj> cCollWorld::createObject (const cVector2& pos,
		const std::shared_ptr<const cCollShape>& genShape, eObjType objType,
		const std::shared_ptr<const sCollShapeNode>& accShape, void* usrPtr) {
	std::shared_ptr<cCollObj> collObj = 
		std::make_shared<cCollObj>(pos,genShape,objType,accShape,usrPtr);
	if (objType == eObjType::STATIC)
		collObjListStatic_.push_back(collObj);
	else if (objType == eObjType::DYNAMIC)
		collObjListDyn_.push_back(collObj);
	return collObj;
}
/*
void cCollWorld::removeObject (void) {

}
*/
std::forward_list<cCollPair>* cCollWorld::checkColls (void) {
	collPairList_.empty();
	// Run broadphase
	if (broadphase_.expired() == false) {
		broadphase_.lock()->genList(collPairList_,
				collObjListDyn_,collObjListStatic_);
	}
	else {
		// Throw an error saying the broadphase has been deleted
	}
	// Run narrow phase
	for (auto& qItr : collPairList_)
		testHandler_.testPair(qItr);
	collPairList_.remove_if([](const cCollPair& pair) {
			return pair.getCollType() == eCollType::NO_COLLISION ? true : false;
			});
	return &collPairList_;
}

void cCollWorld::setDebugDraw (const std::shared_ptr<cCollDebugDrawer>&
		debugDrawer) {
	debugDrawer_ = debugDrawer;
}

void cCollWorld::drawDebugWorld (SDL_Renderer* renderer) {
	if (debugDrawer_.expired() == false) {
		for (auto& itr : collObjListStatic_) {
			debugDrawer_.lock()->drawObj(renderer,*itr);
		}
		for (auto& itr : collObjListDyn_) {
			debugDrawer_.lock()->drawObj(renderer,*itr);
		}
	}
}

void cCollWorld::addCollMask (int objMask, int collMask) {
	if (auto broadphase = broadphase_.lock()) {
		broadphase->addCollMask(objMask,collMask);
	}
	else {
		// Throw an error saying the broadphase has been deleted
	}
}
