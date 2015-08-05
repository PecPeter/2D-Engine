#ifndef COLLSHAPE_HPP
#define COLLSHAPE_HPP

#include <array>
#include <vector>

#include "mathMatrix.hpp"
#include "mathVector.hpp"

enum class eShapeType {
	POINT,
	LINE,
	TRI,
	AABB,
	OOBB,
	POLY,
	CIRCLE
};

class cCollShape {
	public:
		cCollShape (eShapeType shapeType, int numNorms);
		virtual ~cCollShape (void);

		const eShapeType& getShapeType (void) const;
		const std::vector<cVector2>& getNormList (void) const;
	protected:
		eShapeType shapeType_;
		std::vector<cVector2> normList_;
};

class cCollLine : public cCollShape {
	public:
		//coll|no coll
		//    |
		//    |
		//    |-> right normal
		//    |
		//    |
		cCollLine (const cVector2& p1, const cVector2& p2);
		cCollLine (const cVector2& dir);
		cVector2 getDir (void) const;

	private:
		cVector2 dir_;
};

class cCollTri : public cCollShape {
	public:
		cCollTri (const cVector2& pt1, const cVector2& pt2, const cVector2& pt3);
		cCollTri (double x1, double y1, double x2, double y2, double x3, double x4);
		~cCollTri (void);

		const std::vector<cVector2>& getPtList (void) const;
	private:
		std::vector<cVector2> ptList_;
};

class cCollAabb : public cCollShape {
	public:
		cCollAabb (double hw, double hh); //This needs to throw in case negative values are given
		~cCollAabb (void);

		double getHW (void) const;
		double getHH (void) const;
	private:
		double hw_,
			   hh_;
};

class cCollPoly : public cCollShape {
	public:
		// The polygon must be non-self-intersecting, and closed (ie. the
		// first point must be the last point as well). The points should be
		// defined in CCW order
		cCollPoly (const std::vector<cVector2>& pts);
		~cCollPoly (void);

		const std::vector<cVector2>& getPtList (void) const;
	private:
		std::vector<cVector2> ptList_;
};

bool operator== (const cCollShape& lhs, const cCollShape& rhs);

// Calculates centroid of a non-self-intersecting polygon
// pts: list of points. The final point has to be the first point (ie. a
// closed polygon).
cVector2 polygonCentroid (const std::vector<cVector2>& pts);

#endif
