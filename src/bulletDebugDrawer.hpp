#ifndef BULLETDEBUGDRAWER_HPP
#define BULLETDEBUGDRAWER_HPP

#include <iostream>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
#include <SDL2_gfx.h>

#include <bullet/btBulletCollisionCommon.h>
#include <bullet/LinearMath/btIDebugDraw.h>

//bullet debug drawing class
class cDebugDraw : public btIDebugDraw {
	public:
		cDebugDraw (SDL_Renderer *renderer);
		~cDebugDraw (void);

		virtual void drawLine(const btVector3& from,const btVector3& to,const btVector3& color) override;
/*		virtual void drawLine(const btVector3& from,const btVector3& to, const btVector3& fromColor, const btVector3& toColor) override;
		virtual void drawSphere(btScalar radius, const btTransform& transform, const btVector3& color) override;
		virtual void drawSphere (const btVector3& p, btScalar radius, const btVector3& color) override;
		virtual	void drawTriangle(const btVector3& v0,const btVector3& v1,const btVector3& v2,const btVector3& n0,const btVector3& n1,const btVector3& n2,const btVector3& color, btScalar alpha) override; //comment out the "nx" variables
		virtual	void drawTriangle(const btVector3& v0,const btVector3& v1,const btVector3& v2,const btVector3& color, btScalar alpha) override; //comment out alpha
		virtual void drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color) override;
		virtual void reportErrorWarning(const char* warningString) override;
		virtual void draw3dText(const btVector3& location,const char* textString) override;
		virtual void setDebugMode(int debugMode) override;
		virtual int	getDebugMode() const override;
		virtual void drawAabb(const btVector3& from,const btVector3& to,const btVector3& color) override;
		virtual void drawTransform(const btTransform& transform, btScalar orthoLen) override;
		virtual void drawArc(const btVector3& center, const btVector3& normal, const btVector3& axis, btScalar radiusA, btScalar radiusB, btScalar minAngle, btScalar maxAngle, const btVector3& color, bool drawSect, btScalar stepDegrees) override;
		virtual void drawSpherePatch(const btVector3& center, const btVector3& up, const btVector3& axis, btScalar radius,	btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, const btVector3& color, btScalar stepDegrees,bool drawCenter) override;
		virtual void drawBox(const btVector3& bbMin, const btVector3& bbMax, const btVector3& color) override;
		virtual void drawBox(const btVector3& bbMin, const btVector3& bbMax, const btTransform& trans, const btVector3& color) override;
		virtual void drawCapsule(btScalar radius, btScalar halfHeight, int upAxis, const btTransform& transform, const btVector3& color) override;
		virtual void drawCylinder(btScalar radius, btScalar halfHeight, int upAxis, const btTransform& transform, const btVector3& color) override;
		virtual void drawCone(btScalar radius, btScalar height, int upAxis, const btTransform& transform, const btVector3& color) override;
		virtual void drawPlane(const btVector3& planeNormal, btScalar planeConst, const btTransform& transform, const btVector3& color) override;
*/	private:
		int m_debugMode;
		SDL_Renderer *renderer;
		Uint8 alphaLevel;
};

#endif

