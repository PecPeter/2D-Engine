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

typedef std::vector<cEntity> entityListCont;
typedef std::vector<std::shared_ptr<cEntityNode>> entityNodeListCont;
typedef std::vector<std::shared_ptr<cCollShape>> collShapeListCont;

class cCollWorld {
	public:
		cCollWorld (const std::shared_ptr<cCollBroadphase>& broadphase);
		~cCollWorld (void);

		const cEntity& createEntity (const eEntityType& type, const cPosComp& pos,
				const cEntityNode& entityNode,
				int entityMask = DEFAULT_ENTITYMASK, void* userPtr = nullptr);
		const cEntity& createEntity (const eEntityType& type, const cPosComp& pos,
				const std::vector<cEntityNode>& entityNode,
				int entityMask = DEFAULT_ENTITYMASK, void* userPtr = nullptr);
		void removeEntity (int entityId);

/*		const cEntityNode* createEntityNode (void);
		void removeEntityNode (int entityNodeId);

		const cCollShape* createCollShape (void);
		void removeCollShape (int shapeId);

*/		std::forward_list<cCollPair>* checkColls (void);

		void setDebugDraw (const std::shared_ptr<cCollDebugDrawer>& debugDrawer); 
		void drawDebugWorld (SDL_Renderer* renderer);
		void addCollMask (int objMask, int collMask);
	private:
		// Storage list containers for the different parts needed
		// to create entities
		entityListCont entityListStatic_,
					   entityListDyn_;
//		entityNodeListCont entityNodeList_;
//		collShapeListCont collShapeList_;

		std::forward_list<cCollPair> collPairList_;
		std::weak_ptr<cCollBroadphase> broadphase_;
		cCollTest testHandler_;
		std::weak_ptr<cCollDebugDrawer> debugDrawer_;

		int numEntities_;		// This is used as the entity id number
};

#endif
