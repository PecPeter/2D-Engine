#ifndef COLLDEBUGDRAWER_HPP
#define COLLDEBUGDRAWER_HPP

#include <string>
#include <map>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "collShape.hpp"
#include "collObject.hpp"
#include "mathVector.hpp"
#include "mathLinAlgebra.hpp"
#include "renderFunctions.hpp"

class cCollDebugDrawer {
	public:
		cCollDebugDrawer (int alpha = 255);

		void drawObj (SDL_Renderer* rend, const cCollObj& obj);
		void drawObj (SDL_Renderer* rend, const cCollObj& obj, const cVector4& col);

	private:
//		typedef std::pair<eObjectType,eObjectState> colIndex;
//		std::map<colIndex,cVector3> colMap;
		std::map<eObjType,cVector4> colMap_;
};

#endif
