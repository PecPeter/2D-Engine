#include "collPair.hpp"

sCollPairInfo::sCollPairInfo (int entNodeId1, int entNodeId2,
		const cVector2& overlap, const eCollType& collType):
	entNodeId1_(entNodeId1), entNodeId2_(entNodeId2), overlap_(overlap),
	collType_(collType) {}

cCollPair::cCollPair (const cEntity& entity1, const cEntity& entity2) :
		 entity1_(&entity1), entity2_(&entity2), collType_(eCollType::NO_COLLISION) {
	eEntityType ent1Type = entity1.getType(),
				 ent2Type = entity2.getType();
	if (ent1Type == eEntityType::STATIC 
			&& (ent2Type == eEntityType::DYNAMIC
				|| ent2Type == eEntityType::KINEMATIC)) {
		std::swap(entity1_,entity2_);
	}
}

/*	WHEN YOU CAN GUARANTEE THAT OBJ1 WONT BE STATIC, REMOVE THE COMMENTS AND
 *	THE ABOVE VERSION OF THE CONSTRUCTOR
cCollPair::cCollPair (cCollObj* object1, cCollObj* object2):
		object1_(object1), object2_(object2), collType_(eCollType::NO_COLLISION) {}
*/

cCollPair::~cCollPair (void) {}

const cEntity& cCollPair::ent1 (void) const {
	return *entity1_;
}

const cEntity& cCollPair::ent2 (void) const {
	return *entity2_;
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
