#include "commandTestState.hpp"

cCommandTestState::cCommandTestState (void): cGameState(eStateAction::NONE,eStateAction::REMOVE_STATE) { kbCommandHandler_.addCommand(eKbAction::ESCAPE,SDLK_ESCAPE);
	kbCommandHandler_.addCommand(eKbAction::M1_LEFT,SDLK_a);
	kbCommandHandler_.addCommand(eKbAction::M1_RIGHT,SDLK_d);
	kbCommandHandler_.addCommand(eKbAction::M1_UP,SDLK_w);
	kbCommandHandler_.addCommand(eKbAction::M1_DOWN,SDLK_s);
	kbCommandHandler_.addCommand(eKbAction::M2_LEFT,SDLK_LEFT);
	kbCommandHandler_.addCommand(eKbAction::M2_RIGHT,SDLK_RIGHT);
	kbCommandHandler_.addCommand(eKbAction::M2_UP,SDLK_UP);
	kbCommandHandler_.addCommand(eKbAction::M2_DOWN,SDLK_DOWN);

	rect = {50,50,10,10};
	rect1 = {100,100,10,10};
}

cCommandTestState::~cCommandTestState (void) {

}

void cCommandTestState::handleState (SDL_Event& event) {
	// TODO: Add an event type handler for multiple events
	// ie. check for quit, window change, mouse event, 
	// keyboard event, etc and hand it off to the appropriate
	// handler.
	switch (event.type) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			kbCommandHandler_.checkCommand(event.key,&kbActions_);
			break;
		case SDL_MOUSEMOTION:
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			break;
		default:
			break;
	}
}

int cCommandTestState::updateState (double tickRate) {
	if (kbActions_.size() > 0) {
		for (auto& kbCommand : kbActions_) {
			switch (kbCommand) {
				case eKbAction::ESCAPE:
					return eStateAction::REMOVE_STATE;
					break;
				case eKbAction::M1_LEFT:
					rect.x -= 1;
					break;
				case eKbAction::M1_RIGHT:
					rect.x += 1;
					break;
				case eKbAction::M1_UP:
					rect.y -= 1;
					break;
				case eKbAction::M1_DOWN:
					rect.y += 1;
					break;
				case eKbAction::M2_LEFT:
					rect1.x -= 1;
					break;
				case eKbAction::M2_RIGHT:
					rect1.x += 1;
					break;
				case eKbAction::M2_UP:
					rect1.y -= 1;
					break;
				case eKbAction::M2_DOWN:
					rect1.y += 1;
					break;
				default:
					break;
			}
		}
	}
	return eStateAction::NONE;
}

void cCommandTestState::renderState (SDL_Renderer* renderer, double timelag) {
	SDL_SetRenderDrawColor(renderer,255,0,0,255);
	SDL_RenderDrawRect(renderer,&rect);
	SDL_RenderDrawRect(renderer,&rect1);
	SDL_SetRenderDrawColor(renderer,255,255,255,255);
}

bool cCommandTestState::initState (SDL_Renderer* renderer) {
//	cCollWorld collWorld(cVector2(0,0),cVector2(640,480));
//	cCollAabb aabb(10,5);
//	cCollCircle circle(20);
//	cCollObject2D* boxObj = collWorld.createObject(cVector2(20,20),aabb),
//		*boxObj1 = collWorld.createObject(cVector2(100,40),aabb,eObjectType::DYNAMIC);

//	const cCollShape* shape = boxObj->getCollShape();

	return true;
}
