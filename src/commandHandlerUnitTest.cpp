#include "commandHandlerUnitTest.hpp"

void commandHandlerUnitTest (void) {
	cCntrlKb<stateActions> handler;
	handler.addCommand(stateActions::NONETEST,SDLK_ESCAPE);
}
