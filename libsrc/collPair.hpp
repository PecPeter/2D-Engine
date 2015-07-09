#ifndef COLLPAIR_HPP
#define COLLPAIR_HPP

#include "mathVector.hpp"
#include "collObject.hpp"

enum class eCollType {
	NO_COLLISION,
	CONTACT,
	COLLISION
};

class cCollPair {
	public:
		cCollPair (cCollObject2D* object1, cCollObject2D* object2);
		~cCollPair (void);

		const cCollObject2D* object1 (void) const;
		const cCollObject2D* object2 (void) const;
		void setObjOverlap (const cVector2& overlap);
		cVector2& getObjOverlap (void);
		void setCollType (const eCollType& collType);
		eCollType getCollType (void);
	private:
		cCollObject2D* object1_, *object2_;
		cVector2 overlap_;
		eCollType collType_;
};

#endif
