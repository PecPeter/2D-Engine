#include <iostream>

#include "gameState.hpp"
#include "stateHandler.hpp"
#include "engine.hpp"
#include "gameStateTypes.hpp"
#include "commandTestState.hpp"

class handler: public cStateHandler {
	public:
		handler (void): state_(nullptr) {
			state_ = new cCommandTestState;
			++numStates_;
		}
		~handler (void) {
			if (state_ != nullptr)
				delete state_;
			state_ = nullptr;
			numStates_ = 0;
		}
		cGameState* getState (void) {
			return state_;
		}
		void changeState (int stateAction) {
			switch (stateAction) {
				case eStateAction::REMOVE_STATE:
					delete state_;
					state_ = nullptr;
					--numStates_;
					break;
				case eStateAction::COMMAND_STATE:
					break;
				default:
					break;
			}
		}
	private:
		cGameState* state_;
};

int main (void) {
	cEngine engine;
	const int SCREEN_WIDTH = 640,
		  SCREEN_HEIGHT = 480;
	char title[] = "Space Game";
	handler* sH = new handler;

	if (engine.init (SCREEN_WIDTH,SCREEN_HEIGHT,title,sH) == false) {
		std::cerr << "Could not initialize engine properly. Now exiting." << std::endl;
		return 1;
	}
	engine.mainLoop();
	engine.quit();
	return 0;
}
