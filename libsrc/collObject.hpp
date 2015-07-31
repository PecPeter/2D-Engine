#ifndef COLLOBJECT_HPP
#define COLLOBJECT_HPP

#include "collShape.hpp"
#include "mathVector.hpp"

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
		const cCollShape* getCollShape (void) const;
		eObjType getObjType (void) const;
		void setUsrPtr (void* objPtr);
		void* getUsrPtr (void);
	private:
		cVector2 pos_;
		const cCollShape* shape_;
		eObjType objType_;
		// ADD SOMETHING ABOUT ROTATION?
		void* usrPtr_;
};

#endif
