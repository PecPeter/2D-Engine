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
#include "mathMatrix.hpp"
#include "mathVector.hpp"

class cCollDebugDrawer {
	public:
		cCollDebugDrawer (int alpha = 255);

		void drawObj (SDL_Renderer* rend, const cCollObj& obj);
		void drawObj (SDL_Renderer* rend, const cCollObj& obj, const cVector3& col);
		void drawStrL (SDL_Renderer* rend, TTF_Font* font,
				const cVector2& p, const char* text, const cVector3& col);
		void drawStrR (SDL_Renderer* rend, TTF_Font* font,
				 const cVector2& p, const char* text, const cVector3& col);

	private:
		void drawPoint (SDL_Renderer* rend, const cVector2& p,
				const cVector3& col);
		void drawLine (SDL_Renderer* rend, const cVector2& p1,
				const cVector2& p2, const cVector3& col);
		void drawPoly (SDL_Renderer* rend, const std::vector<cVector2>& pList,
				const cVector3& col);
		void drawCircle (SDL_Renderer* rend, const cVector2& p,
				const double& rad, const cVector3& col);

		int alphaLevel_; // This is not used when drawing strings
//		typedef std::pair<eObjectType,eObjectState> colIndex;
//		std::map<colIndex,cVector3> colMap;
		std::map<eObjType,cVector3> colMap_;
};

#endif