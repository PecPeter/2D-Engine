#include "bulletDebugDrawer.hpp"

cDebugDraw::cDebugDraw (SDL_Renderer *renderer): m_debugMode(0), renderer(renderer), alphaLevel(255) {}

cDebugDraw::~cDebugDraw (void) {}

void cDebugDraw::drawLine(const btVector3& from,const btVector3& to,const btVector3& color) {
	aalineRGBA(renderer,from.getX(),from.getY(),to.getX(),to.getY(),255*color.getX(),255*color.getY(),255*color.getZ(),alphaLevel);
}
/*
void cDebugDraw::drawLine(const btVector3& from,const btVector3& to, const btVector3& fromColor, const btVector3& toColor) {
	drawLine(from,to,toColor);
}

void cDebugDraw::drawSphere(btScalar radius, const btTransform& transform, const btVector3& color) {
	const btVector3 origin(transform.getOrigin());
	drawSphere(origin,radius,color);
}

void cDebugDraw::drawSphere (const btVector3& p, btScalar radius, const btVector3& color) {
	filledCircleRGBA(renderer,p.getX(),p.getY(),radius,255*color.getX(),255*color.getY(),255*color.getZ(),alphaLevel);
}

void cDebugDraw::drawTriangle(const btVector3& v0,const btVector3& v1,const btVector3& v2,const btVector3& n0,const btVector3& n1,const btVector3& n2,const btVector3& color, btScalar alpha) {
}

void cDebugDraw::drawTriangle(const btVector3& v0,const btVector3& v1,const btVector3& v2,const btVector3& color, btScalar alpha) {
}

void cDebugDraw::drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color) {
}

void cDebugDraw::reportErrorWarning(const char* warningString) {
}

void cDebugDraw::draw3dText(const btVector3& location,const char* textString) {
}

void cDebugDraw::setDebugMode(int debugMode) {
	m_debugMode = debugMode;
}

int cDebugDraw::getDebugMode() const {
	return m_debugMode;
}

void cDebugDraw::drawAabb(const btVector3& from,const btVector3& to,const btVector3& color) {
}

void cDebugDraw::drawTransform(const btTransform& transform, btScalar orthoLen) {
}

void cDebugDraw::drawArc(const btVector3& center, const btVector3& normal, const btVector3& axis, btScalar radiusA, btScalar radiusB, btScalar minAngle, btScalar maxAngle, const btVector3& color, bool drawSect, btScalar stepDegrees) {
}

void cDebugDraw::drawSpherePatch(const btVector3& center, const btVector3& up, const btVector3& axis, btScalar radius, 
		btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, const btVector3& color, btScalar stepDegrees,bool drawCenter) {
}

void cDebugDraw::drawBox(const btVector3& bbMin, const btVector3& bbMax, const btVector3& color) {
}

void cDebugDraw::drawBox(const btVector3& bbMin, const btVector3& bbMax, const btTransform& trans, const btVector3& color) {
}

void cDebugDraw::drawCapsule(btScalar radius, btScalar halfHeight, int upAxis, const btTransform& transform, const btVector3& color) {
}

void cDebugDraw::drawCylinder(btScalar radius, btScalar halfHeight, int upAxis, const btTransform& transform, const btVector3& color) {
}

void cDebugDraw::drawCone(btScalar radius, btScalar height, int upAxis, const btTransform& transform, const btVector3& color) {
}

void cDebugDraw::drawPlane(const btVector3& planeNormal, btScalar planeConst, const btTransform& transform, const btVector3& color) {
}
*/
