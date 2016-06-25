#include "entityStructure.hpp"

cEntityStructure::cEntityStructure (const cPosComp& posOffset,
		const cCollComp& collComp) :
		posOffset_(posOffset), collComp_(collComp) {}

cEntityStructure::cEntityStructure (const cPosComp& posOffset,
		const cCollComp& collComp,
		const std::vector<std::weak_ptr<cEntityStructure>>& childrenList) :
		posOffset_(posOffset), collComp_(collComp), childrenList_(childrenList) {}

bool cEntityStructure::getActivity (void) {
	return isActive_;
}

void cEntityStructure::setActivity (bool activity) {
	isActive_ = activity;
}

const int& cEntityStructure::getId (void) const {
	return id_;
}

const cCollComp& cEntityStructure::getCollComp (void) const {
	return collComp_;
}

void cEntityStructure::addChild (
		const std::shared_ptr<cEntityStructure>& child) {
	childrenList_.push_back(std::weak_ptr<cEntityStructure>(child));
}

void cEntityStructure::removeChild (int childId) {
	for (std::vector<std::weak_ptr<cEntityStructure>>::iterator itr = 
			childrenList_.begin(); itr != childrenList_.end(); ++itr) {
		std::shared_ptr<cEntityStructure> tempPtr(itr->lock());
		if (tempPtr != nullptr && tempPtr->getId() == childId) {
			std::iter_swap(itr,childrenList_.end());
			childrenList_.pop_back();
			return;
		}
	}
}

void cEntityStructure::getChild (int childId,
		std::weak_ptr<cEntityStructure>& ptr) const {
	for (const auto& itr : childrenList_) {
		std::shared_ptr<cEntityStructure> tempPtr(itr.lock());
		if (tempPtr != nullptr && tempPtr->getId() == childId) {
			ptr = itr;
			return;
		}
	}
}
