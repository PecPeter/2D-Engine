#ifndef ENTITYSTRUCTURE_HPP
#define ENTITYSTRUCTURE_HPP

#include <algorithm>
#include <memory>

#include "./components/positionComponent.hpp"
#include "./components/collisionComponent.hpp"

class cEntitySensor {
	public:
		cEntitySensor (const cPosComp& posOffset, const cCollComp& collComp,
					   int id, bool activity = true);
		~cEntitySensor (void);

		const cPosComp& getPosComp (void) const;

		const cCollComp& getCollComp (void) const;

		const int& getId (void) const;

		bool getActivity (void);
		void setActivity (bool activity);

	protected:
		cPosComp posComp_;	// Offset for this structure from the 'parent'
		cCollComp collComp_;	// TODO change this to a smart pointer or something
		int id_;
		bool isActive_;
};

class cEntityStruct : public cEntitySensor {
	public:
		cEntityStruct (const cPosComp& posOffset, const cCollComp& collComp,
					   int id, bool activity = true);
	private:
//		cRendComp rendComp_;
};

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

#endif
