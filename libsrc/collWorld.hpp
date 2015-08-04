#ifndef COLLWORLD_HPP
#define COLLWORLD_HPP

#include <vector>
#include <deque>

#include <SDL2/SDL.h>

#include "collShape.hpp"
#include "collObject.hpp"
#include "collPair.hpp"
#include "collTest.hpp"
#include "collBroadphase.hpp"
#include "collDebugDrawer.hpp"
#include "mathVector.hpp"

class cCollWorld {
	public:
		cCollWorld (const cCollBroadphase* broadphase);
		~cCollWorld (void);
		cCollObj* createObject (const cVector2& pos, const cCollShape& shape,
				eObjType objType=eObjType::STATIC);
//		void removeObject (void);
		std::deque<cCollPair>* checkColls (void);

		void setDebugDraw (cCollDebugDrawer* debugDrawer); 
		void drawDebugWorld (SDL_Renderer* renderer);
	private:
		std::vector<cCollObj*> collObjList_;
		std::deque<cCollPair> collPairList_;
		const cCollBroadphase* broadphase_;
		cCollTest* testHandler_;
		cCollDebugDrawer* debugDrawer_;
};

#endif
