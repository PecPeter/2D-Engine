#include "collDebugDrawer.hpp"

cCollDebugDrawer::cCollDebugDrawer (int alpha) {
	colMap_[eObjType::STATIC] = cVector4(alpha,255,0,0);
	colMap_[eObjType::DYNAMIC] = cVector4(alpha,0,255,0);
}

void cCollDebugDrawer::drawObj (SDL_Renderer* rend, const cCollObj& obj) {
	drawObj(rend,obj,colMap_.at(obj.getObjType()));
}

void cCollDebugDrawer::drawObj (SDL_Renderer* rend, const cCollObj& obj,
		const cVector4& col) {
	cVector2 objPos = obj.getObjPos();
	eShapeType shapeType = obj.getCollShape()->getShapeType();
	
	if (shapeType == eShapeType::POLY) {
		std::vector<cVector2> ptList = obj.getCollShape()->getData();
		double objRotn = obj.getRotation();
		if (objRotn != 0.0) {
			cMatrix rotnMatrix = rotnTransform(obj.getRotation());
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
		cVector2 p1,
				 p2,
				 tmpPoint;
		bool isP1Set = false,
			 isP2Set = false;
		cVector2 dir = obj.getCollShape()->getData().at(0);
		dir = rotnTransform(obj.getRotation())*dir;
		// Points for the asymptotes
		cVector2 aP1(0.0,0.0),
				 aP2(0.0,SCREEN_HEIGHT),
				 aP3(SCREEN_WIDTH,0.0);
		// Directions for the asymptotes
		cVector2 dirX(1.0,0.0),
				 dirY(0.0,1.0);
		if(lineIntersection(objPos,dir,aP1,dirY,tmpPoint) == true) { 
			if (isWithinRange(0.0,SCREEN_WIDTH,tmpPoint.getX()) == true &&
					isWithinRange(0.0,SCREEN_HEIGHT,tmpPoint.getY()) == true) {
				p1 = tmpPoint;
				isP1Set = true;
			}
		}
		if(lineIntersection(objPos,dir,aP1,dirX,tmpPoint) == true) { 
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
		if(lineIntersection(objPos,dir,aP2,dirX,tmpPoint) == true) { 
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
		if(lineIntersection(objPos,dir,aP3,dirY,tmpPoint) == true) { 
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
		drawLine(rend,p1,p2,col);
	}
	else if (shapeType == eShapeType::POINT) {
		drawPoint(rend,objPos,col);
	}
	drawCentrPoint(rend,objPos,col);
}
