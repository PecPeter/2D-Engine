#ifndef ENTITYSTRUCTURE_HPP
#define ENTITYSTRUCTURE_HPP

#include <algorithm>
#include <memory>

#include "./components/positionComponent.hpp"
#include "./components/collisionComponent.hpp"

class cEntityStructure {
	public:
		cEntityStructure (const cPosComp& posOffset, const cCollComp& collComp);
		cEntityStructure (const cPosComp& posOffset, const cCollComp& collComp,
				const std::vector<std::weak_ptr<cEntityStructure>>& childrenList);
		~cEntityStructure (void);

		bool getActivity (void);
		void setActivity (bool activity);

		const int& getId (void) const;

		const cCollComp& getCollComp (void) const;

		void addChild (const std::shared_ptr<cEntityStructure>& child);
		void removeChild (int childId);
		void getChild (int childId, std::weak_ptr<cEntityStructure>& ptr) const;

	protected:
		bool isActive_,
			 isSensor_;
		int id_;
		cPosComp posOffset_;	// Offset for this structure from the 'parent'
		cCollComp collComp_;	// TODO change this to a smart pointer or something
//		std::weak_ptr<cRendComp> rendComp_;

		std::vector<std::weak_ptr<cEntityStructure>> childrenList_;
};

#endif
