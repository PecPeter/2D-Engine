#ifndef COLLTEST2D_HPP
#define COLLTEST2D_HPP

#include <cmath>
#include <limits>
#include <utility>
#include <map>

#include "mathVector.hpp"
#include "mathLinAlgebra.hpp"
#include "collShape.hpp"
#include "collObject.hpp"
#include "collPair.hpp"

const cVector2 noColl_ (std::nan(""),std::nan(""));
const cVector2 contactColl_ (0,0);

class cCollTest {
	public:
		cCollTest (void);
		void testPair (cCollPair& collPair);
	private:
		// These collision test should always return what object
		// 1 has to do to get out of the collision (ie. obj1: dynamic,
		// obj2: static (even if it isnt))

		cVector2 collTestPolyPoly (const cCollObj& objPoly1, const cCollObj& objPoly2);
		cVector2 collTestPolyCircle (const cCollObj& objPoly, const cCollObj& objCircle);
		cVector2 collTestCirclePoly (const cCollObj& objCircle, const cCollObj& objPoly);
		cVector2 collTestCircleCircle (const cCollObj& objCircle1, const cCollObj& objCircle2);

		typedef std::pair<eShapeType,eShapeType> collTestMapKey;
		typedef cVector2 (cCollTest::*collTestMapPtr)
			(const cCollObj&,const cCollObj&);
		std::map <collTestMapKey,collTestMapPtr> collTestMap_;
};

void genNormList (const std::vector<cVector2>& nList1, const std::vector<cVector2>& nList2,
		std::vector<cVector2>* normList);
//This return the min displacement that obj1 would have to do to not intersect
//with obj2 along an axis
cVector2 minDisplacement (double obj1Min, double obj1Max, double obj2Min, double obj2Max, cVector2 axis);

#endif
