#include "collObject.hpp"
/*
cCollObj::cCollObj (const cVector2& pos,
		const std::shared_ptr<const cCollShape>& genShape, eObjType objType,
		const std::shared_ptr<const sCollShapeNode>& accShape, void* usrPtr) :
		pos_(pos), rotnRad_(0.0), genCollShape_(genShape), 
		accCollShape_(accShape), objType_(objType),
		objMask_(DEFAULT_OBJMASK), collCallback_(nullptr), usrPtr_(usrPtr) {}

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

const std::weak_ptr<const cCollShape>& cCollObj::getGenCollShape (void) const {
	return genCollShape_;
}

const std::weak_ptr<const sCollShapeNode>&
		cCollObj::getAccCollShape (void) const {
	return accCollShape_;
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

void cCollObj::setCollCallback (collCallbackFunc collCallback) {
	collCallback_ = collCallback;
}

void cCollObj::collCallback (cCollObj* obj1, cCollObj* obj2, cVector2 collVector) {
	if (collCallback_ != nullptr)
		collCallback_(obj1,obj2,collVector);
}

void cCollObj::setUsrPtr (void* usrPtr) {
	usrPtr_ = usrPtr;
}

void* cCollObj::getUsrPtr (void) const {
	return usrPtr_;
}
*/
