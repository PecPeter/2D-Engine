#ifndef COLLWORLD_HPP
#define COLLWORLD_HPP

#include <vector>
#include <deque>

#include "collShape2D.hpp"
#include "collObject.hpp"
#include "collPair.hpp"
#include "collTest2D.hpp"
#include "collBroadphase.hpp"
#include "mathVector.hpp"

class cCollWorld {
	public:
		cCollWorld (const cCollBroadphase* broadphase);
		~cCollWorld (void);
		cCollObject2D* createObject (const cVector2& pos, const cCollShape& shape,
				eObjectType objType=eObjectType::STATIC);
		void checkColls (void);

		/*void drawDebugWorld (void);*/
	private:
		std::vector<cCollShape> shapeList_;
		std::vector<cCollObject2D*> collObjList_;
		std::deque<cCollPair> collPairList_;
		const cCollBroadphase* broadphase_;
		cCollTestHandler* testHandler_; // This is a pointer to make it easier to change the test handler
};

#endif
