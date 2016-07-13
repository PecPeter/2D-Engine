#include "collWorld.hpp"

cCollWorld::cCollWorld (const std::shared_ptr<cCollBroadphase>& broadphase) :
		broadphase_(broadphase), numEntities_(0) {
	assert((broadphase != nullptr || broadphase != NULL) && "Broadphase is not set.");
}

cCollWorld::~cCollWorld (void) {
/*	for (auto itr : entityListStatic_)
		delete itr;
	for (auto itr : entityListDyn_)
		delete itr;
	entityListStatic_.clear();
	entityListDyn_.clear();
	collPairList_.clear();
	delete testHandler_;
*/
}

const cEntity& cCollWorld::createEntity (const eEntityType& type,
		const cPosComp& pos, const std::vector<cEntityNode>& entityNode,
		void* userPtr) {
	entityListCont* entityList = nullptr;
	switch (type) {
		case eEntityType::STATIC: entityList = &entityListStatic_; break;
		case eEntityType::DYNAMIC:
		case eEntityType::KINEMATIC: entityList = &entityListDyn_; break;
		default: break;
	}
	entityList->push_back(
		std::make_unique<cEntity>(numEntities_,type,pos,entityNode,userPtr));
	++numEntities_;
	return *((*(entityList->end())).get());
}

void cCollWorld::removeEntity (int entityId) {
	for (entityListCont::iterator itr = entityListStatic_.begin();
			itr != entityListStatic_.end(); ++itr) {
		if ((*itr)->getId() == entityId) {
			std::iter_swap(itr,entityListStatic_.end());
			entityListStatic_.pop_back();
			return;
		}
	}
	for (entityListCont::iterator itr = entityListDyn_.begin();
			itr != entityListDyn_.end(); ++itr) {
		if ((*itr)->getId() == entityId) {
			std::iter_swap(itr,entityListDyn_.end());
			entityListDyn_.pop_back();
			return;
		}
	}
}
/*
const cEntityNode* cCollWorld::createEntityNode (void) {
	return nullptr;
}

void cCollWorld::removeEntityNode (int entityNodeId) {

}

const cCollShape* cCollWorld::createCollShape (void) {
	return nullptr;
}

void cCollWorld::removeCollShape (int shapeId) {

}
*/
std::forward_list<cCollPair>* cCollWorld::checkColls (void) {
	collPairList_.empty();
	// Run broadphase
	if (broadphase_.expired() == false) {
		broadphase_.lock()->genList(collPairList_,
				entityListDyn_,entityListStatic_);
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
		for (auto& itr : entityListStatic_) {
			debugDrawer_.lock()->drawEnt(renderer,*itr);
		}
		for (auto& itr : entityListDyn_) {
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
