#include "collShape2D.hpp"

cCollShape::cCollShape (eShapeType shapeType): shapeType_(shapeType) {}

cCollShape::~cCollShape (void) {}

cCollAabb::cCollAabb (double hw, double hh): cCollShape(eShapeType::AABB),
		halfWidth_(hw), halfHeight_(hh) {}

cCollAabb::~cCollAabb (void) {}

double cCollAabb::getHalfWidth (void) const {
	return halfWidth_;
}

double cCollAabb::getHalfHeight (void) const {
	return halfHeight_; 
}

bool operator== (const cCollShape& lhs, const cCollShape& rhs) {
	const eShapeType shape1 = lhs.getShapeType(),
		  shape2 = rhs.getShapeType();
	if (shape1 != shape2)
		return false;
	if (shape1 == eShapeType::AABB) {
		const cCollAabb& aabb1 = dynamic_cast<const cCollAabb&>(lhs),
			  &aabb2 = dynamic_cast<const cCollAabb&>(rhs);
		if (aabb1.getHalfWidth() == aabb2.getHalfWidth() &&
				aabb1.getHalfHeight() == aabb2.getHalfHeight())
			return true;
	}
	return false;
}
