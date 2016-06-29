#include "entityNode.hpp"

cEntitySensor::cEntitySensor (const cPosComp& posOffset,
		const cCollComp& collComp, int id, bool activity) :
		posComp_(posOffset), collComp_(collComp), id_(id),
		isActive_(activity) {}

const cPosComp& cEntitySensor::getPosComp (void) const {
	return posComp_;
}

const cCollComp& cEntitySensor::getCollComp (void) const {
	return collComp_;
}

const int& cEntitySensor::getId (void) const {
	return id_;
}

bool cEntitySensor::getActivity (void) {
	return isActive_;
}

void cEntitySensor::setActivity (bool activity) {
	isActive_ = activity;
}

cEntityStruct::cEntityStruct (const cPosComp& posOffset,
		const cCollComp& collComp, int id, bool activity) :
		cEntitySensor(posOffset,collComp,id,activity) {}

cEntityNode::cEntityNode (const StructListCont& structList) :
		structList_(structList) {}

cEntityNode::cEntityNode (const StructListCont& structList,
		const SensorListCont& sensorList) : structList_(structList),
		sensorList_(sensorList) {}


void cEntityNode::addStruct (
		const std::shared_ptr<cEntityStruct>& structure) {
	structList_.push_back(std::weak_ptr<cEntityStruct>(structure));
}

void cEntityNode::removeStruct (int structId) {
	for (std::vector<std::weak_ptr<cEntityStruct>>::iterator itr = 
			structList_.begin(); itr != structList_.end(); ++itr) {
		std::shared_ptr<cEntityStruct> tempPtr(itr->lock());
		if (tempPtr != nullptr && tempPtr->getId() == structId) {
			std::iter_swap(itr,structList_.end());
			structList_.pop_back();
			return;
		}
	}
}

void cEntityNode::getStruct (int structId,
		std::weak_ptr<cEntityStruct>& ptr) const {
	for (const auto& itr : structList_) {
		std::shared_ptr<cEntityStruct> tempPtr(itr.lock());
		if (tempPtr != nullptr && tempPtr->getId() == structId) {
			ptr = itr;
			return;
		}
	}
}

void cEntityNode::addSensor (
		const std::shared_ptr<cEntitySensor>& sensor) {
	sensorList_.push_back(std::weak_ptr<cEntitySensor>(sensor));
}

void cEntityNode::removeSensor (int sensorId) {
	for (std::vector<std::weak_ptr<cEntitySensor>>::iterator itr = 
			sensorList_.begin(); itr != sensorList_.end(); ++itr) {
		std::shared_ptr<cEntitySensor> tempPtr(itr->lock());
		if (tempPtr != nullptr && tempPtr->getId() == sensorId) {
			std::iter_swap(itr,sensorList_.end());
			sensorList_.pop_back();
			return;
		}
	}
}

void cEntityNode::getSensor (int sensorId,
		std::weak_ptr<cEntitySensor>& ptr) const {
	for (const auto& itr : sensorList_) {
		std::shared_ptr<cEntitySensor> tempPtr(itr.lock());
		if (tempPtr != nullptr && tempPtr->getId() == sensorId) {
			ptr = itr;
			return;
		}
	}
}
