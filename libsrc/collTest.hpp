#ifndef COLLTEST2D_HPP
#define COLLTEST2D_HPP

#include <cmath>
#include <utility>
#include <map>

#include "mathVector.hpp"
#include "collShape.hpp"
#include "collObject.hpp"
#include "collPair.hpp"

class cCollTestHandler {
	public:
		cCollTestHandler (void);
		void testPair (cCollPair& collPair);
	private:
		cVector2 collTestAabbAabb (const cCollObj& aabb1,
				const cCollObj& aabb2);

		cVector2 noColl_,
				 contactColl_;

		typedef std::pair<eShapeType,eShapeType> collTestMapKey;
		typedef cVector2 (cCollTestHandler::*collTestMapPtr)
			(const cCollObj&,const cCollObj&);
		std::map <collTestMapKey,collTestMapPtr> collTestMap_;
};

#endif
