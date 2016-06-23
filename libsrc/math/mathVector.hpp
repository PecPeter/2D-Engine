#ifndef MATHVECTOR_HPP
#define MATHVECTOR_HPP

#include <stdexcept>
#include <cassert>
#include <cmath>
#include <limits>

#include "mathMatrix.hpp"
#include "mathConstants.hpp"

class cVector2: public cMatrix {
	public:
		cVector2 (void);
		cVector2 (double x, double y);
		cVector2 (const cVector2& vector);
		cVector2 (const cMatrix& matrix);
		virtual ~cVector2 (void);

		double getX (void) const;
		double getY (void) const;
		void setX (double x);
		void setY (double y);
};

// This is untested in the unit test
class cVector3 : public cMatrix {
	public:
		cVector3 (void);
		cVector3 (double x, double y, double z);
		cVector3 (const cVector3& vector);
		cVector3 (const cMatrix& matrix);
		~cVector3 (void);

		double getX (void) const;
		double getY (void) const;
		double getZ (void) const;
		void setX (double x);
		void setY (double y);
		void setZ (double z);
};

// This is not tested yet
class cVector4 : public cMatrix {
	public:
		cVector4 (void);
		cVector4 (double w, double x, double y, double z);
		cVector4 (const cVector4& vector);
		cVector4 (const cMatrix& matrix);
		~cVector4 (void);

		double getW (void) const;
		double getX (void) const;
		double getY (void) const;
		double getZ (void) const;
		void setW (double w);
		void setX (double x);
		void setY (double y);
		void setZ (double z);
};

const cVector2 zeroVector2(0.0,0.0);
const cVector3 zeroVector3(0.0,0.0,0.0);
const cVector4 zeroVector4(0.0,0.0,0.0,0.0);

double vSqMagnitude (const cVector2& v1);
double vMagnitude (const cVector2& v1);
double vDotProd (const cVector2& v1, const cVector2& v2);
double vAngleRad (const cVector2& v1, const cVector2& v2);
double vAngleDeg (const cVector2& v1, const cVector2& v2);
double vScalProj (const cVector2& projVec, const cVector2& projAxis);
cVector2 vUnitVector (const cVector2& v1); //check for divide by 0
cVector2 vAbsolute (const cVector2& v1);
cVector2 vNormalR (const cVector2& v1);
cVector2 vNormalL (const cVector2& v1);
cVector2 vVecProj (const cVector2& projVec, const cVector2& projAxis);
cVector2 vRotate (const cVector2& v1, const double& rotnRad);
cVector2 vMirror (const cVector2& v1, const cVector2& vMirror);

cVector2 intersectionLineLine (const cVector2& pt1, const cVector2& lineDir1,
		const cVector2& pt2, const cVector2& lineDir2);
double distPtToLine (const cVector2& pt, const cVector2& lineDir,
		const cVector2& ptLine);

#endif
