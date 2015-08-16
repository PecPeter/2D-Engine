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
		cCollPair (cCollObj* object1, cCollObj* object2);
		~cCollPair (void);

		const cCollObj* obj1 (void) const;
		const cCollObj* obj2 (void) const;
		void setObjOverlap (const cVector2& overlap);
		cVector2& getObjOverlap (void);
		void setCollType (const eCollType& collType);
		eCollType getCollType (void) const;
	private:
		cCollObj* object1_, *object2_;
		cVector2 overlap_; // Overlap if wrt what obj1 has to do to get out of collision
		eCollType collType_;
};

#endif
