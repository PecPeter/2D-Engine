#ifndef RENDERFUNCTIONS_HPP
#define RENDERFUNCTIONS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "./math/mathMatrix.hpp"
#include "./math/mathVector.hpp"
#include "./math/mathLinAlgebra.hpp"

void drawStrC (SDL_Renderer* rend, TTF_Font* font,
		 const cVector2& p, const char* text, const cVector4& col);
void drawStrU (SDL_Renderer* rend, TTF_Font* font,
		 const cVector2& p, const char* text, const cVector4& col);
void drawStrUR (SDL_Renderer* rend, TTF_Font* font,
		 const cVector2& p, const char* text, const cVector4& col);
void drawStrR (SDL_Renderer* rend, TTF_Font* font,
		 const cVector2& p, const char* text, const cVector4& col);
void drawStrDR (SDL_Renderer* rend, TTF_Font* font,
		 const cVector2& p, const char* text, const cVector4& col);
void drawStrD (SDL_Renderer* rend, TTF_Font* font,
		 const cVector2& p, const char* text, const cVector4& col);
void drawStrDL (SDL_Renderer* rend, TTF_Font* font,
		 const cVector2& p, const char* text, const cVector4& col);
void drawStrL (SDL_Renderer* rend, TTF_Font* font,
		 const cVector2& p, const char* text, const cVector4& col);
void drawStrUL (SDL_Renderer* rend, TTF_Font* font,
		 const cVector2& p, const char* text, const cVector4& col);
void drawPoint (SDL_Renderer* rend, const cVector2& p,
		const cVector4& col);
void drawLine (SDL_Renderer* rend, const cVector2& p1,
		const cVector2& p2, const cVector4& col);
void drawPoly (SDL_Renderer* rend, const std::vector<cVector2>& pList,
		const cVector4& col);
void drawCircle (SDL_Renderer* rend, const cVector2& p,
		const double& rad, const cVector4& col);
void drawCross (SDL_Renderer* rend, const cVector2& p,
		const double& l, const cVector4& col);
void drawCentrPoint (SDL_Renderer* rend, const cVector2& p,
		const cVector4& col);

#endif
