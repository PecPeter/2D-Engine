#ifndef COLLTEST2D_HPP
#define COLLTEST2D_HPP

#include <cmath>
#include <limits>
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

		cVector2 collTestPolyPoly (const cCollObj& objPoly1, const cCollObj& objPoly2);
		cVector2 collTestPolyCircle (const cCollObj& objPoly, const cCollObj& objCircle);
		cVector2 collTestCirclePoly (const cCollObj& objCircle, const cCollObj& objPoly);
		cVector2 collTestCircleCircle (const cCollObj& objCircle1, const cCollObj& objCircle2);

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
