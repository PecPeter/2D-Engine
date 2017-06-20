#ifndef COLLBROADPHASE_HPP
#define COLLBROADPHASE_HPP

#include <cmath>
#include <forward_list>
#include <map>
#include <memory>
#include <utility>
#include <vector>
#include <string>
#include <exception>

#include "../entity/entity.hpp"
#include "../entity/entityNode.hpp"
#include "collPair.hpp"
#include "collShape.hpp"

typedef std::forward_list<cCollPair> pairCont;
typedef std::vector<std::shared_ptr<cEntity>> objCont;

enum class eBroadphaseType
{
	GENERAL,
	GRID
};

//maybe make these templated so that the queue doesnt have to be hardcoded,
//same with the vector (it may change in the future);
class cCollBroadphase {
	public:
		cCollBroadphase (void);
		virtual ~cCollBroadphase (void);

		//maybe make one that takes 2 lists, 1 dynamic and the other static.
		//This should make pairing easier
		virtual void genList (pairCont& pairList,
				objCont& objList) = 0;
		virtual void genList (pairCont& pairList, objCont& objListDyn,
				objCont& objListStatic) = 0;
		void addCollMask (int objMask, int collMask);
	protected:
		bool compareCollMask (int objMask1, int objMask2) const;
		std::map<int,int> collMaskMap_;
};

// This is a "general" broadphase. It just takes the list and 
// matches every object with another (tests EVERYTHING).
class cGenBroadphase : public cCollBroadphase {
	public:
		cGenBroadphase (void);
		~cGenBroadphase(void);
		void genList (pairCont& pairList, objCont& objList);
		void genList (pairCont& pairList, objCont& objListDyn,
				objCont& objListStatic);
};

//Grid based broadphase - updates both the static and dynamic lists every update
class cGridBroadphase : public cCollBroadphase {
	public:
		cGridBroadphase (double worldMinX, double worldMinY, double worldMaxX,
			double worldMaxY);
		cGridBroadphase (cVector2 worldMin, cVector2 worldMax);
		~cGridBroadphase (void);

		void genList (pairCont& pairList, objCont& objList);
		void genList (pairCont& pairList, objCont& objListDyn,
				objCont& objListStatic);

		void setCellSize (double cellWidth, double cellHeight);
		void setCellSize (const cVector2& cellDim);
	private:
		void sizeCellList (void);
		bool checkValidPair (const cEntity& ent1, const cEntity& ent2,
				std::map<std::string,bool>& pairHashList);

		cVector2 worldMinDim_,
				 worldMaxDim_,
				 cellDim_;
		int numRows_,
			numCols_;
};

// Grid based broadphase - keeps the static list, and updates dynamic list only,
// unless told to update static as well...

cVector2 getBoundingAabbDim (const cEntity& entity);

#endif
