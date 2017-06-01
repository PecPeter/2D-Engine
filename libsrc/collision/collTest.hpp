#ifndef COLLTEST_HPP
#define COLLTEST_HPP

#include <cmath>
#include <limits>
#include <utility>
#include <map>
#include <memory>
#include <vector>
#include <iostream>

#include "./mathLib/mathVector.hpp"
#include "./mathLib/mathLinAlgebra.hpp"

#include "collShape.hpp"
#include "collPair.hpp"
#include "../entity/entity.hpp"
#include "../entity/entityNode.hpp"
#include "../entity/components/positionComponent.hpp"
#include "../entity/components/collisionComponent.hpp"

const cVector2 noColl_ (std::nan(""),std::nan(""));
const cVector2 contactColl_ (0,0);

struct sCollShapeInfo {
	sCollShapeInfo (const cPosComp& parentPosComp, const cPosComp& shapePosComp,
			const cCollComp& collComp);
	const cPosComp parentPosComp_,
		  		   shapePosComp_;
	const cCollComp collComp_;
};

class cCollTest {
	public:
		cCollTest (void);
		bool testPair (cCollPair& collPair);
	private:
		// These collision test should always return what object
		// 1 has to do to get out of the collision (ie. obj1: dynamic,
		// obj2: static (even if it isnt))

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
