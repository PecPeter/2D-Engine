#ifndef COLLTEST2D_HPP
#define COLLTEST2D_HPP

#include <cmath>
#include "mathVector.hpp"
#include "collShape2D.hpp"
#include "collObject.hpp"
#include "collPair.hpp"

class cCollTestHandler {
	public:
		cCollTestHandler (void);
		void operator() (cCollPair& collPair);
	private:
		// This function return a vector, based on the state of the collision:
		// When a collision occurs, the returned vector is with respect to aabb1
		cVector2 collTestAabbAabb (const cCollObject2D& aabb1,
				const cCollObject2D& aabb2);

		cVector2 noColl_,
				 contactColl_;
};

#endif
