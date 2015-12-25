#ifndef STATEHANDLER_HPP
#define STATEHANDLER_HPP

class cGameState;

class cStateHandler {
	public:
		cStateHandler (void): numStates_(0) {}
		virtual ~cStateHandler (void) {}

		virtual cGameState* getState (void) = 0;
		virtual void changeState (int stateAction) = 0;
		virtual int getNumStates (void);
		virtual void** getInterStateInfo (void);
	protected:
		int numStates_;
		void* interStateInfo_;
};

#endif
