#include "collBroadphase.hpp"

cCollBroadphase::cCollBroadphase (void) {
	//The default is from collObject.hpp
	collMaskMap_.insert(std::pair<int,int>(DEFAULT_ENTITYMASK,1));
}

cCollBroadphase::~cCollBroadphase (void) {
	collMaskMap_.clear();
}

void cCollBroadphase::addCollMask (int objMask, int collMask) {
	collMaskMap_.insert(std::pair<int,int>(objMask,collMask));
}

bool cCollBroadphase::compareCollMask (int objMask1, int objMask2) const {
	int collMask1 = collMaskMap_.at(objMask1),
		collMask2 = collMaskMap_.at(objMask2);
	if (((collMask1&objMask2)*(collMask2&objMask1)) != 0)
		return true;
	return false;
}

cGenBroadphase::cGenBroadphase (void) {}

cGenBroadphase::~cGenBroadphase (void) {}

void cGenBroadphase::genList (pairCont& pairList, objCont& objList)
{
	for (objCont::iterator cItr1 = objList.begin();
			cItr1 != objList.end(); ++cItr1) {
		objCont::iterator cItr2 = cItr1;
		++cItr2;
		for (; cItr2 != objList.end(); ++cItr2) {
			if (compareCollMask((*cItr1)->getMask(), (*cItr2)->getMask()) == true)
				pairList.push_front(cCollPair(*(*cItr1),*(*cItr2)));
		}
	}
}

void cGenBroadphase::genList (pairCont& pairList, objCont& objListDyn,
		objCont& objListStatic)
{
	for (objCont::const_iterator cItr1 = objListDyn.begin();
			cItr1 != objListDyn.end(); ++cItr1) {
		objCont::const_iterator cItr2 = cItr1;
		++cItr2;
		for (; cItr2 != objListDyn.end(); ++cItr2) {
			if (compareCollMask((*cItr1)->getMask(),(*cItr2)->getMask()) == true)
				pairList.push_front(cCollPair(*(*cItr1),*(*cItr2)));
		}
		for (objCont::const_iterator cItr3 = objListStatic.begin();
				cItr3 != objListStatic.end(); ++cItr3) {
			if (compareCollMask((*cItr1)->getMask(),(*cItr3)->getMask()) == true)
				pairList.push_front(cCollPair(*(*cItr1),*(*cItr3)));
		}
	}
}

cGridBroadphase::cGridBroadphase (double worldMinX, double worldMinY,
		double worldMaxX, double worldMaxY) : 
	cGridBroadphase(cVector2(worldMinX,worldMinY),cVector2(worldMaxX,
				worldMaxY)) {}

cGridBroadphase::cGridBroadphase (cVector2 worldMin, cVector2 worldMax) : 
	worldMinDim_(worldMin), worldMaxDim_(worldMax),
	cellDim_(cVector2(10,10))
{
	sizeCellList();
}

cGridBroadphase::~cGridBroadphase (void)
{
}

void cGridBroadphase::genList (pairCont& pairList, objCont& objList)
{
	std::vector<objCont> cellList;
	cellList.resize(numRows_*numCols_);
	std::map<std::string,bool> pairHashList;

	// Go through the objList and place the pointers in the appropriate cells
	for (objCont::iterator cItr = objList.begin();
			cItr != objList.end(); ++cItr)
	{
		const cEntity& entity = **cItr;
		cVector2 aabb = getBoundingAabbDim(entity);
		cVector2 pos = entity.getPosComp().getPos();

		// Find the cell indices...
		int minRow = (pos.getX()-aabb.getX())/cellDim_.getX(),
			maxRow = (pos.getX()+aabb.getX())/cellDim_.getX(),
			minCol = (pos.getY()-aabb.getY())/cellDim_.getY(),
			maxCol = (pos.getY()+aabb.getY())/cellDim_.getY();

		// Iterate through the appropriate cells and add the entity reference
		for (int row = minRow; row <= maxRow; ++row)
		{
			for (int col = minCol; col <= maxCol; ++col)
			{
				int index = row*numCols_+col;
				cellList.at(index).push_back(*cItr);
			}
		}
	}

	// Iterate through all of the cells and make the pairs;
	for (auto& itr : cellList)
	{
		if (itr.size() >= 2)
		{
			// Make pairs for every entity in the vector
			for (objCont::iterator cItr1 = itr.begin();
					cItr1 != itr.end(); ++cItr1)
			{
				auto tmpItr = cItr1;
				for (objCont::iterator cItr2 = ++tmpItr;
						cItr2 != itr.end(); ++cItr2)
				{
					if (checkValidPair(**cItr1,**cItr2,pairHashList) == true)
					{
						pairList.push_front(cCollPair(**cItr1,**cItr2));
					}
				}
			}
		}
	}
}

