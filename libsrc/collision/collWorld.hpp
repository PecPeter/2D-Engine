#ifndef COLLWORLD_HPP
#define COLLWORLD_HPP

#include <algorithm>
#include <memory>
#include <vector>
#include <forward_list>

#include <SDL2/SDL.h>

#include "collShape.hpp"
#include "collPair.hpp"
#include "collTest.hpp"
#include "collBroadphase.hpp"
#include "collDebugDrawer.hpp"
#include "../entity/entity.hpp"
#include "../math/mathVector.hpp"

typedef std::vector<std::shared_ptr<cEntity>> entityListCont;

class cCollWorld {
	public:
		cCollWorld (eBroadphaseType broadphaseType = eBroadphaseType::GENERAL);
		~cCollWorld (void);

		cEntity* createEntity (int id, const cPosComp& pos,
				const cEntityNode& entityNode,
				const eEntityType& type = eEntityType::STATIC,
				int entityMask = DEFAULT_ENTITYMASK,
				void* userPtr = nullptr);
		cEntity* createEntity (int id, const cPosComp& pos,
				const std::vector<cEntityNode>& entityNode,
				const eEntityType& type = eEntityType::STATIC,
				int entityMask = DEFAULT_ENTITYMASK,
				void* userPtr = nullptr);
		void removeEntity (int entityId);

		std::forward_list<cCollPair> checkColls (void);

		void setDebugDraw (const cCollDebugDrawer& debugDrawer); 
		void setDebugDraw (cCollDebugDrawer* debugDrawer);
		void drawDebugWorld (SDL_Renderer* renderer);
		void addCollMask (int objMask, int collMask);
	private:
		// Storage list containers for the different parts needed
		// to create entities
		entityListCont entityListStatic_,
					   entityListDyn_;

		cCollBroadphase* broadphase_;
		cCollTest testHandler_;
		cCollDebugDrawer* debugDrawer_;
};

#endif
