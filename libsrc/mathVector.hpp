#ifndef MATHVECTOR_HPP
#define MATHVECTOR_HPP

#include <cmath>
#include "mathMatrix.hpp"

class cVector2: public cMatrix {
	public:
		cVector2 (double x, double y);
		cVector2 (const cVector2& vector);
		virtual ~cVector2 (void);
};

// Make a class that holds lookup tables for the trig functions, and the
// value of PI
double vSqMagnitude (const cVector2& v1);
double vMagnitude (const cVector2& v1);
double vDotProd (const cVector2& v1, const cVector2& v2);
double vAngleRad (const cVector2& v1, const cVector2& v2);
double vAndleDeg (const cVector2& v1, const cVector2& v2);
cVector2 vUnitVector (const cVector2& v1);
cVector2 vAbsolute (const cVector2& v1);
cVector2 vNormal (const cVector2& v1);
//cVector2 vProjection (const cVector2& projAxis);

#endif
