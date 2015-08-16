#include "collBroadphase.hpp"

cCollBroadphase::cCollBroadphase (void) {}

cCollBroadphase::~cCollBroadphase (void) {}

cGenBroadphase::cGenBroadphase (void) {}

cGenBroadphase::~cGenBroadphase (void) {}

void cGenBroadphase::genList (pairCont& pairList, const objCont& objList) const {
	for (objCont::const_iterator cItr1 = objList.begin(); cItr1 != objList.end(); ++cItr1) {
		objCont::const_iterator cItr2 = cItr1;
		++cItr2;
		for (; cItr2 != objList.end(); ++cItr2) {
			pairList.push_front(cCollPair(*cItr1,*cItr2));
		}
	}
}
