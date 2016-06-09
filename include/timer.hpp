#ifndef TIMER_HPP
#define TIMER_HPP

#include "SDL2/SDL.h"

class cTickCounter {
	public:
		cTickCounter (void);
		cTickCounter (double timeScale); // timeScale: number of milliseconds in wanted unit
										 // ie: 1000ms in 1s
		void startLoop (void);
		void endLoop (void);
		double getTicks (void);
		double getTicksAndClear (void);
		double getRateAndClear (void);
	private:
		double loopCount_,
			   cumTicks_,
			   tempTickCount_,
			   timeScale_;
		bool bLoopStarted_;

		void resetValues (void);
};

#endif
