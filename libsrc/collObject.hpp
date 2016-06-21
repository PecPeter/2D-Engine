#ifndef COLLOBJECT_HPP
#define COLLOBJECT_HPP

#include <memory>

#include "collShape.hpp"
#include "collShapeNode.hpp"
#include "mathMatrix.hpp"
#include "mathVector.hpp"
#include "mathConstants.hpp"
#include "mathLinAlgebra.hpp"

class cCollObj;
typedef void (*collCallbackFunc) (cCollObj* obj1, cCollObj* obj2,
		cVector2 collVector);
const int DEFAULT_OBJMASK = 1;

enum class eObjType {
	STATIC,
	DYNAMIC
};

enum class eObjState {
	ACTIVE,
	INACTIVE
};

class cCollObj {
	public: 
		// Constructors and Destructors
		cCollObj (const cVector2& pos,
				const std::shared_ptr<const cCollShape>& genShape,
				eObjType objType = eObjType::STATIC,
				const std::shared_ptr<const sCollShapeNode>& accShape = nullptr,
				void* usrPtr = nullptr);
		~cCollObj (void);

		// Object Position
		void translate (double dx, double dy);
		void translate (const cVector2& dv);
		const cVector2& getObjPos (void) const; 

		// Object Rotation
		void rotate (double rotnRad);
		void setRotation (double rotnRad);
		const double getRotation (void) const;

		// Object Collision Shape
		const std::weak_ptr<const cCollShape>& getGenCollShape (void) const;
		const std::weak_ptr<const sCollShapeNode>& getAccCollShape (void) const;

		// Object Type
		eObjType getObjType (void) const;

		// Object Collision Mask
		void setObjMask (int objMask);
		int getObjMask (void) const;

		// Collision Callback Information
		void setCollCallback (collCallbackFunc collCallback);
		void collCallback (cCollObj* obj1, cCollObj* obj2, cVector2 collVector);

		// Additional Object Information
		void setUsrPtr (void* objPtr);
		void* getUsrPtr (void) const;
	private:
		cVector2 pos_;
		double rotnRad_;
		std::weak_ptr<const cCollShape> genCollShape_;
		std::weak_ptr<const sCollShapeNode> accCollShape_;
		eObjType objType_;
		int objMask_;
		collCallbackFunc collCallback_;
		void* usrPtr_;
};

#endif
