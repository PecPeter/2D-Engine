#include "gameState.hpp"

cGameState::cGameState (void): stateStage_(eStateStage::RENDER_NEW_STATE),exitGameState_(false) {}

cGameState::~cGameState (void) {}

void cGameState::handleEvents (SDL_Event* event) {
	if (stateStage_ == eStateStage::NONE)
		while (SDL_PollEvent(event) == 1)
			handleState(*event);
}

eStateAction cGameState::update (void) {
	eStateAction stateAction(eStateAction::NONE);
	if (stateStage_ == eStateStage::NONE)
		stateAction = updateState();
	else if (stateStage_ == eStateStage::EXIT_STATE)
		return eStateAction::REMOVE_STATE;
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
