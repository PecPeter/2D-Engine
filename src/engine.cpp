#include "engine.hpp"

cEngine::cEngine (void): window_(nullptr),renderer_(nullptr) {}

cEngine::~cEngine (void) {}

bool cEngine::init (int screenWidth, int screenHeight, char* winTitle) {
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
	window_ = SDL_CreateWindow (winTitle, SDL_WINDOWPOS_UNDEFINED,
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
	//Add intro state to stateList
	stateList_.push_back(new cIntroState);
	return true;
}

void cEngine::quit (void) {
	if (renderer_ != nullptr)
		SDL_DestroyRenderer(renderer_);
	if (window_ != nullptr)
		SDL_DestroyWindow(window_);
	renderer_ = nullptr;
	window_ = nullptr;

	if (stateList_.empty() == false)
		for (auto it = stateList_.begin(); it != stateList_.end(); ++it)
			delete *it;
	stateList_.clear();

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
		   renderTime = 0.0,
		   actualTime,
		   sleepTime;
	int numUpdates = 0,
		numFrames = 0;
	while (stateList_.size() > 0) { 					//As long as there is a state on the list, don't end the game
		curTime = SDL_GetTicks();
		dTime = curTime-prevTime;
		prevTime = curTime;
		updateTime += dTime;
		renderTime += dTime;

		int updateCount = 0;
		while (updateTime >= MS_PER_UPDATE && updateCount < MAX_UPDATE_COUNT && (stateList_.empty() == false)) {
			handleEvents();
			updateState();
			updateTime -= MS_PER_UPDATE;
			++updateCount;
			++numUpdates;
		}

		int renderCount = 0;
		if ((renderTime >= MS_PER_RENDER || updateCount > 0) && (stateList_.empty() == false)) {
			// Do interpolation calculations here, send to render
			renderState(updateTime);	// change updateTime to the interpolation value once its calced.
			++renderCount;
			renderTime -= (MS_PER_RENDER == 0.0 ? renderTime : MS_PER_RENDER);
			++numFrames;
		}

		if (updateCount == 0 && renderCount == 0) {
//		if (!sleep && updateCount == 0 && renderCount == 0) {
			double actualTime = updateTime+(SDL_GetTicks()-curTime);
			double sleepTime = (MS_PER_UPDATE-actualTime);
			if (sleepTime > 1) {
				SDL_Delay (sleepTime-1);
			}
		}
	}
}

void cEngine::handleEvents (void) {
	auto currentState = stateList_.rbegin();
	(*currentState)->handleEvents(&event_);
}

void cEngine::updateState (void) {
	auto currentState = stateList_.rbegin();
	switch ((*currentState)->update()) {
		case eStateAction::REMOVE_STATE: {
			delete *currentState;
			stateList_.pop_back();
			break;
		}
		case eStateAction::INTRO_STATE: {
			std::cout << "Creating new introState" << std::endl;
			stateList_.push_back(new cIntroState);
			break;
		}
		default:
			break;
	}
}

void cEngine::renderState (double timeLag) {
	SDL_SetRenderDrawColor(renderer_,0,0,0,255);
	SDL_RenderClear(renderer_);
	auto currentState = stateList_.rbegin();
	(*currentState)->render(renderer_,timeLag);
	SDL_RenderPresent(renderer_);
}
