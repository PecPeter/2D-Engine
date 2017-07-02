#include "engine.hpp"

cEngine::cEngine (void): window_(nullptr),renderer_(nullptr),
	statePntr_(nullptr), debugInfoFont_(nullptr) {}

bool cEngine::init (int screenWidth, int screenHeight, const char* winTitle,
		stateChangeCallback callback, cGameState** statePntr) {
	return init (screenWidth,screenHeight,std::string(winTitle),callback,
			statePntr);
}

bool cEngine::init (int screenWidth, int screenHeight, std::string winTitle,
		stateChangeCallback callback, cGameState** statePntr) {
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
	if (statePntr == nullptr) {
		std::cerr << "statePntr is null, within cEngine::init." << std::endl;
		return false;
	}
	statePntr_ = statePntr;
	stateChange_ = callback;
	TICK_RATE = 15.0;
	MAX_UPDATE_COUNT = 5;
	return true;
}

void cEngine::quit (void) {
	if (renderer_ != nullptr)
		SDL_DestroyRenderer(renderer_);
	if (window_ != nullptr)
		SDL_DestroyWindow(window_);
	if (debugInfoFont_ != nullptr)
		TTF_CloseFont(debugInfoFont_);
	renderer_ = nullptr;
	window_ = nullptr;
	debugInfoFont_ = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

// The game loop is based on the DeWitters game loop post
// http://www.koonsolo.com/news/dewitters-gameloop/
void cEngine::mainLoop (void) {
	double numUpdates = 0,
		   numFrames = 0;
	cTickCounter rateCounter;

	int loops;
	double interpolation;
	double nextTick = SDL_GetTicks();

	while ((*statePntr_) != nullptr) {
		rateCounter.startLoop();

		// Update loop
		loops = 0;
		while (SDL_GetTicks() > nextTick && loops < MAX_UPDATE_COUNT &&
			   ((*statePntr_) != nullptr)) {
			++loops;
			++numUpdates;
			handleEvents();
			updateState(TICK_RATE);
			nextTick += MS_PER_UPDATE;
		}

		// Render Loop
		interpolation = double(SDL_GetTicks()+MS_PER_UPDATE-nextTick) /
			MS_PER_UPDATE;
		if ((*statePntr_) != nullptr) {
			renderState(interpolation);
			++numFrames;
		}

		rateCounter.endLoop();
		if (rateCounter.getTicks() >= 200) {
			double dt = rateCounter.getTicksAndClear();
			CALCED_TICK_RATE = double(numUpdates)/(dt/1000.0);
			CALCED_FRAME_RATE = double(numFrames)/(dt/1000.0);
			numUpdates = numFrames = 0;
		}
	}
}

void cEngine::handleEvents (void) {
	(*statePntr_)->handleEvents(&event_);
}

void cEngine::updateState (double tickRate) {
	int stateIndex = (*statePntr_)->update(tickRate,interStateInfo_);
	stateChange_(stateIndex,statePntr_,interStateInfo_);
}

void cEngine::renderState (double timeLag) {
	(*statePntr_)->render(renderer_,timeLag);
	if (RENDER_SETTINGS != 0) {
		if ((RENDER_SETTINGS & RENDER_FPS) > 0) {
			std::string fpsText = "FPS: " + std::to_string(CALCED_FRAME_RATE);
			drawStrDR(renderer_,debugInfoFont_,cVector2(0,0),fpsText.c_str(),
					cVector4(255,255,255,255));
		}
		if ((RENDER_SETTINGS & RENDER_TPS) > 0) {
			std::string tpsText = "TPS: " + std::to_string(CALCED_TICK_RATE);
			drawStrDR(renderer_,debugInfoFont_,cVector2(0,10),tpsText.c_str(),
					cVector4(255,255,255,255));
		}
	}
	SDL_RenderPresent(renderer_);
	SDL_SetRenderDrawColor(renderer_,0,0,0,255);
	SDL_RenderClear(renderer_);
}
