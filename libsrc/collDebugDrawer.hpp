#ifndef COLLDEBUGDRAWER_HPP
#define COLLDEBUGDRAWER_HPP

#include <cmath>
#include <map>
#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "collObject.hpp"
#include "collShape.hpp"
#include "collShapeNode.hpp"
#include "mathVector.hpp"
#include "mathLinAlgebra.hpp"
#include "renderFunctions.hpp"

class cCollDebugDrawer {
	public:
		cCollDebugDrawer (int alpha = 255);

		void drawObj (const SDL_Renderer* rend, const cCollObj& obj);
		void drawObj (const SDL_Renderer* rend, const cCollObj& obj,
				const cVector4& col);

	private:
		void drawComplexShape (const SDL_Renderer* rend,
				const sCollShapeNode& shapeNode, const cVector2& posOffset,
				const double& rotnOffset, const cVector4& col);
		void drawShape (const SDL_Renderer* rend, const cCollShape& shape,
				const cVector2& shapePos, const double& shapeRotn,
				const cVector4& col);
//		typedef std::pair<eObjectType,eObjectState> colIndex;
//		std::map<colIndex,cVector3> colMap;
		std::map<eObjType,cVector4> colMap_;
};

#endif
