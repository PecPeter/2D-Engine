#ifndef ENTITYSTRUCTURE_HPP
#define ENTITYSTRUCTURE_HPP

#include <algorithm>
#include <memory>

#include "./components/positionComponent.hpp"
#include "./components/collisionComponent.hpp"

enum class eNodeType {
	SENSOR,
	STRUCT
};

class cEntitySensor {
	public:
		cEntitySensor (const cPosComp& posOffset, const cCollComp& collComp);

		const cPosComp& getPosComp (void) const;

		const cCollComp& getCollComp (void) const;

	protected:
		cPosComp posComp_;	// Offset for this structure from the 'parent'
		cCollComp collComp_;	// TODO change this to a smart pointer or something
};

class cEntityStruct : public cEntitySensor {
	public:
		cEntityStruct (const cPosComp& posOffset, const cCollComp& collComp);
	private:
//		cRendComp rendComp_;
};

class cEntityNode {
	public:
		// Add someway to toggle whether the node is active or not
		cEntityNode (eNodeType nodeType,
				const std::shared_ptr<cEntitySensor>& nodeInfo);

		int getId (void) const;
		int getParentId (void) const;

		eNodeType getNodeType (void) const;

		std::shared_ptr<cEntitySensor> getSensor (void) const;
		std::shared_ptr<cEntityStruct> getStruct (void) const;
	private:
		int nodeId_; // Use the id to link the different levels and children together.
		int parentNodeId_;
		bool nodeActivity_;
		eNodeType nodeType_;
		std::weak_ptr<cEntitySensor> nodeInfo_;
};
/*
struct sEntityNode {
	public:
		enum class eNodeType {
			SENSOR,
			STRUCT
		} nodeType;
		std::weak_ptr<cEntitySensor> nodeInfo_;
		std::weak_ptr<sEntityNode

typedef std::vector<std::weak_ptr<cEntitySensor>> SensorListCont;
typedef std::vector<std::weak_ptr<cEntityStruct>> StructListCont;

class cEntityNode {
	public:
		cEntityNode (const StructListCont& structList);
		cEntityNode (const StructListCont& structList,
				const SensorListCont& sensorList);

		void addStruct (const std::shared_ptr<cEntityStruct>& structure);
		void removeStruct (int structId);
		void getStruct (int structId, std::weak_ptr<cEntityStruct>& ptr) const;

		void addSensor (const std::shared_ptr<cEntitySensor>& sensor);
		void removeSensor (int sensorId);
		void getSensor (int sensorId, std::weak_ptr<cEntitySensor>& ptr) const;

	private:
		std::weak_ptr<cEntityStruct> parentStructure_;
		StructListCont structList_;
		SensorListCont sensorList_;
};
*/
#endif
