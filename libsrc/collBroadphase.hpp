#ifndef COLLBROADPHASE_HPP
#define COLLBROADPHASE_HPP

#include <vector>
#include <deque>

#include "collObject.hpp"
#include "collPair.hpp"

typedef std::deque<cCollPair> pairCont;
typedef std::vector<cCollObj*> objCont;

//maybe make these templated so that the queue doesnt have to be hardcoded,
//same with the vector (it may change in the future);
class cCollBroadphase {
	public:
		cCollBroadphase (void);
		virtual ~cCollBroadphase (void);

		//maybe make one that takes 2 lists, 1 dynamic and the other static.
		//This should make pairing easier
		virtual void genList (pairCont& pairList, const objCont& objList) const = 0;
};

// This is a "general" broadphase. It just takes the list and 
// matches every object with another (tests EVERYTHING).
class cGenBroadphase : public cCollBroadphase {
	public:
		cGenBroadphase (void);
		~cGenBroadphase(void);
		void genList (pairCont& pairList, const objCont& objList) const;
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
