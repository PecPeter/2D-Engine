#ifndef MATHVECTOR_HPP
#define MATHVECTOR_HPP

#include "mathMatrix.hpp"

class cVector2: public cMatrix {
	public:
		cVector2 (double x, double y);
		cVector2 (const cVector2& vector);
		virtual ~cVector2 (void);

//		cVector2 projection (const cVector2& projAxis);
		double sqMagnitude (void);
		double magnitude (void);
	private:
};

double dotProd (const cVector2& v1, const cVector2& v2);

#endif
