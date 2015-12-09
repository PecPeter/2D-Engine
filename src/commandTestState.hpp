#ifndef COMMANDTESTSTATE_HPP
#define COMMANDTESTSTATE_HPP

#include <iostream>
#include <SDL2/SDL.h>

#include "gameState.hpp"
#include "cntrlKb.hpp"
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
		int updateState (double tickRate);
		void renderState (SDL_Renderer* renderer, double timeLag);

		bool initState (SDL_Renderer* renderer);

		enum class eKbAction {
			ESCAPE=0,
			M1_LEFT,
			M2_LEFT,
			M1_RIGHT,
			M2_RIGHT,
			M1_UP,
			M2_UP,
			M1_DOWN,
			M2_DOWN
		};

		std::vector<eKbAction> kbActions_;
		cCntrlKb<eKbAction> kbCommandHandler_;
		SDL_Rect rect,
				 rect1;
};

#endif
