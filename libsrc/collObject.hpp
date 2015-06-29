#ifndef COLLOBJECT_HPP
#define COLLOBJECT_HPP

#include "collShape2D.hpp"
#include "mathVector.hpp"

enum class eObjectType {
	STATIC,
	DYNAMIC
};

class cCollObject2D {
	public:
		cCollObject2D (const cVector2& pos, const cCollShape* shape,
				eObjectType objectType=eObjectType::STATIC);
		~cCollObject2D (void);
		void translate (double dx, double dy);
		void translate (const cVector2& dv);
		const cVector2& getPosition (void) const {return pos_;}
		const cCollShape* getCollShape (void) const {return shape_;}
	private:
		cVector2 pos_;
		const cCollShape* shape_;
		int collShapeIndex_;
		eObjectType objectType_;
		// ADD SOMETHING ABOUT ROTATION?
};

#endif
