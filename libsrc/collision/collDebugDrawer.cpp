#include "collDebugDrawer.hpp"

cCollDebugDrawer::cCollDebugDrawer (int alpha) {
	int alphaLevel = alpha;
	if (alpha > 255)
		alphaLevel = 255;
	else if (alpha < 0)
		alphaLevel = 0;

	colIndex statAndAct(eEntityType::STATIC,true),
			 statAndInact(eEntityType::STATIC,false),
			 dynAndAct(eEntityType::DYNAMIC,true),
			 dynAndInact(eEntityType::DYNAMIC,false),
			 kinAndAct(eEntityType::KINEMATIC,true),
			 kinAndInact(eEntityType::KINEMATIC,false);

	colMap_[statAndAct] = cVector4(alphaLevel,255,0,0);
	colMap_[statAndInact] = cVector4(alphaLevel,255,128,128);
	colMap_[dynAndAct] = cVector4(alphaLevel,0,255,0);
	colMap_[dynAndInact] = cVector4(alphaLevel,128,255,128);
	colMap_[kinAndAct] = cVector4(alphaLevel,0,0,255);
	colMap_[kinAndInact] = cVector4(alphaLevel,128,128,255);
}

void cCollDebugDrawer::drawEnt (const SDL_Renderer* rend, const cEntity& ent)
{
	const cPosComp entPos = ent.getPosComp();
	cMatrix rotnMatrix = rotnTransform(ent.getRotn());
	const std::vector<cEntityNode> nodeList = ent.getNodes();
	std::map<int,cPosComp> nodeOffset = getNodeOffset(nodeList);
	// Iterate through the cEntityNode vector of the cEntity class
	// and draw each shape
	for (const auto& itr : nodeList)
	{
		// Calculate the positions at which the different shapes will be at,
		// rotating them by the amount that the entity is rotated by
		cPosComp shapePos = nodeOffset.at(itr.getId());
		shapePos.setPos(rotnMatrix*shapePos.getPos()+entPos.getPos());
		shapePos.setRotn(shapePos.getRotn()+entPos.getRotn());

		const cCollShape collShape = itr.getCollComp().getCollShape();

		colIndex index(ent.getType(),ent.getNodeActivity(itr.getId()));
		cVector4 col = colMap_.at(index);

		drawShape(rend,collShape,shapePos.getPos(),shapePos.getRotn(),col);
	}
}

void cCollDebugDrawer::drawEnt (const SDL_Renderer* rend, const cEntity& ent,
		const cVector4& col) {
	const cPosComp entPos = ent.getPosComp();
	cMatrix rotnMatrix = rotnTransform(ent.getRotn());
	const std::vector<cEntityNode> nodeList = ent.getNodes();
	std::map<int,cPosComp> nodeOffset = getNodeOffset(nodeList);
	// Iterate through the cEntityNode vector of the cEntity class
	// and draw each shape
	for (const auto& itr : nodeList) {
		// Calculate the positions at which the different shapes will be at,
		// rotating them by the amount that the entity is rotated by
		cPosComp shapePos = nodeOffset.at(itr.getId());
		shapePos.setPos(rotnMatrix*shapePos.getPos()+entPos.getPos());
		shapePos.setRotn(shapePos.getRotn()+entPos.getRotn());

		const cCollShape collShape = itr.getCollComp().getCollShape();
		drawShape(rend,collShape,shapePos.getPos(),shapePos.getRotn(),col);
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
		// TODO: Make this a function to shorten the length of this func
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
