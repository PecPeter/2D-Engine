#ifndef COMMANDTESTSTATE_HPP
#define COMMANDTESTSTATE_HPP

#include <iostream>
#include <SDL2/SDL.h>

#include "gameState.hpp"
#include "commandHandler.hpp"
#include "collWorld.hpp"
#include "collShape.hpp"
#include "collObject.hpp"
#include "mathVector.hpp"

#include "gameStateTypes.hpp"

class cCommandTestState: public cGameState {
	public:
		cCommandTestState (void);
		~cCommandTestState (void);
	private:
		void handleState (SDL_Event& event);
		int updateState (void);
		void renderState (SDL_Renderer* renderer, double timeLag);

		bool initState (SDL_Renderer* renderer);

		enum class eKbAction {
			ESCAPE=0,
			MOVE_LEFT,
			MOVE_RIGHT,
			MOVE_UP,
			MOVE_DOWN
		};

		std::vector<eKbAction> kbActions_;
		cKbCommandHandler<eKbAction> kbCommandHandler_;
		SDL_Rect rect;
};

#endif
