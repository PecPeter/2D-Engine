#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <algorithm>
#include <memory>

#include "entityNode.hpp"
#include "./components/positionComponent.hpp"
#include "./components/collisionComponent.hpp"

enum class eEntityState {
	STATIC,
	DYNAMIC,
	KINEMATIC
};

enum class eEntityType {
	ACTOR,
	PAWN,
	OBJECT
};

class cEntity;
typedef void (*collCallbackFunc) (cEntity* entity1, cEntity* entity2,
		int entStructId1, int entStructId2, const cVector2& collVector);
const int DEFAULT_ENTITYMASK = 1;

class cEntity {
	public:
		cEntity (const eEntityType& type, const cPosComp& pos,
				const cEntityNode& entityNode,
				void* usrPtr = nullptr);
		~cEntity (void);

		// Entity Position
		void translate (double dx, double dy);
		void translate (const cVector2& dv);
		void setPos (double x, double y);
		void setPos (const cVector2& v);
		const cVector2& getPos (void) const; 

		// Entity Rotation
		void rotate (double rotnRad);
		void setRotn (double rotnRad);
		double getRotn (void) const;

		// Entity Transforms
		void translateRotate (double dx, double dy, double rotnRad);
		void translateRotate (const cVector2& dv, double rotnRad);
		void translateRotate (const cPosComp& posComp);
		void setPosRotn (double x, double y, double rotnRad);
		void setPosRotn (const cVector2& v, double rotnRad);
		void setPosRotn (const cPosComp& posComp);

		// Add something to deal with entity node 

		// Entity Type
		eEntityType getType (void) const;

		// Entity Collision Mask
		void setEntMask (int entityMask);
		int getEntMask (void) const;

		// Collision Callback Information
		void setCollCallback (collCallbackFunc collCallback);
		void collCallback (cEntity* entity1, cEntity* entity2,
				int entStructId1, int entStructId2, const cVector2& collVector);

		// Additional Entity Information
		void setUsrPtr (void* usrPtr);
		void* getUsrPtr (void) const;

	private:
		eEntityState state_;
		eEntityType type_;
		cPosComp entityPos_;
		cEntityNode entityNode_;
		int entityMask_;
		collCallbackFunc collCallback_;
		void* usrPtr_;
};

#endif
