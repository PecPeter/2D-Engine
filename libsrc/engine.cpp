#include "engine.hpp"

cEngine::cEngine (void): window_(nullptr),renderer_(nullptr),MS_PER_UPDATE((1.f/120.f)*1000.f),
	MS_PER_RENDER((1.f/250.f)*1000.f),MAX_UPDATE_COUNT(10),stateHandler_(nullptr) {}

cEngine::~cEngine (void) {}

bool cEngine::init (int screenWidth, int screenHeight, const char* winTitle, cStateHandler* stateHandler) {
	return init (screenWidth,screenHeight,std::string(winTitle),stateHandler);
}

bool cEngine::init (int screenWidth, int screenHeight, std::string winTitle,
		cStateHandler* stateHandler) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "SDL could not be initialized, within cEngine::init()" <<
			"\nSDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	if (IMG_Init (IMG_INIT_PNG) < 0) {
		std::cerr << "SDL_Image could not be initialized." <<
			"\nIMG_Error: " << IMG_GetError() << std::endl;
		return false;
	}
	window_ = SDL_CreateWindow (winTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window_ == nullptr) {
		std::cerr << "window could not be created." <<
			"\nSDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	renderer_ = SDL_CreateRenderer (window_,-1,SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC);
	if (renderer_ == nullptr) {
		std::cerr << "renderer could not be created." << 
			"\nSDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	if (SDL_SetRenderDrawColor (renderer_,0,0,0,255) != 0) {
		std::cerr << "Could not set render draw color, within cEngine::init." <<
			"\nSDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	if (TTF_Init() == -1) {
		std::cerr << "SDL_TTF could not be initialized." << 
			"\nTTF_Error: " << TTF_GetError() << std::endl;
		return false;
	}
	if (stateHandler == nullptr) {
		std::cerr << "stateHandler is null, within cEngine::init." << std::endl;
		return false;
	}
	stateHandler_ = stateHandler;
	return true;
}

void cEngine::quit (void) {
//	if (stateHandler_ != nullptr) {
//		delete stateHandler_;
//	}
	stateHandler_ = nullptr;
//	if (stateList_.empty() == false)
//		for (auto& itr : stateList_)
//			delete &itr;
//	stateList_.clear();
	if (renderer_ != nullptr)
		SDL_DestroyRenderer(renderer_);
	if (window_ != nullptr)
		SDL_DestroyWindow(window_);
	renderer_ = nullptr;
	window_ = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void cEngine::mainLoop (void) {
	// SDL_GetTicks() returns the time since initialization in milliseconds
	double prevTime = SDL_GetTicks(),
		   curTime,
		   dTime,
		   updateTime = 0.0,
		   renderTime = 0.0;
	int numUpdates = 0,
		numFrames = 0;
	while (stateHandler_->getNumStates() > 0) {
		//As long as there is a state on the list, don't end the game
		curTime = SDL_GetTicks();
		dTime = curTime-prevTime;
		prevTime = curTime;
		updateTime += dTime;
		renderTime += dTime;

		int updateCount = 0;
		while (updateTime >= MS_PER_UPDATE && updateCount < MAX_UPDATE_COUNT && (stateHandler_->getNumStates() > 0)) {
			handleEvents();
			updateState();
			updateTime -= MS_PER_UPDATE;
			++updateCount;
			++numUpdates;
		}

		int renderCount = 0;
		if ((renderTime >= MS_PER_RENDER || updateCount > 0) && (stateHandler_->getNumStates() > 0)) {
			// Do interpolation calculations here, send to render
			renderState(updateTime);	// change updateTime to the interpolation value once its calced.
			++renderCount;
			renderTime -= (MS_PER_RENDER == 0.0 ? renderTime : MS_PER_RENDER);
			++numFrames;
		}

		if (updateCount == 0 && renderCount == 0) {
			double actualTime = updateTime+(SDL_GetTicks()-curTime);
			double sleepTime = (MS_PER_UPDATE-actualTime);
			if (sleepTime > 1) {
				SDL_Delay (sleepTime-1);
			}
		}
	}
}

void cEngine::handleEvents (void) {
	auto currentState = stateHandler_->getState();
	if (currentState != nullptr)
		currentState->handleEvents(&event_);
}

void cEngine::updateState (void) {
	auto currentState = stateHandler_->getState();
	if (currentState != nullptr)
		stateHandler_->changeState(currentState->update());
}

void cEngine::renderState (double timeLag) {
	auto currentState = stateHandler_->getState();
	if (currentState != nullptr) {
		currentState->render(renderer_,timeLag);
		SDL_RenderPresent(renderer_);
		SDL_SetRenderDrawColor(renderer_,0,0,0,255);
		SDL_RenderClear(renderer_);
	}
}
