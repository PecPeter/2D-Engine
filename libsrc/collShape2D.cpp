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
