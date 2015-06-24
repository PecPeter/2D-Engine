#ifndef COLLOBJECT_HPP
#define COLLOBJECT_HPP

#include "mathVector.hpp"

enum class eObjectType {
	STATIC,
	DYNAMIC
};

class cCollObject2D {
	public:
		cCollObject2D (const cVector2& pos, int collShapeIndex,
				eObjectType objectType=eObjectType::STATIC);
		~cCollObject2D (void);
		void translate (double dx, double dy);
		void translate (const cVector2& dv);
		const cVector2& getPosition (void) const {return pos_;}
		int getCollShapeIndex (void) const {return collShapeIndex_;}
	private:
		cVector2 pos_;
		int collShapeIndex_;
		eObjectType objectType_;
		// ADD SOMETHING ABOUT ROTATION?
};

#endif