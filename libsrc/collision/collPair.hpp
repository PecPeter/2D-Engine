#ifndef COLLPAIR_HPP
#define COLLPAIR_HPP

#include <algorithm>
#include <list>
#include <memory>

#include "../entity/entity.hpp"
#include "../math/mathVector.hpp"

enum class eCollType {
	NO_COLLISION,
	CONTACT,
	COLLISION
};

struct sCollPairInfo {
	sCollPairInfo (int entNodeId1, int entNodeId2, const cVector2& overlap,
			const eCollType& collType);
	int entNodeId1_,
		entNodeId2_;
	cVector2 overlap_;
	eCollType collType_;
};

class cCollPair {
	public:
		cCollPair (cEntity& entity1, cEntity& entity2);
		~cCollPair (void);

		cEntity& ent1 (void) const;
		cEntity& ent2 (void) const;

		void addCollision (const sCollPairInfo& collInfo);
		void addCollision (int entNodeId1, int entNodeId2,
				const cVector2& overlap, const eCollType& collType);
		const std::list<sCollPairInfo>& getCollisions (void) const;
		void resetCollisions (void);
	private:
		cEntity* entity1_,
			   * entity2_;
//		cVector2 overlap_; // Overlap is wrt what obj1 has to do
						   // to get out of collision
		// TODO: Add the ids of the entity nodes that are colliding
		// also add a vector or something that logs all of the shapes that can
		// collide (multiple nodes may collide with each other)
//		eCollType collType_;
		std::list<sCollPairInfo> collisionList_;
};

#endif
