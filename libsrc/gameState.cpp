#include "gameState.hpp"

cGameState::cGameState (int noStateChange, int removeState): stateStage_(eStateStage::RENDER_NEW_STATE),
		exitGameState_(false),noStateChange_(noStateChange),removeState_(removeState) {}

cGameState::~cGameState (void) {}

void cGameState::handleEvents (SDL_Event* event) {
	if (stateStage_ == eStateStage::NONE)
		while (SDL_PollEvent(event) == 1)
			handleState(*event);
}

int cGameState::update (double tickRate, void* interStateInfo) {
	int stateAction(noStateChange_);
	if (stateStage_ == eStateStage::NONE)
		stateAction = updateState(tickRate,interStateInfo);
	else if (stateStage_ == eStateStage::EXIT_STATE)
		return removeState_;
	return stateAction;
}

void cGameState::render (SDL_Renderer* renderer, double timeLag) {
	if (stateStage_ == eStateStage::RENDER_NEW_STATE) {
		if (initState(renderer) == true)
			stateStage_ = eStateStage::NONE;
		return;
	}
	else if (exitGameState_ == true) {
		if (exitState(renderer) == true) {
			stateStage_ = eStateStage::EXIT_STATE;
			exitGameState_ = false;
		}
	}
	renderState(renderer,timeLag);
}

bool cGameState::initState (SDL_Renderer* renderer) {
	return true;
}

bool cGameState::exitState (SDL_Renderer* renderer) {
	return true;
}
