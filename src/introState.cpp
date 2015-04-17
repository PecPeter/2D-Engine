#include "introState.hpp"

cIntroState::cIntroState (void): broadphase_(nullptr), collisionConfiguration_(nullptr), 
		dispatcher_(nullptr), solver_(nullptr), dynamicsWorld_(nullptr), debugDraw_(nullptr) {
	broadphase_ = new btDbvtBroadphase();
	collisionConfiguration_ = new btDefaultCollisionConfiguration();
	dispatcher_ = new btCollisionDispatcher(collisionConfiguration_);
	solver_ = new btSequentialImpulseConstraintSolver();
	dynamicsWorld_ = new btDiscreteDynamicsWorld(dispatcher_,broadphase_,solver_,collisionConfiguration_);
	dynamicsWorld_->setGravity(btVector3(0.f,-9.81f,0.f));

	//Create a box for the world
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),0);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(
			btTransform(btQuaternion(0,0,0,1),btVector3(0,10,0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld_->addRigidBody(groundRigidBody);

	// Create a player-controller capsule
	btCollisionShape* playerShape = new btCapsuleShape(btScalar(2),btScalar(6));
	cKinematicCharMotionState* playerMotionState = new cKinematicCharMotionState(btTransform(btQuaternion(0,0,0,1),
				btVector3(10,20,0)));
	btRigidBody::btRigidBodyConstructionInfo playerRigidBodyCI(0,playerMotionState,playerShape,btVector3(0,0,0));
	playerRigidBody_ = new btRigidBody(playerRigidBodyCI);
	dynamicsWorld_->addRigidBody(playerRigidBody_);

	// Create a random object
	btCollisionShape* fallShape = new btBoxShape(btVector3(10,50,10));
	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(
				btQuaternion(0,0,0,1),btVector3(500,100,0)));
	btScalar mass = 100;
	btVector3 fallInertia(0,0,0);
	fallShape->calculateLocalInertia(mass,fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,
			fallShape,fallInertia);
	fallRigidBody_ = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld_->addRigidBody(fallRigidBody_);

	//Add actions
	kbActionsList_.addAction(SDLK_DOWN,SDLK_ESCAPE,KMOD_NONE,eKbAction::ESCAPE);
	kbActionsList_.addAction(SDLK_DOWN,SDLK_LEFT,KMOD_NONE,eKbAction::M_LEFT);
	kbActionsList_.addAction(SDLK_DOWN,SDLK_RIGHT,KMOD_NONE,eKbAction::M_RIGHT);
}

cIntroState::~cIntroState (void) {
	delete fallRigidBody_;
	delete dynamicsWorld_;
	delete solver_;
	delete dispatcher_;
	delete collisionConfiguration_;
	delete broadphase_;
}

void cIntroState::handleState (SDL_Event& event) {
	kbAction_ = kbActionsList_.getAction(event.key);
}

eStateAction cIntroState::updateState (void) {
	switch (kbAction_) {
		case eKbAction::ESCAPE:
			return eStateAction::REMOVE_STATE;
			break;
		case eKbAction::M_LEFT:
			break;
		case eKbAction::M_RIGHT:
			break;
		default:
			break;
	}
	dynamicsWorld_->stepSimulation(1/60.f,10);
	return eStateAction::NONE;
}

void cIntroState::renderState (SDL_Renderer* renderer, double timeLag) {
	dynamicsWorld_->debugDrawWorld();
}

bool cIntroState::initState (SDL_Renderer* renderer) {
	//Create and attach the debug drawing object
	debugDraw_ = new cDebugDraw2D(renderer);
	debugDraw_->setDebugMode(btIDebugDraw::DebugDrawModes::DBG_DrawWireframe);
	dynamicsWorld_->setDebugDrawer(debugDraw_);
	return true;
}

bool cIntroState::exitState (SDL_Renderer* renderer) {
	return true;
}
