#ifndef COLLWORLD_HPP
#define COLLWORLD_HPP

#include <vector>

#include "collShape2D.hpp"
#include "collObject.hpp"
#include "mathVector.hpp"

class cCollWorld {
	public:
		cCollWorld (double worldMinX, double worldMinY, double worldMaxX, double worldMaxY);
		cCollWorld (const cVector2& worldDimMin, const cVector2& worldDimMax);
		~cCollWorld (void);
		cCollObject2D* createObject (const cVector2& pos, const cCollShape& shape,
				eObjectType objType=eObjectType::STATIC);
		const cCollShape& getShape (int shapeIndex) const;

		/*void drawDebugWorld (void);*/
	private:
		cVector2 worldDimMin_,
				 worldDimMax_;
		std::vector<cCollShape> shapeList_;
		std::vector<cCollObject2D*> collObjList_;
};

#endif
