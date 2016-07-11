#include "entityNode.hpp"

cEntitySensor::cEntitySensor (const cPosComp& posOffset,
		const cCollComp& collComp) : posComp_(posOffset),
		collComp_(collComp) {}

const cPosComp& cEntitySensor::getPosComp (void) const {
	return posComp_;
}

const cCollComp& cEntitySensor::getCollComp (void) const {
	return collComp_;
}

cEntityStruct::cEntityStruct (const cPosComp& posOffset,
		const cCollComp& collComp) :
		cEntitySensor(posOffset,collComp) {}


cEntityNode::cEntityNode (eNodeType nodeType,
		const std::shared_ptr<cEntitySensor>& nodeInfo) :
		nodeId_(0), parentNodeId_(0), nodeType_(nodeType), nodeInfo_(nodeInfo) {}

int cEntityNode::getId (void) const {
	return nodeId_;
}

int cEntityNode::getParentId (void) const {
	return parentNodeId_;
}

eNodeType cEntityNode::getNodeType (void) const {
	return nodeType_;
}

std::shared_ptr<cEntitySensor>  cEntityNode::getSensor (void) const {
	if (nodeType_ == eNodeType::SENSOR)
		return nodeInfo_.lock();
	return nullptr;
}

std::shared_ptr<cEntityStruct> cEntityNode::getStruct (void) const {
	if (nodeType_ == eNodeType::STRUCT)
		return std::static_pointer_cast<cEntityStruct>(nodeInfo_.lock());
	return nullptr;
}
