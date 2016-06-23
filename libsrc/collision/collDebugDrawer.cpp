#include "collDebugDrawer.hpp"

cCollDebugDrawer::cCollDebugDrawer (int alpha) {
	colMap_[eObjType::STATIC] = cVector4(alpha,255,0,0);
	colMap_[eObjType::DYNAMIC] = cVector4(alpha,0,255,0);
}

void cCollDebugDrawer::drawObj (const SDL_Renderer* rend, const cCollObj& obj) {
	drawObj(rend,obj,colMap_.at(obj.getObjType()));
}

void cCollDebugDrawer::drawObj (const SDL_Renderer* rend, const cCollObj& obj,
		const cVector4& col) {
	cVector2 objPos = obj.getObjPos();
	double objRotn = obj.getRotation();

	if (auto genCollShape = obj.getGenCollShape().lock()) {
		drawShape(rend,*genCollShape,objPos,objRotn,col);
	}

	if (auto accCollShape = obj.getAccCollShape().lock()) {
		drawComplexShape(rend,*accCollShape,obj.getObjPos(),
				obj.getRotation(),col);
	}
}

void cCollDebugDrawer::drawComplexShape (const SDL_Renderer* rend,
		const sCollShapeNode& shapeNode, const cVector2& posOffset,
		const double& rotnOffset, const cVector4& col) {
	cVector2 shapePos = posOffset+shapeNode.posOffset_;
	double shapeRotn = rotnOffset+shapeNode.rotnOffset_;
	drawShape(rend,*(shapeNode.collShape_.lock()),shapePos,shapeRotn,col);
	for (auto const &listItr : shapeNode.childrenNodeList_) {
		drawComplexShape(rend,*(listItr.lock()),shapePos,shapeRotn,col);
	}
}

void cCollDebugDrawer::drawShape (const SDL_Renderer* rend,
		const cCollShape& shape, const cVector2& shapePos,
		const double& shapeRotn, const cVector4& col) {
	eShapeType shapeType = shape.getShapeType();
	if (shapeType == eShapeType::POLY) {
		std::vector<cVector2> ptList = shape.getData();
		if (shapeRotn != 0.0) {
			cMatrix rotnMatrix = rotnTransform(shapeRotn);
			for (auto& ptListItr : ptList)
				ptListItr = rotnMatrix*ptListItr+shapePos;
		}
		else {
			for (auto& ptListItr : ptList)
				ptListItr += shapePos;
		}
		ptList.push_back(*ptList.begin());
		drawPoly(const_cast<SDL_Renderer*>(rend),ptList,col);
	}
	else if (shapeType == eShapeType::CIRCLE) {
		drawCircle(const_cast<SDL_Renderer*>(rend),shapePos,
				shape.getData().at(0).getX(),col);
	}
	else if (shapeType == eShapeType::LINE) {
		cVector2 p1,
				 p2,
				 tmpPoint;
		bool isP1Set = false,
			 isP2Set = false;
		cVector2 dir = shape.getData().at(0);
		dir = rotnTransform(shapeRotn)*dir;
		// Points for the asymptotes
		cVector2 aP1(0.0,0.0),
				 aP2(0.0,SCREEN_HEIGHT),
				 aP3(SCREEN_WIDTH,0.0);
		// Directions for the asymptotes
		cVector2 dirX(1.0,0.0),
				 dirY(0.0,1.0);
		if(lineIntersection(shapePos,dir,aP1,dirY,tmpPoint) == true) { 
			if (isWithinRange(0.0,SCREEN_WIDTH,tmpPoint.getX()) == true &&
					isWithinRange(0.0,SCREEN_HEIGHT,tmpPoint.getY()) == true) {
				p1 = tmpPoint;
				isP1Set = true;
			}
		}
		if(lineIntersection(shapePos,dir,aP1,dirX,tmpPoint) == true) { 
			if (isWithinRange(0.0,SCREEN_WIDTH,tmpPoint.getX()) == true &&
					isWithinRange(0.0,SCREEN_HEIGHT,tmpPoint.getY()) == true) {
				if (isP1Set == false) {
					p1 = tmpPoint;
					isP1Set = true;
				}
				else if (p1 != tmpPoint) {
					p2 = tmpPoint;
					isP2Set = true;
				}
			}
		}
		if(lineIntersection(shapePos,dir,aP2,dirX,tmpPoint) == true) { 
			if (isWithinRange(0.0,SCREEN_WIDTH,tmpPoint.getX()) == true &&
					isWithinRange(0.0,SCREEN_HEIGHT,tmpPoint.getY()) == true) {
				if (isP1Set == false) {
					p1 = tmpPoint;
					isP1Set = true;
				}
				else if (isP2Set == false && p1 != tmpPoint) {
					p2 = tmpPoint;
					isP2Set = true;
				}
			}
		}
		if(lineIntersection(shapePos,dir,aP3,dirY,tmpPoint) == true) { 
			if (isWithinRange(0.0,SCREEN_WIDTH,tmpPoint.getX()) == true &&
					isWithinRange(0.0,SCREEN_HEIGHT,tmpPoint.getY()) == true) {
				if (isP1Set == false) {
					p1 = tmpPoint;
					isP1Set = true;
				}
				else if (isP2Set == false && p1 != tmpPoint) {
					p2 = tmpPoint;
					isP2Set = true;
				}
			}
		}
		drawLine(const_cast<SDL_Renderer*>(rend),p1,p2,col);
	}
	else if (shapeType == eShapeType::POINT) {
		drawPoint(const_cast<SDL_Renderer*>(rend),shapePos,col);
	}
	drawCentrPoint(const_cast<SDL_Renderer*>(rend),shapePos,col);
}