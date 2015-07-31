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

bool operator== (const cCollShape& lhs, const cCollShape& rhs) {
	const eShapeType shape1 = lhs.getShapeType(),
		  shape2 = rhs.getShapeType();
	if (shape1 != shape2)
		return false;
	if (shape1 == eShapeType::AABB) {
		const cCollAabb& aabb1 = dynamic_cast<const cCollAabb&>(lhs);
		const cCollAabb& aabb2 = dynamic_cast<const cCollAabb&>(rhs);
		if (aabb1.getHW() == aabb2.getHW() &&
				aabb1.getHH() == aabb2.getHH())
			return true;
	}
	return false;
}
