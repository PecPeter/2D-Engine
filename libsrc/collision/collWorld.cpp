#include "collWorld.hpp"

cCollWorld::cCollWorld (const std::shared_ptr<cCollBroadphase>& broadphase) :
		broadphase_(broadphase), numEntities_(0) {
	assert((broadphase != nullptr || broadphase != NULL) && "Broadphase is not set.");
}

cCollWorld::~cCollWorld (void) {
/*	for (auto itr : collEntListStatic_)
		delete itr;
	for (auto itr : collEntListDyn_)
		delete itr;
	collEntListStatic_.clear();
	collEntListDyn_.clear();
	collPairList_.clear();
	delete testHandler_;
*/
}

std::shared_ptr<cEntity> cCollWorld::createEntity (const eEntityType& type,
		const cPosComp& pos, const std::vector<cEntityNode>& entityNodeList,
		void* userPtr) {
	std::shared_ptr<cEntity> entity = 
		std::make_shared<cEntity>(numEntities_,type,pos,entityNodeList,userPtr);
	++numEntities_;
	switch(entity->getState()) {
		case eEntityState::STATIC: 
			collEntListStatic_.push_back(entity);
			break;
		case eEntityState::DYNAMIC:
		case eEntityState::KINEMATIC:
			collEntListDyn_.push_back(entity);
			break;
		default:
			break;
	}
	return entity;
}

void cCollWorld::removeEntity (int entityId) {
	for (entListCont::iterator itr = collEntListStatic_.begin();
			itr != collEntListStatic_.end(); ++itr) {
		if ((*itr)->getId() == entityId) {
			std::iter_swap(itr,collEntListStatic_.end());
			collEntListStatic_.pop_back();
			return;
		}
	}
	for (entListCont::iterator itr = collEntListDyn_.begin();
			itr != collEntListDyn_.end(); ++itr) {
		if ((*itr)->getId() == entityId) {
			std::iter_swap(itr,collEntListDyn_.end());
			collEntListDyn_.pop_back();
			return;
		}
	}
}

void cCollWorld::removeShape (int shapeId) {}

std::forward_list<cCollPair>* cCollWorld::checkColls (void) {
	collPairList_.empty();
	// Run broadphase
	if (broadphase_.expired() == false) {
		broadphase_.lock()->genList(collPairList_,
				collEntListDyn_,collEntListStatic_);
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
		for (auto& itr : collEntListStatic_) {
			debugDrawer_.lock()->drawEnt(renderer,*itr);
		}
		for (auto& itr : collEntListDyn_) {
			debugDrawer_.lock()->drawEnt(renderer,*itr);
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
