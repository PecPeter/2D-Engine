#ifndef COLLBROADPHASE_HPP
#define COLLBROADPHASE_HPP

#include <forward_list>
#include <map>
#include <memory>
#include <utility>
#include <vector>

//#include "collObject.hpp"
#include "../entity/entity.hpp"
#include "collPair.hpp"

typedef std::forward_list<cCollPair> pairCont;
typedef std::vector<std::unique_ptr<cEntity>> objCont;

//maybe make these templated so that the queue doesnt have to be hardcoded,
//same with the vector (it may change in the future);
class cCollBroadphase {
	public:
		cCollBroadphase (void);
		virtual ~cCollBroadphase (void);

		//maybe make one that takes 2 lists, 1 dynamic and the other static.
		//This should make pairing easier
		virtual void genList (pairCont& pairList,
				const objCont& objList) const = 0;
		virtual void genList (pairCont& pairList, const objCont& objListDyn,
				const objCont& objListStatic) const = 0;
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
		void genList (pairCont& pairList, const objCont& objList) const;
		void genList (pairCont& pairList, const objCont& objListDyn,
				const objCont& objListStatic) const;
};

//Grid based broadphase
/*
class cGridBroadphase : public cCollBroadphase {
	public:
		cGridBroadphase (double worldMinX, double worldMinY, double worldMaxX,
			double worldMaxY);
		cGridBroadphase (cVector2 worldMin, cVector2 worldMax);

	private:
		cVector2 worldMinDim_,
				 worldMaxDim_;
};
*/

#endif
