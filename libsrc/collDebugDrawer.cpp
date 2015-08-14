#include "collDebugDrawer.hpp"

cCollDebugDrawer::cCollDebugDrawer (int alpha): alphaLevel_(alpha) {
	colMap_[eObjType::STATIC] = cVector3(255,0,0);
	colMap_[eObjType::DYNAMIC] = cVector3(0,255,0);
}

void cCollDebugDrawer::drawObj (SDL_Renderer* rend, const cCollObj& obj) {
	drawObj(rend,obj,colMap_.at(obj.getObjType()));
}

void cCollDebugDrawer::drawObj (SDL_Renderer* rend, const cCollObj& obj, const cVector3& col) {
	cVector2 objPos = obj.getObjPos();
	eShapeType shapeType = obj.getCollShape()->getShapeType();
	
	if (shapeType == eShapeType::POLY) {
		std::vector<cVector2> ptList = obj.getCollShape()->getData();
		double objRotn = obj.getRotation();
		if (objRotn != 0.0) {
			cMatrix rotnMatrix = solveRotationMatrix(obj.getRotation());
			for (auto& ptListItr : ptList)
				ptListItr = rotnMatrix*ptListItr+objPos;
		}
		else {
			for (auto& ptListItr : ptList)
				ptListItr += objPos;
		}
		ptList.push_back(*ptList.begin());
		drawPoly(rend,ptList,col);
	}
	else if (shapeType == eShapeType::CIRCLE) {
		drawCircle(rend,objPos,obj.getCollShape()->getData().at(0).getX(),col);
	}
	else if (shapeType == eShapeType::LINE) {
//		drawLine(rend...);
	}
	else if (shapeType == eShapeType::POINT) {
//		drawPoint(rend,...);
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
}

void cCollDebugDrawer::drawCircle (SDL_Renderer* rend, const cVector2& p,
		const double& rad, const cVector3& col) {
	filledCircleRGBA(rend,p.getX(),p.getY(),rad, col.getX(),col.getY(),
			col.getZ(),alphaLevel_);
}
