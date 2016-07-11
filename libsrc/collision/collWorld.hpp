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

typedef std::vector<std::shared_ptr<cEntity>> entListCont;

class cCollWorld {
	public:
		cCollWorld (const std::shared_ptr<cCollBroadphase>& broadphase);
		~cCollWorld (void);
		std::shared_ptr<cEntity> createEntity (const eEntityType& type,
				const cPosComp& pos, const std::vector<cEntityNode>& entityNode,
				void* userPtr = nullptr);
		void removeEntity (int entityId);
		void removeShape (int shapeId);
		std::forward_list<cCollPair>* checkColls (void);

		void setDebugDraw (const std::shared_ptr<cCollDebugDrawer>& debugDrawer); 
		void drawDebugWorld (SDL_Renderer* renderer);
		void addCollMask (int objMask, int collMask);
	private:
		// Move the ownership of the shapes to the collWorld object as well
		// Make a list for kinematic stuff too, or keep it with dyn
		entListCont collEntListStatic_,
					collEntListDyn_;
		std::forward_list<cCollPair> collPairList_;
		std::weak_ptr<cCollBroadphase> broadphase_;
		cCollTest testHandler_;
		std::weak_ptr<cCollDebugDrawer> debugDrawer_;

		int numEntities_;		// This is used as the entity id number
};

#endif
