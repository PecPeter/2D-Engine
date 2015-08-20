#include "collObject.hpp"

cCollObj::cCollObj (const cVector2& pos, const cCollShape* shape,
		eObjType objType, void* usrPtr): pos_(pos),rotnRad_(0.0),shape_(shape),
		objType_(objType), objMask_(DEFAULT_OBJMASK), usrPtr_(usrPtr) {}

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

void cCollObj::rotate (double rotnRad) {
	rotnRad_ += rotnRad;
	int numRotations = rotnRad_/PI_2;
	rotnRad_ -= numRotations*PI_2;
}

void cCollObj::setRotation (double rotnRad) {
	rotnRad_ = rotnRad;
	int numRotations = rotnRad_/PI_2;
	rotnRad_ -= numRotations*PI_2;
}

const double cCollObj::getRotation (void) const {
	return rotnRad_;
}

const cCollShape* cCollObj::getCollShape (void) const {
	return shape_;
}

eObjType cCollObj::getObjType (void) const {
	return objType_;
}

void cCollObj::setObjMask (int objMask) {
	objMask_ = objMask;
}

int cCollObj::getObjMask (void) const {
	return objMask_;
}

void cCollObj::setUsrPtr (void* usrPtr) {
	usrPtr_ = usrPtr;
}

void* cCollObj::getUsrPtr (void) const {
	return usrPtr_;
}
