#include "collDebugDrawer.hpp"

cCollDebugDrawer::cCollDebugDrawer (void): alphaLevel_(255) {}

void cCollDebugDrawer::drawLine (const cVector2& p1, const cVector2& p2,
		const cVector3& col) {

}

void cCollDebugDrawer::drawSphere (const cVector2& p, const double& rad,
		const cVector3& col) {

}

void cCollDebugDrawer::drawTriangle (const cVector2& v1, const cVector2& v2,
		const cVector2& v3, const cVector3& col) {

}

void cCollDebugDrawer::drawRect (const cVector2& p, const cVector2& halfDim,
		const cVector3& col) {

}


void cCollDebugDrawer::drawRect (const cVector2& p, const double& hw,
		const double& hh, const cVector3& col) {

}

void cCollDebugDrawer::drawShape (const cCollShape& shape, const cVector3& col) {

}
