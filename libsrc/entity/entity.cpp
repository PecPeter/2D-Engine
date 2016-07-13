#include "entity.hpp"

cEntity::cEntity (int id, const eEntityType& type, const cPosComp& pos,
		const std::vector<const cEntityNode*>& entityNodeList, void* usrPtr) :
		id_(id), type_(type), entityPos_(pos),
		entityNodeList_(entityNodeList), usrPtr_(usrPtr) {}

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
const std::vector<const cEntityNode*>& cEntity::getNodes (void) const {
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
