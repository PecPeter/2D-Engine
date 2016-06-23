#ifndef COMMANDTESTSTATE_HPP
#define COMMANDTESTSTATE_HPP

#include <iostream>
#include <SDL2/SDL.h>

#include "./2D-Engine/gameState.hpp"
#include "./2D-Engine/cntrlKb.hpp"
#include "./2D-Engine/collWorld.hpp"
#include "./2D-Engine/collShape.hpp"
#include "./2D-Engine/collObject.hpp"
#include "./2D-Engine/mathVector.hpp"

#include "gameStateTypes.hpp"

class cCommandTestState: public cGameState {
	public:
		cCommandTestState (void);
		~cCommandTestState (void);
	private:
		void handleState (SDL_Event& event);
		int updateState (double tickRate, void** interStateInfo);
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
