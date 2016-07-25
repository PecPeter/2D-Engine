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

void cGenBroadphase::genList (pairCont& pairList, const objCont& objList) const {
	for (objCont::const_iterator cItr1 = objList.begin();
			cItr1 != objList.end(); ++cItr1) {
		objCont::const_iterator cItr2 = cItr1;
		++cItr2;
		for (; cItr2 != objList.end(); ++cItr2) {
			if (compareCollMask((*cItr1)->getMask(), (*cItr2)->getMask()) == true)
				pairList.push_front(cCollPair(*(*cItr1),*(*cItr2)));
		}
	}
}

void cGenBroadphase::genList (pairCont& pairList, const objCont& objListDyn,
		const objCont& objListStatic) const {
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
