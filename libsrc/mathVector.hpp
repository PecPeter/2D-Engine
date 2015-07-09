#ifndef MATHVECTOR_HPP
#define MATHVECTOR_HPP

#include <cmath>
#include "mathMatrix.hpp"

class cVector2: public cMatrix {
	public:
		cVector2 (void);
		cVector2 (const double& x, const double& y);
		cVector2 (const cVector2& vector);
		cVector2 (const cMatrix& matrix);
		virtual ~cVector2 (void);

		double getX (void) const;
		double getY (void) const;
};

double vSqMagnitude (const cVector2& v1);
double vMagnitude (const cVector2& v1);
double vDotProd (const cVector2& v1, const cVector2& v2);
double vAngleRad (const cVector2& v1, const cVector2& v2);
double vAndleDeg (const cVector2& v1, const cVector2& v2);
double vScalProj (const cVector2& projVec, const cVector2& projAxis);
cVector2 vUnitVector (const cVector2& v1);
cVector2 vAbsolute (const cVector2& v1);
cVector2 vNormal (const cVector2& v1);
cVector2 vVecProj (const cVector2& projVec, const cVector2& projAxis);

#endif
