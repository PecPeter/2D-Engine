#include "collWorld.hpp"

cCollWorld::cCollWorld (eBroadphaseType broadphaseType, void* info) :
		broadphase_(nullptr), debugDrawer_(nullptr)
{
	switch (broadphaseType)
	{
		case eBroadphaseType::GENERAL:
			broadphase_ = new cGenBroadphase;
			break;
		case eBroadphaseType::GRID: {
			//TODO: LOOK INTO THROWING AN ERROR IF THE CONVERSION FAILS
			cVector2* worldDim = static_cast<cVector2*>(info);
			broadphase_ = new cGridBroadphase(0,0,worldDim->getX(),
					worldDim->getY());
			break;
		}
		default:
			break;
	}
}

cCollWorld::~cCollWorld (void)
{
	delete broadphase_;
}

cEntity* cCollWorld::createEntity (int id, const cPosComp& pos,
		const cEntityNode& entityNode, const eEntityType& type,
		int entityMask, void* userPtr)
{
	return createEntity(id,pos,std::vector<cEntityNode>(1,entityNode),
			type,entityMask,userPtr);
}

cEntity* cCollWorld::createEntity (int id, const cPosComp& pos,
		const std::vector<cEntityNode>& entityNode,
		const eEntityType& type, int entityMask, void* userPtr)
{
	// Check if the ID is unique
	cEntity* tmpEnt = nullptr;
	tmpEnt = findEntity(id);
	if (tmpEnt != nullptr) {
		tmpEnt = nullptr;
		std::string errorString = "ID: " + std::to_string(id) + 
			" already exists.";
		throw std::invalid_argument(errorString);
	}

	entityListCont* entityList = nullptr;
	switch (type)
	{
		case eEntityType::STATIC:
			entityList = &entityListStatic_;
			break;
		case eEntityType::DYNAMIC:
		case eEntityType::KINEMATIC:
			entityList = &entityListDyn_;
			break;
		default:
			break;
	}
	std::shared_ptr<cEntity> entityPtr = std::make_shared<cEntity>(
			id,type,pos,entityNode,entityMask,userPtr);
	entityList->push_back(entityPtr);
	return entityPtr.get();
}

void cCollWorld::removeEntity (int entityId)
{
	for (entityListCont::iterator itr = entityListStatic_.begin();
			itr != entityListStatic_.end(); ++itr)
	{
		if ((*itr)->getId() == entityId)
		{
			std::iter_swap(itr,entityListStatic_.end());
			entityListStatic_.pop_back();
			return;
		}
	}
	for (entityListCont::iterator itr = entityListDyn_.begin();
			itr != entityListDyn_.end(); ++itr)
	{
		if ((*itr)->getId() == entityId)
		{
			std::iter_swap(itr,entityListDyn_.end());
			entityListDyn_.pop_back();
			return;
		}
	}
}

cEntity* cCollWorld::findEntity (int entityId)
{
	for (entityListCont::iterator itr = entityListStatic_.begin();
			itr != entityListStatic_.end(); ++itr)
	{
		if ((*itr)->getId() == entityId)
		{
			return (*itr).get();
		}
	}
	for (entityListCont::iterator itr = entityListDyn_.begin();
			itr != entityListDyn_.end(); ++itr)
	{
		if ((*itr)->getId() == entityId)
		{
			return (*itr).get();
		}
	}
	return nullptr;
}

std::forward_list<cCollPair> cCollWorld::checkColls (void)
{
	std::forward_list<cCollPair> collPairListTmp, collPairList;
	// Run broadphase
	broadphase_->genList(collPairListTmp,entityListDyn_,entityListStatic_);
	// Run narrow phase
	for (auto& itr : collPairListTmp)
	{
		if (testHandler_.testPair(itr) == true)
		{
			collPairList.push_front(itr);
		}
	}
	return collPairList;
}

cCollBroadphase* cCollWorld::getBroadphase (void)
{
	return broadphase_;
}

void cCollWorld::setDebugDraw (const cCollDebugDrawer& debugDrawer)
{
	*debugDrawer_ = debugDrawer;
}

void cCollWorld::setDebugDraw (cCollDebugDrawer* debugDrawer)
{
	debugDrawer_ = debugDrawer;
}

void cCollWorld::drawDebugWorld (SDL_Renderer* renderer)
{
	for (auto& itr : entityListStatic_)
	{
		debugDrawer_->drawEnt(renderer,*itr);
	}
	for (auto& itr : entityListDyn_)
	{
		debugDrawer_->drawEnt(renderer,*itr);
	}
}

void cCollWorld::addCollMask (int objMask, int collMask)
{
	broadphase_->addCollMask(objMask,collMask);
}
