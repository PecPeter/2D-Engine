#include "renderFunctions.hpp"

void drawStrC (SDL_Renderer* rend, TTF_Font* font,
		const cVector2& p, const char* text, const cVector4& col) {
	SDL_Color textColor;
	textColor.a = col.getW();
	textColor.r = col.getX();
	textColor.g = col.getY();
	textColor.b = col.getZ();
	SDL_Surface* textSurface = nullptr;
	textSurface = TTF_RenderText_Solid(font,text,textColor);
	if (textSurface != nullptr) {
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rend,
				textSurface);
		SDL_FreeSurface(textSurface);
		SDL_Rect renderRect;
		SDL_QueryTexture(textTexture,NULL,NULL,&renderRect.w,&renderRect.h);
		renderRect.x = p.getX()-renderRect.w/2;
		renderRect.y = p.getY()-renderRect.h/2;
		SDL_RenderCopy(rend,textTexture,NULL,&renderRect);
		SDL_DestroyTexture(textTexture);
	}
}

void drawStrU (SDL_Renderer* rend, TTF_Font* font,
		const cVector2& p, const char* text, const cVector4& col) {
	SDL_Color textColor;
	textColor.a = col.getW();
	textColor.r = col.getX();
	textColor.g = col.getY();
	textColor.b = col.getZ();
	SDL_Surface* textSurface = nullptr;
	textSurface = TTF_RenderText_Solid(font,text,textColor);
	if (textSurface != nullptr) {
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rend,
				textSurface);
		SDL_FreeSurface(textSurface);
		SDL_Rect renderRect;
		SDL_QueryTexture(textTexture,NULL,NULL,&renderRect.w,&renderRect.h);
		renderRect.x = p.getX()-renderRect.w/2;
		renderRect.y = p.getY()-renderRect.h;
		SDL_RenderCopy(rend,textTexture,NULL,&renderRect);
		SDL_DestroyTexture(textTexture);
	}
}

void drawStrUR (SDL_Renderer* rend, TTF_Font* font,
		const cVector2& p, const char* text, const cVector4& col) {
	SDL_Color textColor;
	textColor.a = col.getW();
	textColor.r = col.getX();
	textColor.g = col.getY();
	textColor.b = col.getZ();
	SDL_Surface* textSurface = nullptr;
	textSurface = TTF_RenderText_Solid(font,text,textColor);
	if (textSurface != nullptr) {
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rend,
				textSurface);
		SDL_FreeSurface(textSurface);
		SDL_Rect renderRect;
		SDL_QueryTexture(textTexture,NULL,NULL,&renderRect.w,&renderRect.h);
		renderRect.x = p.getX();
		renderRect.y = p.getY()-renderRect.h;
		SDL_RenderCopy(rend,textTexture,NULL,&renderRect);
		SDL_DestroyTexture(textTexture);
	}
}

void drawStrR (SDL_Renderer* rend, TTF_Font* font,
		const cVector2& p, const char* text, const cVector4& col) {
	SDL_Color textColor;
	textColor.a = col.getW();
	textColor.r = col.getX();
	textColor.g = col.getY();
	textColor.b = col.getZ();
	SDL_Surface* textSurface = nullptr;
	textSurface = TTF_RenderText_Solid(font,text,textColor);
	if (textSurface != nullptr) {
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rend,
				textSurface);
		SDL_FreeSurface(textSurface);
		SDL_Rect renderRect;
		SDL_QueryTexture(textTexture,NULL,NULL,&renderRect.w,&renderRect.h);
		renderRect.x = p.getX();
		renderRect.y = p.getY()-renderRect.h/2;
		SDL_RenderCopy(rend,textTexture,NULL,&renderRect);
		SDL_DestroyTexture(textTexture);
	}
}

void drawStrDR (SDL_Renderer* rend, TTF_Font* font,
		const cVector2& p, const char* text, const cVector4& col) {
	SDL_Color textColor;
	textColor.a = col.getW();
	textColor.r = col.getX();
	textColor.g = col.getY();
	textColor.b = col.getZ();
	SDL_Surface* textSurface = nullptr;
	textSurface = TTF_RenderText_Solid(font,text,textColor);
	if (textSurface != nullptr) {
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rend,
				textSurface);
		SDL_FreeSurface(textSurface);
		SDL_Rect renderRect;
		SDL_QueryTexture(textTexture,NULL,NULL,&renderRect.w,&renderRect.h);
		renderRect.x = p.getX();
		renderRect.y = p.getY();
		SDL_RenderCopy(rend,textTexture,NULL,&renderRect);
		SDL_DestroyTexture(textTexture);
	}
}

