#ifndef COLLOBJECT_HPP
#define COLLOBJECT_HPP

#include "collShape.hpp"
#include "mathMatrix.hpp"
#include "mathVector.hpp"
#include "mathConstants.hpp"
#include "mathLinAlgebra.hpp"

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
		cCollObj (const cVector2& pos, const cCollShape* shape,
				eObjType objType=eObjType::STATIC, void* usrPtr = nullptr);
		~cCollObj (void);
		void translate (double dx, double dy);
		void translate (const cVector2& dv);
		const cVector2& getObjPos (void) const; 
		void rotate (double rotnRad);
		void setRotation (double rotnRad);
		const double getRotation (void) const;
		const cCollShape* getCollShape (void) const;
		eObjType getObjType (void) const;
		void setObjMask (int objMask);
		int getObjMask (void) const;
		void setUsrPtr (void* objPtr);
		void* getUsrPtr (void) const;
	private:
		cVector2 pos_;
		double rotnRad_;
		const cCollShape* shape_;
		eObjType objType_;
		int objMask_;
		void* usrPtr_;
};

#endif