void cGridBroadphase::genList (pairCont& pairList, objCont& objListDyn,
				objCont& objListStatic)
{
	std::vector<objCont> cellList;
	cellList.resize(numRows_*numCols_);
	std::map<std::string,bool> pairHashList;

	// Go through the objList and place the pointers in the appropriate cells
	for (objCont::iterator cItr = objListDyn.begin();
			cItr != objListDyn.end(); ++cItr)
	{
		const cEntity& entity = **cItr;
		cVector2 aabb = getBoundingAabbDim(entity);
		cVector2 pos = entity.getPosComp().getPos();

		// Find the cell indices...
		int minRow = (pos.getX()-aabb.getX())/cellDim_.getX(),
			maxRow = (pos.getX()+aabb.getX())/cellDim_.getX(),
			minCol = (pos.getY()-aabb.getY())/cellDim_.getY(),
			maxCol = (pos.getY()+aabb.getY())/cellDim_.getY();

		// Iterate through the appropriate cells and add the entity reference
		for (int row = minRow; row <= maxRow; ++row)
		{
			for (int col = minCol; col <= maxCol; ++col)
			{
				int index = row*numCols_+col;
				cellList.at(index).push_back(*cItr);
			}
		}
	}
	for (objCont::iterator cItr = objListStatic.begin();
			cItr != objListStatic.end(); ++cItr)
	{
		const cEntity& entity = **cItr;
		cVector2 aabb = getBoundingAabbDim(entity);
		cVector2 pos = entity.getPosComp().getPos();

		// Find the cell indices...
		int minRow = (pos.getX()-aabb.getX())/cellDim_.getX(),
			maxRow = (pos.getX()+aabb.getX())/cellDim_.getX(),
			minCol = (pos.getY()-aabb.getY())/cellDim_.getY(),
			maxCol = (pos.getY()+aabb.getY())/cellDim_.getY();

		// Iterate through the appropriate cells and add the entity reference
		for (int row = minRow; row <= maxRow; ++row)
		{
			for (int col = minCol; col <= maxCol; ++col)
			{
				int index = row*numCols_+col;
				cellList.at(index).push_back(*cItr);
			}
		}
	}

	// Iterate through all of the cells and make the pairs;
	for (auto& itr : cellList)
	{
		if (itr.size() >= 2)
		{
			// Make pairs for every entity in the vector
			for (objCont::iterator cItr1 = itr.begin();
					cItr1 != itr.end(); ++cItr1)
			{
				auto tmpItr = cItr1;
				for (objCont::iterator cItr2 = ++tmpItr;
						cItr2 != itr.end(); ++cItr2)
				{
					if (checkValidPair(**cItr1,**cItr2,pairHashList) == true)
					{
						pairList.push_front(cCollPair(**cItr1,**cItr2));
					}
				}
			}
		}
	}
}

void cGridBroadphase::setCellSize (double cellWidth, double cellHeight)
{
	cellDim_.setX(cellWidth);
	cellDim_.setY(cellHeight);
	sizeCellList();
}

void cGridBroadphase::setCellSize (const cVector2& cellDim)
{
	cellDim_ = cellDim;
	sizeCellList();
}

