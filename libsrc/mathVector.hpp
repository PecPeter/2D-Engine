#ifndef MATHVECTOR_HPP
#define MATHVECTOR_HPP

#include <cmath>
#include "mathMatrix.hpp"

class cVector2: public cMatrix {
	public:
		cVector2 (double x, double y);
		cVector2 (const cVector2& vector);
		virtual ~cVector2 (void);

//		cVector2 projection (const cVector2& projAxis);
		double sqMagnitude (void) const;
		double magnitude (void) const;
	private:
};

// Make a class that holds lookup tables for the trig functions, and the
// value of PI
double dotProd (const cVector2& v1, const cVector2& v2);
double angleRad (const cVector2& v1, const cVector2& v2);
double andleDeg (const cVector2& v1, const cVector2& v2);
cVector2 unitVector (const cVector2& v1);
cVector2 absolute (const cVector2& v1);

#endif