void drawStrD (SDL_Renderer* rend, TTF_Font* font,
		const cVector2& p, const char* text, const cVector4& col) {
	SDL_Color textColor;
	textColor.a = col.getW();
	textColor.r = col.getX();
	textColor.g = col.getY();
	textColor.b = col.getZ();
	SDL_Surface* textSurface = nullptr;
	textSurface = TTF_RenderText_Solid(font,text,textColor);
	if (textSurface != nullptr) {
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rend,
				textSurface);
		SDL_FreeSurface(textSurface);
		SDL_Rect renderRect;
		SDL_QueryTexture(textTexture,NULL,NULL,&renderRect.w,&renderRect.h);
		renderRect.x = p.getX()-renderRect.w/2;
		renderRect.y = p.getY();
		SDL_RenderCopy(rend,textTexture,NULL,&renderRect);
		SDL_DestroyTexture(textTexture);
	}
}

void drawStrDL (SDL_Renderer* rend, TTF_Font* font,
		const cVector2& p, const char* text, const cVector4& col) {
	SDL_Color textColor;
	textColor.a = col.getW();
	textColor.r = col.getX();
	textColor.g = col.getY();
	textColor.b = col.getZ();
	SDL_Surface* textSurface = nullptr;
	textSurface = TTF_RenderText_Solid(font,text,textColor);
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

void drawStrL (SDL_Renderer* rend, TTF_Font* font,
		const cVector2& p, const char* text, const cVector4& col) {
	SDL_Color textColor;
	textColor.a = col.getW();
	textColor.r = col.getX();
	textColor.g = col.getY();
	textColor.b = col.getZ();
	SDL_Surface* textSurface = nullptr;
	textSurface = TTF_RenderText_Solid(font,text,textColor);
	if (textSurface != nullptr) {
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rend,
				textSurface);
		SDL_FreeSurface(textSurface);
		SDL_Rect renderRect;
		SDL_QueryTexture(textTexture,NULL,NULL,&renderRect.w,&renderRect.h);
		renderRect.x = p.getX()-renderRect.w;
		renderRect.y = p.getY()-renderRect.h/2;
		SDL_RenderCopy(rend,textTexture,NULL,&renderRect);
		SDL_DestroyTexture(textTexture);
	}
}

void drawStrUL (SDL_Renderer* rend, TTF_Font* font,
		const cVector2& p, const char* text, const cVector4& col) {
	SDL_Color textColor;
	textColor.a = col.getW();
	textColor.r = col.getX();
	textColor.g = col.getY();
	textColor.b = col.getZ();
	SDL_Surface* textSurface = nullptr;
	textSurface = TTF_RenderText_Solid(font,text,textColor);
	if (textSurface != nullptr) {
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rend,
				textSurface);
		SDL_FreeSurface(textSurface);
		SDL_Rect renderRect;
		SDL_QueryTexture(textTexture,NULL,NULL,&renderRect.w,&renderRect.h);
		renderRect.x = p.getX()-renderRect.w;
		renderRect.y = p.getY()-renderRect.h;
		SDL_RenderCopy(rend,textTexture,NULL,&renderRect);
		SDL_DestroyTexture(textTexture);
	}
}

void drawPoint (SDL_Renderer* rend, const cVector2& p,
		const cVector4& col) {
	pixelRGBA(rend,p.getX(),p.getY(),col.getX(),col.getY(),
			col.getZ(),col.getW());
}

void drawLine (SDL_Renderer* rend, const cVector2& p1,
		const cVector2& p2, const cVector4& col) {
	lineRGBA(rend,p1.getX(),p1.getY(),p2.getX(),p2.getY(),
			col.getX(),col.getY(),col.getZ(),col.getW());
}

void drawPoly (SDL_Renderer* rend,
		const std::vector<cVector2>& pList, const cVector4& col) {
	Sint16* vx = new Sint16[pList.size()];
	Sint16* vy = new Sint16[pList.size()];
	for (unsigned int i = 0; i < pList.size(); ++i) {
		vx[i] = pList.at(i).getX();
		vy[i] = pList.at(i).getY();
	}
	polygonRGBA(rend,vx,vy,pList.size(),col.getX(),col.getY(),
			col.getZ(),col.getW());
	delete[] vx;
	delete[] vy;
}

void drawCircle (SDL_Renderer* rend, const cVector2& p,
		const double& rad, const cVector4& col) {
	circleRGBA(rend,p.getX(),p.getY(),rad, col.getX(),col.getY(),
			col.getZ(),col.getW());
}

void drawCross (SDL_Renderer* rend, const cVector2& p,
		const double& l, const cVector4& col) {
	drawLine(rend,cVector2(p.getX()-l/2.0,p.getY()),cVector2(p.getX()+l/2.0,p.getY()),col);
	drawLine(rend,cVector2(p.getX(),p.getY()-l/2.0),cVector2(p.getX(),p.getY()+l/2.0),col);
}
void drawCentrPoint (SDL_Renderer* rend, const cVector2& p,
		const cVector4& col) {
	drawCross(rend,p,6,col);
	drawCircle(rend,p,2,col);
}
