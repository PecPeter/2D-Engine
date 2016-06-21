#ifndef COLLTEST2D_HPP
#define COLLTEST2D_HPP

#include <cmath>
#include <limits>
#include <utility>
#include <map>
#include <memory>

#include "mathVector.hpp"
#include "mathLinAlgebra.hpp"
#include "collShape.hpp"
#include "collShapeNode.hpp"
#include "collObject.hpp"
#include "collPair.hpp"

const cVector2 noColl_ (std::nan(""),std::nan(""));
const cVector2 contactColl_ (0,0);

struct sCollShapeInfo {
	double shapeRotn_;
	cVector2 shapePos_;
	std::shared_ptr<const cCollShape> shape_;
};

class cCollTest {
	public:
		cCollTest (void);
		void testPair (cCollPair& collPair);
	private:
		// These collision test should always return what object
		// 1 has to do to get out of the collision (ie. obj1: dynamic,
		// obj2: static (even if it isnt))

		// Collision test management functions
		cVector2 collTestComplexComplex (const cCollObj& objComplex1,
				const cCollObj& objComplex2, const cVector2& collVector);
		cVector2 collTestSimpleComplex (const cCollObj& objComplex1,
				const cCollObj& objComplex2, const cVector2& collVector);
		cVector2 collTestComplexSimple (const cCollObj& objComplex1,
				const cCollObj& objComplex2, const cVector2& collVector);

		// Functions for the colTestMap_
		cVector2 collTestPolyPoly (const sCollShapeInfo& objPoly1,
				const sCollShapeInfo& objPoly2);
		cVector2 collTestPolyCircle (const sCollShapeInfo& objPoly,
				const sCollShapeInfo& objCircle);
		cVector2 collTestCirclePoly (const sCollShapeInfo& objCircle,
				const sCollShapeInfo& objPoly);
		cVector2 collTestCircleCircle (const sCollShapeInfo& objCircle1,
				const sCollShapeInfo& objCircle2);

		typedef std::pair<eShapeType,eShapeType> collTestMapKey;
		typedef cVector2 (cCollTest::*collTestMapPtr)
			(const sCollShapeInfo&,const sCollShapeInfo&);
		std::map <collTestMapKey,collTestMapPtr> collTestMap_;
};

void genNormList (const std::vector<cVector2>& nList1, const std::vector<cVector2>& nList2,
		std::vector<cVector2>* normList);
//This return the min displacement that obj1 would have to do to not intersect
//with obj2 along an axis
cVector2 minDisplacement (double obj1Min, double obj1Max, double obj2Min, double obj2Max, cVector2 axis);

#endif
