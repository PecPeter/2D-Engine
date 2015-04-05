#include "bulletDebugDrawer.hpp"

cDebugDraw2D::cDebugDraw2D (SDL_Renderer* renderer,int debugMode,Uint8 alphaLevel,eRenderingPlane renderingPlane): renderer_(renderer), debugMode_(debugMode), alphaLevel_(alphaLevel), renderingPlane_(renderingPlane) {}

cDebugDraw2D::~cDebugDraw2D (void) {}

void cDebugDraw2D::drawLine (const btVector3& from,const btVector3& to,const btVector3& color) {
	aalineRGBA(renderer_,from.getX(),from.getY(),to.getX(),to.getY(),255*color.getX(),255*color.getY(),255*color.getZ(),alphaLevel_);
}

void cDebugDraw2D::drawContactPoint (const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color) {
}

void cDebugDraw2D::reportErrorWarning (const char* warningString) {
}

void cDebugDraw2D::draw3dText (const btVector3& location,const char* textString) {
}

void cDebugDraw2D::setDebugMode (int debugMode) {
	debugMode_ = debugMode;
}

int cDebugDraw2D::getDebugMode (void) const {
	return debugMode_;
}

void cDebugDraw2D::setRenderingPlane (const eRenderingPlane renderingPlane) {
	renderingPlane_ = renderingPlane;
}

eRenderingPlane cDebugDraw2D::getRenderingPlane (void) {
	return renderingPlane_;
}
