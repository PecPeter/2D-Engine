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

		cVector2 collTestPolyPoly (const cCollObj& obj1, const cCollObj& obj2);

		cVector2 noColl_,
				 contactColl_;

		typedef std::pair<eShapeType,eShapeType> collTestMapKey;
		typedef cVector2 (cCollTest::*collTestMapPtr)
			(const cCollObj&,const cCollObj&);
		std::map <collTestMapKey,collTestMapPtr> collTestMap_;
};

void genNormList (const std::vector<cVector2>& nList1, const std::vector<cVector2>& nList2,
		std::vector<cVector2>* normList);


#endif
