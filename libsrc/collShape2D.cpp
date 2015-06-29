#include "collShape2D.hpp"

cCollShape::cCollShape (eShapeType shapeType): shapeType_(shapeType),shapeDim_(0,0) {
	switch (shapeType_) {
		case eShapeType::POINT:
			shapeDim_.resize(0,0);
			break;
		case eShapeType::CIRCLE:
			shapeDim_.resize(1,1);
			break;
		case eShapeType::AABB:
			shapeDim_.resize(2,1);
			break;
		default:
			break;
	}
}

cCollShape::cCollShape (const eShapeType shapeType, const cMatrix& shapeDim):
	shapeType_(shapeType),shapeDim_(shapeDim) {}

cCollShape::~cCollShape (void) {}

bool cCollShape::operator== (const cCollShape& rhs) const {
	if (shapeType_ != rhs.getShapeType())
		return false;
	if (shapeDim_ != rhs.getShapeDim())
		return false;
	return true;
}

cCollPoint::cCollPoint (void): cCollShape(eShapeType::POINT) {}

cCollPoint::~cCollPoint (void) {}

cCollCircle::cCollCircle (double radius): cCollShape(eShapeType::CIRCLE) {
	shapeDim_.set(0,0) = radius;
}

cCollCircle::cCollCircle (const cCollCircle& ref): cCollShape(eShapeType::CIRCLE) {
	shapeDim_ = ref.getShapeDim();
}

cCollCircle::~cCollCircle (void) {}

cCollAabb::cCollAabb (double hw, double hh): cCollShape(eShapeType::AABB) {
	shapeDim_.set(0,0) = hw;
	shapeDim_.set(1,0) = hh;
}

cCollAabb::cCollAabb (const cCollAabb& ref): cCollShape(eShapeType::AABB) {
	shapeDim_ = ref.getShapeDim();
}

cCollAabb::~cCollAabb (void) {}
