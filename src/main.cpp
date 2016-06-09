#include <iostream>

#include "gameState.hpp"
#include "stateHandler.hpp"
#include "engine.hpp"
#include "engineMetrics.hpp"
#include "gameStateTypes.hpp"
#include "commandTestState.hpp"

#include "mathMatrixUnitTest.hpp"
#include "mathVectorUnitTest.hpp"
#include "collObjectUnitTest.hpp"
#include "collPairUnitTest.hpp"
#include "collTestHandlerUnitTest.hpp"
#include "collWorldUnitTest.hpp"
#include "collDebugDrawerUnitTest.hpp"
#include "commandHandlerUnitTest.hpp"

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
	setSettings(60,200,10);

	char title[] = "Space Game";
	handler* sH = new handler;

	if (engine.init (640,480,title,sH) == false) {
		std::cerr << "Could not initialize engine properly. Now exiting." << std::endl;
		return 1;
	}
//	engine.mainLoop();
	engine.quit();

/*	std::cout << "Matrix unit test:\n";
	mathMatrixTest();
	std::cout << "Vector unit test:\n";
	mathVectorUnitTest();
	std::cout << "Collision object unit test:\n";
	collObjectUnitTest();
	std::cout << "Collision pair unit test:\n";
	collPairUnitTest();
	std::cout << "Collision test handler unit test:\n";
	collTestHandlerUnitTest();
	std::cout << "Collision world unit test:\n";
	collWorldUnitTest();
*/	std::cout << "Collision world debug drawer unit test:\n";
	collDebugDrawerUnitTest();
//	std::cout << "Command handler unit test:\n";
//	commandHandlerUnitTest();
	return 0;
}
