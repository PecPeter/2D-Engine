#ifndef ENTITYSTRUCTURE_HPP
#define ENTITYSTRUCTURE_HPP

#include <algorithm>
#include <memory>

#include "./components/positionComponent.hpp"
#include "./components/collisionComponent.hpp"

class cEntitySensor {
	public:
		cEntitySensor (const cPosComp& posOffset, const cCollComp& collComp);

		const cPosComp& getPosComp (void) const;

		const cCollComp& getCollComp (void) const;

	protected:
		cPosComp posComp_;	// Offset for this structure from the 'parent'
		cCollComp collComp_;
};

class cEntityStruct : public cEntitySensor {
	public:
		cEntityStruct (const cPosComp& posOffset, const cCollComp& collComp);
	private:
//		cRendComp rendComp_;
};

enum class eNodeType {
	SENSOR,
	STRUCT
};

class cEntityNode {
	public:
		// Add someway to toggle whether the node is active or not
		// This constructor creates a sensor cEntityNode
		cEntityNode (int nodeId, const cPosComp& posOffset,
				const cCollComp& collComp, int parentNodeId = 0);
		// This constructor creates a struct cEntityNode
		cEntityNode (int nodeId, const cPosComp& posOffset,
				const cCollComp& collComp, int dummyVar, int parentNodeId = 0);

		int getId (void) const;
		int getParentId (void) const;

		eNodeType getNodeType (void) const;

		const cEntitySensor* getSensor (void) const;
		const cEntityStruct* getStruct (void) const;
	private:
		int nodeId_; // Use the id to link the different levels and children together.
		int parentNodeId_;
		bool nodeActivity_;
		eNodeType nodeType_;
		std::unique_ptr<cEntitySensor> nodeInfo_;
};

#endif
