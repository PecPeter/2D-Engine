#include "engine.hpp"

cEngine::cEngine (void): window_(nullptr),renderer_(nullptr),
	stateHandler_(nullptr), debugInfoFont_(nullptr) {}

bool cEngine::init (int screenWidth, int screenHeight, const char* winTitle,
		cStateHandler* stateHandler) {
	return init (screenWidth,screenHeight,std::string(winTitle),stateHandler);
}

bool cEngine::init (int screenWidth, int screenHeight, std::string winTitle,
		cStateHandler* stateHandler) {
	SCREEN_WIDTH = screenWidth;
	SCREEN_HEIGHT = screenHeight;
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
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (window_ == nullptr) {
		std::cerr << "window could not be created." <<
			"\nSDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
//	renderer_ = SDL_CreateRenderer (window_,-1,SDL_RENDERER_ACCELERATED |
//			SDL_RENDERER_PRESENTVSYNC);
	renderer_ = SDL_CreateRenderer (window_,-1,SDL_RENDERER_ACCELERATED);
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
	debugInfoFont_ = TTF_OpenFont("./assets/fonts/TerminusTTF.ttf",12);
	if (debugInfoFont_ == nullptr) {
		std::cerr << "debugInfoFont is null, within cEngine::init."
				  << std::endl;
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
	int loops;
	double interpolation;
	double numUpdates = 0,
		   numFrames = 0;
	cTickCounter rateCounter;

	TICK_RATE = 60;
	MS_PER_UPDATE = 1000.0/TICK_RATE;
	MAX_UPDATE_COUNT = 10;
	FRAME_RATE = 200;
	MS_PER_RENDER = 1000.0/FRAME_RATE;
	Uint32 nextTick = SDL_GetTicks();
	Uint32 lastRender = SDL_GetTicks();
	while (stateHandler_->getNumStates() > 0) {
		//As long as there is a state on the list, don't end the game
		rateCounter.startLoop();
		loops = 0;
		while (nextTick < SDL_GetTicks() && loops < MAX_UPDATE_COUNT) {
			handleEvents();
			updateState(TICK_RATE);
			nextTick += MS_PER_UPDATE;
			++loops;
			++numUpdates;
		}

		interpolation = double(SDL_GetTicks()+MS_PER_UPDATE-nextTick)
			/MS_PER_UPDATE;
		renderState(interpolation);
		++numFrames;

		while (SDL_GetTicks() < lastRender+MS_PER_RENDER) {
			SDL_Delay((lastRender+MS_PER_RENDER)-SDL_GetTicks());
		}
		lastRender = SDL_GetTicks();

		if (rateCounter.getTicks() >= 200) {
			double dt = rateCounter.getTicksAndClear();
			CALCED_TICK_RATE = double(numUpdates)/(dt/1000.0);
			CALCED_FRAME_RATE = double(numFrames)/(dt/1000.0);
			numUpdates = numFrames = 0;
		}
		rateCounter.endLoop();
	}
}

void cEngine::handleEvents (void) {
	auto currentState = stateHandler_->getState();
	if (currentState != nullptr)
		currentState->handleEvents(&event_);
}

void cEngine::updateState (double tickRate) {
	auto currentState = stateHandler_->getState();
	if (currentState != nullptr) {
		void** interStateInfo = stateHandler_->getInterStateInfo();
		stateHandler_->changeState(currentState->update(tickRate,interStateInfo));
	}
}

void cEngine::renderState (double timeLag) {
	auto currentState = stateHandler_->getState();
	if (currentState != nullptr) {
		currentState->render(renderer_,timeLag);

		// Add something to toggle this, ie. "Show fps..."
		std::string debugText = "Tick Rate = " + std::to_string(CALCED_TICK_RATE)
			+ "FPS = " + std::to_string(CALCED_FRAME_RATE);
		drawStrC(renderer_,debugInfoFont_,cVector2(200,
					200),debugText.c_str(),cVector4(255,255,255,255));

		SDL_RenderPresent(renderer_);
		SDL_SetRenderDrawColor(renderer_,0,0,0,255);
		SDL_RenderClear(renderer_);
	}
}
