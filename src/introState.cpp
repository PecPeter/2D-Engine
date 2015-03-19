#include "introState.hpp"

cIntroState::cIntroState (void): bgTexture_(nullptr),xTexture_(nullptr),
		oTexture_(nullptr),endState_(eEndState::NONE) {
	// Setup controls
	kbActions_.addAction(SDL_KEYDOWN,SDLK_q,KMOD_NONE,eKbAction::ESCAPE);
	kbActions_.addAction(SDL_KEYDOWN,SDLK_ESCAPE,KMOD_NONE,eKbAction::ESCAPE);
	kbActions_.addAction(SDL_KEYDOWN,SDLK_a,KMOD_NONE,eKbAction::M_LEFT);
	kbActions_.addAction(SDL_KEYDOWN,SDLK_d,KMOD_NONE,eKbAction::M_RIGHT);
	kbActions_.addAction(SDL_KEYDOWN,SDLK_w,KMOD_NONE,eKbAction::M_UP);
	kbActions_.addAction(SDL_KEYDOWN,SDLK_s,KMOD_NONE,eKbAction::M_DOWN);
	kbActions_.addAction(SDL_KEYDOWN,SDLK_RETURN,KMOD_NONE,eKbAction::ENTER);

	grid_.fill(0);
}

cIntroState::~cIntroState (void) {
	SDL_DestroyTexture(bgTexture_);
	SDL_DestroyTexture(xTexture_);
	SDL_DestroyTexture(oTexture_);
	bgTexture_ = xTexture_ = oTexture_ = nullptr;
}

void cIntroState::handleState (SDL_Event& event) {
	switch (kbActions_.getAction(event.key)) {
		case eKbAction::ESCAPE:
			exitGameState_ = true;
			break;
		case eKbAction::M_LEFT:
			curCol_ -= 1;;
			break;
		case eKbAction::M_RIGHT:
			curCol_ += 1;
			break;
		case eKbAction::M_UP:
			curRow_ -= 1;
			break;
		case eKbAction::M_DOWN:
			curRow_ += 1;
			break;
		case eKbAction::ENTER:
			changeSelCell_ = true;
			break;
		default:
			break;
	}
}

eStateAction cIntroState::updateState (void) {
	if (curRow_ < 0)
		curRow_ += 3;
	else if (curRow_ > 2)
		curRow_ -= 3;
	if (curCol_ < 0)
		curCol_ += 3;
	else if (curCol_ > 2)
		curCol_ -= 3;
	if (changeSelCell_ == true) {
		changeSelCell_ = false;
		if (curPlayerToggle_ == true)
			grid_.at(curCol_+(curRow_*3)) = 1;
		else
			grid_.at(curCol_+(curRow_*3)) = -1;
		curPlayerToggle_ = !curPlayerToggle_;
	}
	endState_ = checkEndGame();
	if (endState_ != eEndState::NONE)
		exitGameState_ = true;

	return eStateAction::NONE;
}

void cIntroState::renderState (SDL_Renderer* renderer, double timeLag) {
	SDL_RenderCopy(renderer,bgTexture_,NULL,NULL);

	SDL_Rect tempRect;
	for (int i = 0; i <= 2; ++i) {
		for (int j = 0; j <= 2; ++j) {
			if (grid_.at(j+(i*3)) == 1) {
				tempRect = {189+(101*j),139+(101*i),60,60};
				SDL_RenderCopy(renderer,xTexture_,NULL,&tempRect);
			}
			else if (grid_.at(j+(i*3)) == -1) {
				tempRect = {189+(101*j),139+(101*i),60,60};
				SDL_RenderCopy(renderer,oTexture_,NULL,&tempRect);
			}
		}
	}
	tempRect = {170+(101*curCol_),120+(101*curRow_),97,97};
	if (grid_.at(curCol_+(curRow_*3)) == 0)
		SDL_SetRenderDrawColor(renderer,200,200,200,0);
	else
		SDL_SetRenderDrawColor(renderer,200,0,0,0);
	SDL_RenderFillRect(renderer,&tempRect);
}

bool cIntroState::initState (SDL_Renderer* renderer) {
	//Load Textures
	SDL_Surface* tempSurface = IMG_Load("./assets/gfx/background.png");
	bgTexture_ = SDL_CreateTextureFromSurface(renderer,tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = IMG_Load("./assets/gfx/o.png");
	oTexture_ = SDL_CreateTextureFromSurface(renderer,tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = IMG_Load("./assets/gfx/x.png");
	xTexture_ = SDL_CreateTextureFromSurface(renderer,tempSurface);
	SDL_FreeSurface(tempSurface);
	return true;
}

bool cIntroState::exitState (SDL_Renderer* renderer) {
	switch (endState_) {
		case eEndState::TIE:
			std::cout << "TIE GAME" << std::endl;
			break;
		case eEndState::P1_WINS:
			std::cout << "PLAYER X WINS" << std::endl;
			break;
		case eEndState::P2_WINS:
			std::cout << "PLAYER O WINS" << std::endl;
			break;
		default:
			break;
	}
	return true;
}

eEndState cIntroState::checkEndGame (void) {
	// It's a win when the sum of any row, col, or diagonal is +/-3
	// Check rows
	int sum;
	for (int i = 0; i <= 2; ++i) {
		sum = grid_.at(i*3)+grid_.at(1+i*3)+grid_.at(2+i*3);
		if (sum == 3)
			return eEndState::P1_WINS;
		else if (sum == -3)
			return eEndState::P2_WINS;
	}
	//Check cols
	for (int i = 0; i <= 2; ++i) {
		sum = grid_.at(i)+grid_.at(3+i)+grid_.at(6+i);
		if (sum == 3)
			return eEndState::P1_WINS;
		else if (sum == -3)
			return eEndState::P2_WINS;
	}
	// Check diag
	sum = grid_.at(0)+grid_.at(4)+grid_.at(8);
	if (sum == 3)
		return eEndState::P1_WINS;
	else if (sum == -3)
		return eEndState::P2_WINS;

	sum = grid_.at(2)+grid_.at(4)+grid_.at(6);
	if (sum == 3)
		return eEndState::P1_WINS;
	else if (sum == -3)
		return eEndState::P2_WINS;

	// Check for tie
	int count = 0;
	for (auto it = grid_.begin(); it != grid_.end(); ++it)
		if (*it != 0)
			++count;
	if (count == 9)
		return eEndState::TIE;
	
	return eEndState::NONE;
}
