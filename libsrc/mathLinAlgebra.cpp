#include "mathLinAlgebra.hpp"

double max (const double& v1, const double& v2) {
	if (v1 > v2) return v1;
	return v2;
}

double min (const double& v1, const double& v2) {
	if (v1 < v2) return v1;
	return v2;
}

void clampMax (const double& max, double& value) {
	if (value > max) value = max;
}

void clampMin (const double& min, double& value) {
	if (value < min) value = min;
}

void clamp (const double& min, const double& max, double& value) {
	clampMax(max,value);
	clampMin(min,value);
}

bool isWithinRange (const double& min, const double& max, const double& value) {
	if (value >= min && value <= max) return true;
	return false;
}

cMatrix rotnTransform (const double rotnRad) {
	cMatrix rotnMatrix(2,2);
	rotnMatrix.set(0,0) = std::cos(rotnRad);
	rotnMatrix.set(0,1) = -std::sin(rotnRad);
	rotnMatrix.set(1,0) = std::sin(rotnRad);
	rotnMatrix.set(1,1) = std::cos(rotnRad);
	return rotnMatrix;
}

bool lineIntersection (const cVector2& p1, const cVector2& d1,
		const cVector2& p2, const cVector2& d2, cVector2& point) {
	// Check for zero vectors
	if (d1 == zeroVector2 || d2 == zeroVector2) {
		return false;
	}

	// Check for asymptotes
	bool isL1Asymptotic = false,
		 isL2Asymptotic = false;
	if (d1.getX() == 0.0) {
		isL1Asymptotic = true;
		if (d2.getX() == 0.0) return false;
	}
	else if (d1.getY() == 0.0) {
		isL1Asymptotic = true;
		if (d2.getY() == 0.0) return false;
	}
	if (d2.getX() == 0.0) isL2Asymptotic = true;
	if (d2.getY() == 0.0) isL2Asymptotic = true;

	if (isL1Asymptotic == true && isL2Asymptotic == true) {
		if (d1.getX() == 0.0)
			// d1 is the X-Asymptote
			point.setX(p1.getX());
		else
			// d2 is the X-Asymptote
			point.setX(p2.getX());
		if (d1.getY() == 0.0)
			// d1 is the Y-Asymptote
			point.setY(p1.getY());
		else
			// d2 is the Y-Asymptote
			point.setY(p2.getY());
		return true;
	}

	// One line is asymptotic, the other isn't
	double m1,
		   m2,
		   b1,
		   b2;
	if (isL1Asymptotic == true) {
		m2 = d2.getY()/d2.getX();
		b2 = p2.getY()-(m2*p2.getX());
		if (d1.getX() == 0.0) {
			point.setX(p1.getX());
			point.setY(m2*point.getX()+b2);
		}
		else {
			point.setY(p1.getY());
			point.setX((point.getY()-b2)/m2);
		}
		return true;
	}
	else if (isL2Asymptotic == true) {
		m1 = d1.getY()/d1.getX();
		b1 = p1.getY()-(m1*p1.getX());
		if (d2.getX() == 0.0) {
			point.setX(p2.getX());
			point.setY(m1*point.getX()+b1);
		}
		else {
			point.setY(p2.getY());
			point.setX((point.getY()-b1)/m1);
		}
		return true;
	}

	// Regular lines
	m1 = d1.getY()/d1.getX();
	m2 = d2.getY()/d2.getX();
	// Check if the lines intersect at all, or infinitely many times
	if (m1 == m2) return false;
	b1 = p1.getY()-(m1*p1.getX()),
	b2 = p2.getY()-(m2*p2.getX());
	point.setX((b2-b1)/(m1-m2));
	point.setY((m1*point.getX())+b1);
	return true;
}
