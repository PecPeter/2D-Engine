#include "bulletKinematicCharacterController.hpp"

cKinematicCharMotionState::cKinematicCharMotionState (const btTransform &initialPos): pos_(initialPos) {}
cKinematicCharMotionState::~cKinematicCharMotionState (void) {}

void cKinematicCharMotionState::getWorldTransform (btTransform& worldTrans) const {
	worldTrans = pos_;
}
void cKinematicCharMotionState::setWorldTransform (const btTransform& worldTrans) {}
void cKinematicCharMotionState::setKinematicPos (const btTransform &currentPos) {
	pos_ = currentPos;
}
