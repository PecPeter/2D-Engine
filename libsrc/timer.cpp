#include "timer.hpp"

cTickCounter::cTickCounter (double timeScale): loopCount_(0),
	cumTicks_(0),tempTickCount_(0),timeScale_(timeScale) {}

void cTickCounter::startLoop (void) {
	tempTickCount_ = SDL_GetTicks();
}

void cTickCounter::endLoop (void) {
	loopCount_++;
	cumTicks_ += SDL_GetTicks()-tempTickCount_;
}

double cTickCounter::getTicks (void) {
	return cumTicks_;
}

double cTickCounter::getTicksAndClear (void) {
	double tickCount = cumTicks_;
	loopCount_ = cumTicks_ = 0;
	return tickCount;
}

double cTickCounter::getRate (void) {
	double rate = loopCount_/cumTicks_;
	loopCount_ = cumTicks_ = 0;
//	rate /= timeScale_;
	return rate;
}
