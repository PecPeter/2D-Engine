#include "entity.hpp"

cEntity::cEntity (int id, const eEntityType& type, const cPosComp& pos,
		const cEntityNode& entityNode, int entityMask, void* usrPtr) :
		cEntity(id,type,pos,std::vector<cEntityNode>(1,entityNode),
				entityMask,usrPtr) {}

cEntity::cEntity (int id, const eEntityType& type, const cPosComp& pos,
		const std::vector<cEntityNode>& entityNodeList, int entityMask,
		void* usrPtr) :
		id_(id), type_(type), entityPos_(pos),
		entityNodeList_(entityNodeList),
		entityMask_(entityMask),
		usrPtr_(usrPtr)
{
	for (const auto& itr : entityNodeList_)
	{
		entityNodeActivityMap_[itr.getId()] = true;
	}
}

cEntity::~cEntity (void) {}

int cEntity::getId (void) const {
	return id_;
}

// Entity Position
void cEntity::translate (double dx, double dy) {
	entityPos_.addPos(dx,dy);
}

void cEntity::translate (const cVector2& dv) {
	entityPos_.addPos(dv);
}

void cEntity::setPos (double x, double y) {
	entityPos_.setPos(x,y);
}

void cEntity::setPos (const cVector2& v) {
	entityPos_.setPos(v);
}

const cVector2& cEntity::getPos (void) const {
	return entityPos_.getPos();
}

// Entity Rotation
void cEntity::rotate (double rotnRad) {
	entityPos_.addRotn(rotnRad);
}

void cEntity::setRotn (double rotnRad) {
	entityPos_.setRotn(rotnRad);
}

double cEntity::getRotn (void) const {
	return entityPos_.getRotn();
}

// Entity Position Component
const cPosComp& cEntity::getPosComp (void) const {
	return entityPos_;
}

// Entity Transforms
void cEntity::translateRotate (double dx, double dy, double rotnRad) {
	translate(dx,dy);
	rotate(rotnRad);
}

void cEntity::translateRotate (const cVector2& dv, double rotnRad) {
	translate(dv);
	rotate(rotnRad);
}

void cEntity::translateRotate (const cPosComp& posComp) {
	translate(posComp.getPos());
	rotate(posComp.getRotn());
}

void cEntity::setPosRotn (double x, double y, double rotnRad) {
	setPos(x,y);
	setRotn(rotnRad);
}

void cEntity::setPosRotn (const cVector2& v, double rotnRad) {
	setPos(v);
	setRotn(rotnRad);
}

void cEntity::setPosRotn (const cPosComp& posComp) {
	setPos(posComp.getPos());
	setRotn(posComp.getRotn());
}

// Entity Node
const std::vector<cEntityNode>& cEntity::getNodes (void) const {
	return entityNodeList_;
}

// Entity Type
eEntityType cEntity::getType (void) const {
	return type_;
}

// Entity Collision Mask
void cEntity::setMask (int entityMask) {
	entityMask_ = entityMask;
}

int cEntity::getMask (void) const {
	return entityMask_;
}

// Collision Callback Information
void cEntity::setCollCallback (collCallbackFunc collCallback) {
	collCallback_ = collCallback;
}

void cEntity::collCallback (cEntity* entity1, cEntity* entity2,
		int structId1, int structId2, const cVector2& collVector) {
	if (collCallback_ != nullptr)
		collCallback_(entity1,entity2,structId1,structId2,collVector);
}

// Additional Entity Information
void cEntity::setUsrPtr (void* usrPtr) {
	usrPtr_ = usrPtr;
}

void* cEntity::getUsrPtr (void) const {
	return usrPtr_;
}

// Entity activity function
bool cEntity::getActivity (void) const
{
	for (const auto& itr : entityNodeActivityMap_)
	{
		if (itr.second == true)
		{
			return true;
		}
	}
	return false;
}

void cEntity::setNodeActivity (int nodeId, bool nodeActivity)
{
	int entityNodeIndex = 0;
	for (auto& nodeItr : getNodes())
	{
		if (nodeItr.getId() == nodeId)
		{
			entityNodeActivityMap_.at(entityNodeIndex) = nodeActivity;
			break;
		}
		++entityNodeIndex;
	}
}

bool cEntity::getNodeActivity (int nodeId) const
{
	return entityNodeActivityMap_.at(nodeId);
}

std::map<int,cPosComp> getNodeOffset (const std::vector<cEntityNode>& nodeList) {
	std::map<int,cPosComp> nodeOffsetMap;

	for (const auto& itr : nodeList) {
		cPosComp parentOffset(0,0,0),
				 nodeOffset(0,0,0);
		if (itr.getParentId() != 0)
			parentOffset = nodeOffsetMap.at(itr.getParentId());
		nodeOffsetMap[itr.getId()] = cPosComp(0,0,0);
		cVector2 posOffset = parentOffset.getPos()
						   + itr.getPosComp().getPos();
		double rotnOffset = parentOffset.getRotn()
						  + itr.getPosComp().getRotn();
		nodeOffsetMap[itr.getId()].setPos(posOffset);
		nodeOffsetMap[itr.getId()].setRotn(rotnOffset);
	}
	return nodeOffsetMap;
}
