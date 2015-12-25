#include "stateHandler.hpp"

int cStateHandler::getNumStates (void) {
	return numStates_;
}

void** cStateHandler::getInterStateInfo (void) {
	return &interStateInfo_;
}
