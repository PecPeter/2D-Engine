#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SDL2/SDL.h>

#include "gameStateTypes.hpp"

// Base class for engine state. Other states may inherit from this base class
class cGameState {
	public:
		cGameState (void);
		virtual ~cGameState (void);

		void handleEvents (SDL_Event *event);
		// When a new gameState needs to be added, this function will return
		// an index for which one needs to be added, from eStateAction. 
		eStateAction update (void);
		void render (SDL_Renderer* renderer, double timeLag);
	protected:
		virtual void handleState (SDL_Event& event) = 0;
		virtual eStateAction updateState (void) = 0;
		virtual void renderState (SDL_Renderer* renderer, double timeLag) = 0;
		// These operations will run the transitions between states. They can
		// run different rendering patterns, and then load up an alternate
		// game state.
			// It will run through this function until it completes the initial
			// rendering stages, at which point it will return true.
		virtual bool initState (SDL_Renderer* renderer);
			// It will run through this function until it completes the exit 
			// rendering stages, at which point it will return true.
		virtual bool exitState (SDL_Renderer* renderer);

		enum class eStateStage {
			NONE,
			RENDER_NEW_STATE,
			RENDER_EXIT_STATE,
			EXIT_STATE
		} stateStage_;

		bool exitGameState_;
};

#endif
