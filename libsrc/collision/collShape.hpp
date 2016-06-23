#ifndef COLLSHAPE_HPP
#define COLLSHAPE_HPP

#include <array>
#include <vector>

#include "../math/mathMatrix.hpp"
#include "../math/mathVector.hpp"

enum class eShapeType {
	POINT,
	LINE,
	POLY,
	CIRCLE
};

class cCollShape {
	public:
		cCollShape (eShapeType shapeType, int numNorms);
		virtual ~cCollShape (void);

		const eShapeType& getShapeType (void) const;
		const std::vector<cVector2>& getNormList (void) const;
		const std::vector<cVector2> getData (void) const;
	protected:
		eShapeType shapeType_;
		std::vector<cVector2> normList_;
		std::vector<cVector2> data_;
};

class cCollPoint : public cCollShape {
	public:
		cCollPoint (void);
};

class cCollLine : public cCollShape {
	public:
		/*
		 * data_: direction of the line
		 */
		//coll|no coll
		//    |
		//    |
		//    |-> right normal
		//    |
		//    |
		cCollLine (double px1, double py1, double px2, double py2);
		cCollLine (const cVector2& p1, const cVector2& p2);
		cCollLine (const cVector2& dir);
};

class cCollTri : public cCollShape {
	public:
		/*
		 * data_: points of the triangle, with the centroid at 0,0
		 */
		cCollTri (const cVector2& pt1, const cVector2& pt2, const cVector2& pt3);
		cCollTri (double x1, double y1, double x2, double y2, double x3, double x4);
};

class cCollAabb : public cCollShape {
	public:
		/*
		 * data_: points of the AABB, with the centroid at 0,0
		 */
		cCollAabb (double hw, double hh); //This needs to throw in case negative values are given
};

class cCollPoly : public cCollShape {
	public:
		/*
		 * data_: points of the polygon, with the centroid at 0,0
		 */
		// The polygon must be non-self-intersecting, and closed (ie. the
		// first point must be the last point as well). The points should be
		// defined in CCW order
		cCollPoly (const std::vector<cVector2>& pts);
};

class cCollCircle : public cCollShape {
	public:
		/*
		 * data_: radius of the circle
		 */
		cCollCircle (double radius);
};

bool operator== (const cCollShape& lhs, const cCollShape& rhs);

// Calculates centroid of a non-self-intersecting polygon
// pts: list of points. The final point has to be the first point (ie. a
// closed polygon).
cVector2 polygonCentroid (const std::vector<cVector2>& pts);

#endif