void cGridBroadphase::sizeCellList (void)
{
	// Size the vector appropriately
	double worldLength = worldMaxDim_.getX() - worldMinDim_.getX(),
		   worldHeight = worldMaxDim_.getY() - worldMinDim_.getY();
	numRows_ = ceil(worldLength/cellDim_.getX());
	numCols_ = ceil(worldHeight/cellDim_.getY());
}

bool cGridBroadphase::checkValidPair (const cEntity& ent1, 
		const cEntity& ent2, std::map<std::string,bool>& pairHashList) 
{
	// Compare the masks
	if (compareCollMask(ent1.getMask(),ent2.getMask()) == false)
		return false;
	
	// Compare the hashes
	std::string hash1 = std::to_string(ent1.getId()) +
		std::to_string(ent2.getId()),
				hash2 = std::to_string(ent2.getId()) +
		std::to_string(ent1.getId());
	auto mapPair = pairHashList.find(hash1);
	std::pair<const std::string,bool> nullPair (std::string("NULL"),false);

	// Check if mapItr was found
	if (mapPair == pairHashList.end())
	{
		// Not found, check other hash
		mapPair = pairHashList.find(hash2);
		if (mapPair == pairHashList.end())
		{
			// Collision pair hasn't been added yet
			pairHashList[hash1] = true;
		}
		else if ((*mapPair).second == true)
		{
			return false;
		}
	}
	else if ((*mapPair).second == true)
	{
		return false;
	}
	else
	{
		(*mapPair).second = true;
	}
	return true;
}

// The bounding AABB is at the entities position. No other offset is needed.
cVector2 getBoundingAabbDim (const cEntity& entity)
{
	// Iterate through the nodes of the entity to find the min/max positions
	// for an AABB. Can be then rotated by the entity's rotation
	std::vector<cEntityNode> nodeList = entity.getNodes();
	std::map<int, cPosComp> nodeOffsetMap = getNodeOffset(nodeList);
	double minX = 10000, maxX = -10000, minY = 10000, maxY = -10000;
	for (const auto& itr : nodeList)
	{
		// Find the min and max positions
		cCollShape shape = itr.getCollComp().getCollShape();
		double rotn = itr.getPosComp().getRotn();
		cVector2 xPos = minMaxPos(shape,rotn,cVector2(1,0)),
				 yPos = minMaxPos(shape,rotn,cVector2(0,1));
		double nMinX, nMaxX, nMinY, nMaxY;
		nMinX = nodeOffsetMap[itr.getId()].getPos().getX() + xPos.getX() - 
			xPos.getY();
		nMaxX = nodeOffsetMap[itr.getId()].getPos().getX() + xPos.getX() +
			xPos.getY();
		nMinY = nodeOffsetMap[itr.getId()].getPos().getY() + yPos.getX() -
			yPos.getY();
		nMaxY = nodeOffsetMap[itr.getId()].getPos().getY() + yPos.getX() +
			yPos.getY();

		if (nMinX < minX)
			minX = nMinX;
		if (nMaxX > maxX)
			maxX = nMaxX;
		if (nMinY < minY)
			minY = nMinY;
		if (nMaxY > maxY)
			maxY = nMaxY;
	}
	// Rotate the values to get the appropriate size for the AABB
	cVector2 entPos = entity.getPosComp().getPos();
	double entRotn = entity.getPosComp().getRotn();
	cVector2 ptList[4] = {cVector2(minX,minY),
		cVector2(minX,maxY),
		cVector2(maxX,maxY),
		cVector2(maxX,minY)};
	minX = minY = 10000;
	maxX = maxY = -10000;
	for (int i = 0; i < 4; ++i)
	{
		if (entRotn != 0.0)
		{
			ptList[i] = vRotate(ptList[i],entRotn);
		}
		if (ptList[i].getX() > maxX)
			maxX = ptList[i].getX();
		if (ptList[i].getX() < minX)
			minX = ptList[i].getX();
		if (ptList[i].getY() > maxY)
			maxY = ptList[i].getY();
		if (ptList[i].getY() < minY)
			minY = ptList[i].getY();
	}

	double hw = minX > maxX ? minX : maxX,
		hh = minY > maxY ? minY : maxY;
	return cVector2(hw,hh);
}
