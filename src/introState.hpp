#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include <bullet/btBulletDynamicsCommon.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "bulletDebugDrawer.hpp"
#include "bulletKinematicCharacterController.hpp"
#include "gameState.hpp"
#include "gameStateTypes.hpp"
#include "event.hpp"

class cIntroState: public cGameState {
	public:
		cIntroState (void);
		virtual ~cIntroState (void);
	private:
		virtual void handleState (SDL_Event& event);
		virtual eStateAction updateState (void);
		virtual void renderState (SDL_Renderer* renderer, double timeLag);
		virtual bool initState (SDL_Renderer* renderer);
		virtual bool exitState (SDL_Renderer* renderer);

		btBroadphaseInterface* broadphase_;
		btDefaultCollisionConfiguration* collisionConfiguration_;
		btCollisionDispatcher* dispatcher_;
		btSequentialImpulseConstraintSolver* solver_;
		btDiscreteDynamicsWorld* dynamicsWorld_;
		btRigidBody* fallRigidBody_;
		btRigidBody* playerRigidBody_;
		
		cDebugDraw2D* debugDraw_;

		cKbActionList kbActionsList_;
		eKbAction kbAction_;

		bool quitState_;
};

#endif
