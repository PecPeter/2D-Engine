#ifndef COLLTEST2D_HPP
#define COLLTEST2D_HPP

#include <cmath>
#include <utility>
#include <map>
#include "mathVector.hpp"
#include "collShape2D.hpp"
#include "collObject.hpp"
#include "collPair.hpp"

class cCollTestHandler {
	public:
		cCollTestHandler (void);
		void operator() (cCollPair& collPair);
	private:
		cVector2 collTestAabbAabb (const cCollObject2D& aabb1,
				const cCollObject2D& aabb2);

		cVector2 noColl_,
				 contactColl_;

		typedef std::pair<eShapeType,eShapeType> collTestMapKey;
		typedef cVector2 (cCollTestHandler::*collTestMapPtr)
			(const cCollObject2D&,const cCollObject2D&);
		std::map <collTestMapKey,collTestMapPtr> collTestMap_;
};

#endif
