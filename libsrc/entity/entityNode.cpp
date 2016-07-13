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

cEntityNode::cEntityNode (int nodeId, const cPosComp& posOffset,
		const cCollComp& collComp, int parentNodeId) :
		nodeId_(nodeId), parentNodeId_(parentNodeId),
		nodeType_(eNodeType::SENSOR) {
	nodeInfo_ = std::make_unique<cEntitySensor>(posOffset,collComp);
}

cEntityNode::cEntityNode (int nodeId, const cPosComp& posOffset,
		const cCollComp& collComp, int dummyVar, int parentNodeId) :
		nodeId_(nodeId), parentNodeId_(parentNodeId),
		nodeType_(eNodeType::STRUCT) {
	nodeInfo_ = std::make_unique<cEntityStruct>(posOffset,collComp);
}

int cEntityNode::getId (void) const {
	return nodeId_;
}

int cEntityNode::getParentId (void) const {
	return parentNodeId_;
}

eNodeType cEntityNode::getNodeType (void) const {
	return nodeType_;
}

const cEntitySensor*  cEntityNode::getSensor (void) const {
	if (nodeType_ == eNodeType::SENSOR)
		return nodeInfo_.get();
	return nullptr;
}

const cEntityStruct* cEntityNode::getStruct (void) const {
	if (nodeType_ == eNodeType::STRUCT)
		return static_cast<const cEntityStruct*>(nodeInfo_.get());
	return nullptr;
}
