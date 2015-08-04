#ifndef COLLTEST2D_HPP
#define COLLTEST2D_HPP

#include <cmath>
#include <utility>
#include <map>

#include "mathVector.hpp"
#include "collShape.hpp"
#include "collObject.hpp"
#include "collPair.hpp"

class cCollTest {
	public:
		cCollTest (void);
		void testPair (cCollPair& collPair);
	private:
		// These collision test should always return what object
		// 1 has to do to get out of the collision

		cVector2 collTestAabbAabb (const cCollObj& aabb1,
				const cCollObj& aabb2);

		// THESE NEED TO BE TESTED
		cVector2 collTestAabbLine (const cCollObj& aabb,
				const cCollObj& line);
		cVector2 collTestLineAabb (const cCollObj& line,
				const cCollObj& aabb);
		cVector2 collTestLineLine (const cCollObj& line1, //Returns noColl_
				const cCollObj& line2);					  //No need to test

		cVector2 noColl_,
				 contactColl_;

		typedef std::pair<eShapeType,eShapeType> collTestMapKey;
		typedef cVector2 (cCollTest::*collTestMapPtr)
			(const cCollObj&,const cCollObj&);
		std::map <collTestMapKey,collTestMapPtr> collTestMap_;
};

#endif
