#ifndef ENTITYNODE_HPP
#define ENTITYNODE_HPP

#include <algorithm>
#include <memory>

#include "./components/positionComponent.hpp"
#include "./components/collisionComponent.hpp"

class cEntityNode {
	public:
		// Add someway to toggle whether the node is active or not
		cEntityNode (int nodeId, const cPosComp& posOffset,
				const cCollComp& collComp, int parentNodeId = 0);

		int getId (void) const;
		int getParentId (void) const;

		const cPosComp& getPosComp (void) const;
		const cCollComp& getCollComp (void) const;

		int getComponentMask (void) const;

	private:
		int nodeId_; // Use the id to link the different levels and children together.
		int parentNodeId_;
		bool nodeActivity_;

		// Data storage objects
		cPosComp posComp_;	//Offset from cEntity pos
		cCollComp collComp_;

		// Additional storage objects are maintained as unique_ptrs
		// Add an entry for the bitwise
		int componentMask_;
};

#endif
