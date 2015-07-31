#include "collObject.hpp"

cCollObj::cCollObj (const cVector2& pos, const cCollShape* shape,
		eObjType objType, void* usrPtr): pos_(pos),shape_(shape),
		objType_(objType), usrPtr_(usrPtr) {}

cCollObj::~cCollObj (void) {}

void cCollObj::translate (double dx, double dy) {
	cVector2 dv(dx,dy);
	pos_ += dv;
}

void cCollObj::translate (const cVector2& dv) {
	pos_ += dv;
}

const cVector2& cCollObj::getObjPos (void) const {
	return pos_;
}

const cCollShape* cCollObj::getCollShape (void) const {
	return shape_;
}

eObjType cCollObj::getObjType (void) const {
	return objType_;
}

void cCollObj::setUsrPtr (void* usrPtr) {
	usrPtr_ = usrPtr;
}

void* cCollObj::getUsrPtr (void) {
	return usrPtr_;
}
