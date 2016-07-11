#include "collPair.hpp"

sCollPairInfo::sCollPairInfo (int entNodeId1, int entNodeId2,
		const cVector2& overlap, const eCollType& collType):
	entNodeId1_(entNodeId1), entNodeId2_(entNodeId2), overlap_(overlap),
	collType_(collType) {}

cCollPair::cCollPair (std::shared_ptr<cEntity> entity1,
		std::shared_ptr<cEntity> entity2) : collType_(eCollType::NO_COLLISION) {
	eEntityState ent1State = entity1->getState(),
				 ent2State = entity2->getState();
	if (ent1State == eEntityState::STATIC 
			&& (ent2State == eEntityState::DYNAMIC
				|| ent2State == eEntityState::KINEMATIC)) {
		entity1_ = entity2;
		entity2_ = entity1;
	}
	else {
		entity1_ = entity1;
		entity2_ = entity2;
	}
}

/*	WHEN YOU CAN GUARANTEE THAT OBJ1 WONT BE STATIC, REMOVE THE COMMENTS AND
 *	THE ABOVE VERSION OF THE CONSTRUCTOR
cCollPair::cCollPair (cCollObj* object1, cCollObj* object2):
		object1_(object1), object2_(object2), collType_(eCollType::NO_COLLISION) {}
*/

cCollPair::~cCollPair (void) {}

std::shared_ptr<cEntity> cCollPair::ent1 (void) const {
	return entity1_.lock();
}

std::shared_ptr<cEntity> cCollPair::ent2 (void) const {
	return entity2_.lock();
}

void cCollPair::setEntOverlap (const cVector2& overlap) {
	overlap_ = overlap;
}

const cVector2& cCollPair::getEntOverlap (void) const {
	return overlap_;
}

void cCollPair::setCollType (const eCollType& collType) {
	collType_ = collType;
}

eCollType cCollPair::getCollType (void) const {
	return collType_;
}

void cCollPair::addCollision (const sCollPairInfo& collInfo) {
	collisionList_.push_back(collInfo);
}
