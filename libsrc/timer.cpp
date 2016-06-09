#include "timer.hpp"

cTickCounter::cTickCounter (void) : cTickCounter(0) {}

cTickCounter::cTickCounter (double timeScale): loopCount_(0),
	cumTicks_(0),tempTickCount_(0),timeScale_(timeScale),
	bLoopStarted_(false) {}

void cTickCounter::startLoop (void) {
	tempTickCount_ = SDL_GetTicks();
	bLoopStarted_ = true;
}

void cTickCounter::endLoop (void) {
	if (bLoopStarted_ == true) {
		bLoopStarted_ = false;
		++loopCount_;
		cumTicks_ += SDL_GetTicks()-tempTickCount_;
	}
}

double cTickCounter::getTicks (void) {
	return cumTicks_;
}

double cTickCounter::getTicksAndClear (void) {
	double tickCount = cumTicks_;
	resetValues();
	return tickCount;
}

double cTickCounter::getRateAndClear (void) {
	double rate = loopCount_/cumTicks_;
	resetValues();
	if (timeScale_ > 0) {
		rate /= timeScale_;
	}
	return rate;
}

void cTickCounter::resetValues (void) {
	loopCount_ = cumTicks_ = 0;
	bLoopStarted_ = false;
}
