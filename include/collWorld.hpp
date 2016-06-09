#ifndef COLLWORLD_HPP
#define COLLWORLD_HPP

#include <vector>
#include <forward_list>

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
		cCollWorld (cCollBroadphase* broadphase);
		~cCollWorld (void);
		cCollObj* createObject (const cVector2& pos, const cCollShape& shape,
				eObjType objType=eObjType::STATIC);
//		void removeObject (void);
		std::forward_list<cCollPair>* checkColls (void);

		void setDebugDraw (cCollDebugDrawer* debugDrawer); 
		void drawDebugWorld (SDL_Renderer* renderer);
		void addCollMask (int objMask, int collMask);
	private:
		std::vector<cCollObj*> collObjListStatic_,
			collObjListDyn_;
		std::forward_list<cCollPair> collPairList_;
		cCollBroadphase* broadphase_;
		cCollTest* testHandler_;
		cCollDebugDrawer* debugDrawer_;
};

#endif
