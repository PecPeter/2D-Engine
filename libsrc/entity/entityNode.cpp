#include "entityNode.hpp"

cEntityNode::cEntityNode (int nodeId, const cPosComp& posOffset,
		const cCollComp& collComp, int parentNodeId) :
		nodeId_(nodeId), parentNodeId_(parentNodeId),
		nodeActivity_(true), posComp_(posOffset),
		collComp_(collComp), componentMask_(0) {}

int cEntityNode::getId (void) const {
	return nodeId_;
}

int cEntityNode::getParentId (void) const {
	return parentNodeId_;
}

const cPosComp& cEntityNode::getPosComp (void) const {
	return posComp_;
}

const cCollComp& cEntityNode::getCollComp (void) const {
	return collComp_;
}

int cEntityNode::getComponentMask (void) const {
	return componentMask_;
}
