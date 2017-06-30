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

void cEngine::mainLoop (void) {
	int loops = 0;
	double interpolation;
	double numUpdates = 0,
		   numFrames = 0;
	cTickCounter rateCounter;

	if (TICK_RATE == 0.0)
		TICK_RATE = 60.0;
	MS_PER_UPDATE = 1000.0/TICK_RATE;
	double dtUpdate = 0.0,
		   tOffUpdate = 0.0;

	if (MAX_UPDATE_COUNT == 0)
		MAX_UPDATE_COUNT = 10;

	if (FRAME_RATE == 0.0)
		FRAME_RATE = 120.0;
	MS_PER_RENDER = 1000.0/FRAME_RATE;
	double dtRender = 0.0,
		   tOffRender = 0.0;

	double t_lastUpdateCall,
		   t_lastRenderCall;
	t_lastUpdateCall = t_lastRenderCall = SDL_GetTicks();

	while ((*statePntr_) != nullptr) {
		rateCounter.startLoop();
		// Update loop
		double curTime = SDL_GetTicks();
		dtUpdate = curTime - t_lastUpdateCall;

		while ((dtUpdate >= MS_PER_UPDATE) &&
				loops < MAX_UPDATE_COUNT && ((*statePntr_) != nullptr)) {
			dtUpdate -= MS_PER_UPDATE;
			++loops;
			++numUpdates;

			handleEvents();
			updateState(TICK_RATE);
		}
		loops = 0;
//		tOffUpdate = dtUpdate;
		t_lastUpdateCall = curTime - dtUpdate;
		
//		while ((dtUpdate >= MS_PER_UPDATE - tOffUpdate) && 
//				loops < MAX_UPDATE_COUNT) {
//			dtUpdate -= MS_PER_UPDATE;
//			++loops;
//			++numUpdates;
//			
//			handleEvents();
//			updateState(TICK_RATE);
//		}
//		t_lastUpdateCall = SDL_GetTicks();
//		tOffUpdate = dtUpdate;

		// Render Loop
		curTime = SDL_GetTicks();
		dtRender = curTime - t_lastRenderCall;
		if ((dtRender >= MS_PER_RENDER - tOffRender) &&
				((*statePntr_) != nullptr)) {
			tOffRender = dtRender - MS_PER_RENDER;
			t_lastRenderCall = curTime;
			dtRender = 0.0;
			interpolation = double(curTime-t_lastUpdateCall)/MS_PER_UPDATE;
			renderState(interpolation);
			++numFrames;
		}

		while (SDL_GetTicks() < t_lastRenderCall+MS_PER_RENDER) {
			SDL_Delay((t_lastRenderCall+MS_PER_RENDER)-SDL_GetTicks());
		}

		if (rateCounter.getTicks() >= 200) {
			double dt = rateCounter.getTicksAndClear();
			CALCED_TICK_RATE = double(numUpdates)/(dt/1000.0);
			CALCED_FRAME_RATE = double(numFrames)/(dt/1000.0);
			numUpdates = numFrames = 0;
		}
		rateCounter.endLoop();
	}
}
/*
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
*/
void cEngine::handleEvents (void) {
	(*statePntr_)->handleEvents(&event_);
}

void cEngine::updateState (double tickRate) {
	int stateIndex = (*statePntr_)->update(tickRate,interStateInfo_);
	stateChange_(stateIndex,statePntr_);
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
