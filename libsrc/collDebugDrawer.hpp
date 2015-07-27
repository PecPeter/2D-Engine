#ifndef COLLDEBUGDRAWER_HPP
#define COLLDEBUGDRAWER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "collShape2D.hpp"
#include "mathVector.hpp"

class cCollDebugDrawer {
	public:
		cCollDebugDrawer (void);

		void drawLine (const cVector2& p1, const cVector2& p2,
				const cVector3& col);
		void drawSphere (const cVector2& p, const double& rad,
				const cVector3& col);
		void drawTriangle (const cVector2& v1, const cVector2& v2,
				const cVector2& v3, const cVector3& col);
		void drawRect (const cVector2& p, const cVector2& halfDim,
				const cVector3& col);
		void drawRect (const cVector2& p, const double& hw, const double& hh,
				const cVector3& col);
		void drawShape (const cCollShape& shape, const cVector3& col);
	private:
		int alphaLevel_;
};

#endif
