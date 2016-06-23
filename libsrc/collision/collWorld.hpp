#ifndef COLLWORLD_HPP
#define COLLWORLD_HPP

#include <memory>
#include <vector>
#include <forward_list>

#include <SDL2/SDL.h>

#include "collShape.hpp"
#include "collObject.hpp"
#include "collPair.hpp"
#include "collTest.hpp"
#include "collBroadphase.hpp"
#include "collDebugDrawer.hpp"
#include "../math/mathVector.hpp"

class cCollWorld {
	public:
		cCollWorld (const std::shared_ptr<cCollBroadphase>& broadphase);
		~cCollWorld (void);
		std::shared_ptr<cCollObj> createObject (const cVector2& pos,
				const std::shared_ptr<const cCollShape>& genShape,
				eObjType objType = eObjType::STATIC,
				const std::shared_ptr<const sCollShapeNode>& accShape = nullptr,
				void* usrPtr = nullptr);
//		void removeObject (void);
		std::forward_list<cCollPair>* checkColls (void);

		void setDebugDraw (const std::shared_ptr<cCollDebugDrawer>& debugDrawer); 
		void drawDebugWorld (SDL_Renderer* renderer);
		void addCollMask (int objMask, int collMask);
	private:
		std::vector<std::shared_ptr<cCollObj>> collObjListStatic_,
											   collObjListDyn_;
		std::forward_list<cCollPair> collPairList_;
		std::weak_ptr<cCollBroadphase> broadphase_;
		cCollTest testHandler_;
		std::weak_ptr<cCollDebugDrawer> debugDrawer_;
};

#endif
