#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include <array>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "gameState.hpp"
#include "gameStateTypes.hpp"
#include "event.hpp"

enum class eEndState {
	NONE,
	TIE,
	P1_WINS,
	P2_WINS
};

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
		
		eEndState checkEndGame (void);

		cKbActionList kbActions_;
		SDL_Texture* bgTexture_,
			* xTexture_,
			* oTexture_;
		std::array<int,9> grid_;
		bool changeSelCell_ = false,
			 curPlayerToggle_ = true;
		int curRow_ = 0,
			curCol_ = 0;
		eEndState endState_;
};

#endif
