#include "collDebugDrawer.hpp"

cCollDebugDrawer::cCollDebugDrawer (int alpha): alphaLevel_(alpha) {
	colMap_[eObjType::STATIC] = cVector3(255,0,0);
	colMap_[eObjType::DYNAMIC] = cVector3(0,255,0);
}

void cCollDebugDrawer::drawObj (SDL_Renderer* rend, const cCollObj& obj) {
	cVector2 objPos = obj.getObjPos();
	eShapeType shapeType = obj.getCollShape()->getShapeType();
	
	if (shapeType == eShapeType::POLY) {
		drawPoly(rend,obj.getCollShape()->getData(),colMap_.at(obj.getObjType()));
	}
}

void cCollDebugDrawer::drawStrL (SDL_Renderer* rend, TTF_Font* font,
		const cVector2& p, const char* text, const cVector3& col) {
	SDL_Color textColor;
	textColor.a = 255;
	textColor.r = col.getX();
	textColor.g = col.getY();
	textColor.b = col.getZ();
	SDL_Surface* textSurface = TTF_RenderText_Solid(font,text,textColor);
	if (textSurface != nullptr) {
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rend,
				textSurface);
		SDL_FreeSurface(textSurface);
		SDL_Rect renderRect;
		renderRect.x = p.getX();
		renderRect.y = p.getY();
		SDL_QueryTexture(textTexture,NULL,NULL,&renderRect.w,&renderRect.h);
		SDL_RenderCopy(rend,textTexture,NULL,&renderRect);
		SDL_DestroyTexture(textTexture);
	}
}

void cCollDebugDrawer::drawStrR (SDL_Renderer* rend, TTF_Font* font,
		const cVector2& p, const char* text, const cVector3& col) {
	SDL_Color textColor;
	textColor.a = 255;
	textColor.r = col.getX();
	textColor.g = col.getY();
	textColor.b = col.getZ();
	SDL_Surface* textSurface = TTF_RenderText_Solid(font,text,textColor);
	if (textSurface != nullptr) {
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rend,
				textSurface);
		SDL_FreeSurface(textSurface);
		SDL_Rect renderRect;
		SDL_QueryTexture(textTexture,NULL,NULL,&renderRect.w,&renderRect.h);
		renderRect.x = p.getX()-renderRect.w;
		renderRect.y = p.getY();
		SDL_RenderCopy(rend,textTexture,NULL,&renderRect);
		SDL_DestroyTexture(textTexture);
	}
}

void cCollDebugDrawer::drawPoint (SDL_Renderer* rend, const cVector2& p,
		const cVector3& col) {
	pixelRGBA(rend,p.getX(),p.getY(),col.getX(),col.getY(),
			col.getZ(),alphaLevel_);
}

void cCollDebugDrawer::drawLine (SDL_Renderer* rend, const cVector2& p1,
		const cVector2& p2, const cVector3& col) {
	lineRGBA(rend,p1.getX(),p1.getY(),p2.getX(),p2.getY(),
			col.getX(),col.getY(),col.getZ(),alphaLevel_);
}

void cCollDebugDrawer::drawSphere (SDL_Renderer* rend, const cVector2& p,
		const double& rad, const cVector3& col) {
	filledCircleRGBA(rend,p.getX(),p.getY(),rad, col.getX(),col.getY(),
			col.getZ(),alphaLevel_);
}

void cCollDebugDrawer::drawTriangle (SDL_Renderer* rend, const cVector2& v1,
		const cVector2& v2, const cVector2& v3, const cVector3& col) {
	filledTrigonRGBA(rend,v1.getX(),v1.getY(),v2.getX(),v2.getY(),v3.getX(),
			v3.getY(),col.getX(),col.getY(),col.getZ(),alphaLevel_);
//	drawLine(rend,v1,v2,col);
//	drawLine(rend,v1,v3,col);
//	drawLine(rend,v2,v3,col);
}

void cCollDebugDrawer::drawRect (SDL_Renderer* rend, const cVector2& p,
		const double& hw, const double& hh, const cVector3& col) {
	boxRGBA(rend,p.getX()-hw,p.getY()-hh, p.getX()+hw,p.getY()+hh,
			col.getX(),col.getY(),col.getZ(),alphaLevel_);
}

void cCollDebugDrawer::drawPoly (SDL_Renderer* rend,
		const std::vector<cVector2>& pList, const cVector3& col) {
	Sint16* vx = new Sint16[pList.size()];
	Sint16* vy = new Sint16[pList.size()];
	for (unsigned int i = 0; i < pList.size(); ++i) {
		vx[i] = pList.at(i).getX();
		vy[i] = pList.at(i).getY();
	}
	filledPolygonRGBA(rend,vx,vy,pList.size(),col.getX(),col.getY(),
			col.getZ(),alphaLevel_);
	delete[] vx;
	delete[] vy;
/*
	auto prevItr = pList.begin();
	for (auto itr = prevItr+1; itr != pList.end(); itr++, prevItr++) {
		drawLine(rend,*itr,*prevItr,col);
	}
	drawLine(rend,*pList.begin(),*pList.rbegin(),col);*/
}
