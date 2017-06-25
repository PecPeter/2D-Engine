#ifndef STATEHANDLER_HPP
#define STATEHANDLER_HPP

#include "gameState.hpp"

class cStateHandler {
	public:
		cStateHandler (void): numStates_(0), interStateInfo_(nullptr),
							  statePntr_(nullptr) {}
//		virtual ~cStateHandler (void) {}

		virtual cGameState* getState (void) = 0;
		virtual void changeState (int stateAction) = 0;
		virtual int getNumStates (void);
		virtual void** getInterStateInfo (void);
	protected:
		int numStates_;
		void* interStateInfo_;
		cGameState** statePntr_;
};

#endif
