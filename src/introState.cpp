#include "introState.hpp"

cIntroState::cIntroState (void): broadphase_(nullptr), collisionConfiguration_(nullptr), 
		dispatcher_(nullptr), solver_(nullptr), dynamicsWorld_(nullptr), debugDraw_(nullptr) {
	broadphase_ = new btDbvtBroadphase();
	collisionConfiguration_ = new btDefaultCollisionConfiguration();
	dispatcher_ = new btCollisionDispatcher(collisionConfiguration_);
	solver_ = new btSequentialImpulseConstraintSolver();
	dynamicsWorld_ = new btDiscreteDynamicsWorld(dispatcher_,broadphase_,solver_,collisionConfiguration_);
	dynamicsWorld_->setGravity(btVector3(0.f,-9.81,9.f));

}

cIntroState::~cIntroState (void) {
	delete dynamicsWorld_;
	delete solver_;
	delete dispatcher_;
	delete collisionConfiguration_;
	delete broadphase_;
}

void cIntroState::handleState (SDL_Event& event) {}

eStateAction cIntroState::updateState (void) {
	return eStateAction::NONE;
}

void cIntroState::renderState (SDL_Renderer* renderer, double timeLag) {}

bool cIntroState::initState (SDL_Renderer* renderer) {
	//Create and attach the debug drawing object
	debugDraw_ = new cDebugDraw2D(renderer);
	return true;
}

bool cIntroState::exitState (SDL_Renderer* renderer) {
	return true;
}
