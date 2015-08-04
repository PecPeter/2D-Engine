#include "collShape.hpp"

cCollShape::cCollShape (eShapeType shapeType): shapeType_(shapeType) {}

cCollShape::~cCollShape (void) {}

cCollAabb::cCollAabb (double hw, double hh): cCollShape(eShapeType::AABB),
		hw_(hw), hh_(hh) {}

cCollAabb::~cCollAabb (void) {}

double cCollAabb::getHW (void) const {
	return hw_;
}

double cCollAabb::getHH (void) const {
	return hh_; 
}

cCollLine::cCollLine (const cVector2& p1, const cVector2& p2):
		cCollShape(eShapeType::LINE) {
	cVector2 dv = p2-p1;
	dir_ = vUnitVector(dv);
}

cCollLine::cCollLine (const cVector2& dir): cCollShape(eShapeType::LINE),
	dir_(dir) {}

cVector2 cCollLine::getDir (void) const {
	return dir_;
};

bool operator== (const cCollShape& lhs, const cCollShape& rhs) {
	const eShapeType shape1 = lhs.getShapeType(),
		  shape2 = rhs.getShapeType();
	if (shape1 != shape2)
		return false;
	if (shape1 == eShapeType::AABB) {
		const cCollAabb& aabb1 = static_cast<const cCollAabb&>(lhs);
		const cCollAabb& aabb2 = static_cast<const cCollAabb&>(rhs);
		if (aabb1.getHW() == aabb2.getHW() &&
				aabb1.getHH() == aabb2.getHH())
			return true;
	}
	if (shape1 == eShapeType::LINE) {
		const cCollLine& line1 = static_cast<const cCollLine&>(lhs);
		const cCollLine& line2 = static_cast<const cCollLine&>(rhs);
		if (line1.getDir() == line2.getDir())
			return true;
	}
	return false;
}
