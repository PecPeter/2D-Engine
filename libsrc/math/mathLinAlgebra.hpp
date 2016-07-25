#ifndef MATHLINALGEBRA_HPP
#define MATHLINALGEBRA_HPP

#include <cmath>

#include "../engineMetrics.hpp"
#include "mathMatrix.hpp"
#include "mathVector.hpp"

double max (const double& v1, const double& v2);
double min (const double& v1, const double& v2);
void clampMax (const double& max, double& value);
void clampMin (const double& min, double& value);
void clampRange (const double& min, const double& max, double& value);
bool isWithinRange (const double& min, const double& max, const double& value);

// When the rotation matrix is multiplied by a column vector (ie.
// rotnMatrix*column), the points in the column vector will be rotated
// around the origin.
cMatrix rotnTransform (const double rotnRad);

// Determines whether 2 lines intersect or not. If they do, it will
// return true and the intersection point will be in point. If they 
// don't intersect or intersect infinitely, false will be returned
// and point will contain NAN.
bool lineIntersection (const cVector2& p1, const cVector2& d1,
		const cVector2& p2, const cVector2& d2, cVector2& point);

#endif
