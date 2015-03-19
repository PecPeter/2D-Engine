#ifndef EVENT_HPP
#define EVENT_HPP

#include <vector>
#include <SDL2/SDL.h>

// For mod key and key codes, check the SDL2 API for the structures
// SDL_Keymod and SDL_Keycode respectively

enum class eKbAction {
	NO_ACTION,
	ESCAPE,
	M_LEFT,
	M_RIGHT,
	M_DOWN,
	M_UP,
	ENTER
};

enum class eMAction {
	NO_ACTION
};

enum class eCAction {
	NO_ACTION
};

struct sKbActionNode {
	sKbActionNode (SDL_Keycode keyCode, SDL_Keymod modCode, eKbAction kbAction,
			bool isRepeatableAction):
		keyCode_(keyCode),modCode_(modCode),kbAction_(kbAction),
		isRepeatableAction_(isRepeatableAction) {}

	SDL_Keycode keyCode_;
	SDL_Keymod modCode_;
	eKbAction kbAction_;
	bool isRepeatableAction_;
};

struct sMActionNode {
	sMActionNode (void);
};

struct sCActionNode {
	sCActionNode (void);
};

// When adding actions, you can't create 2 actions where the only difference
// is that one may be repeated and the other can't.
class cKbActionList {
	public:
		cKbActionList (void) {}
		~cKbActionList (void) {
			keyDownActions_.clear();
			keyUpActions_.clear();
		}

		void addAction (SDL_KeyboardEvent key, eKbAction kbAction,
				bool isRepeatableAction=true);
		void addAction (Uint32 type, SDL_Keycode keyCode, SDL_Keymod modCodes,
				eKbAction kbAction, bool isRepeatableAction=true);

		eKbAction getAction (SDL_KeyboardEvent &key);
	private:
		bool compareEventVsNode (SDL_KeyboardEvent& kbEvent, sKbActionNode& kbNode);

		std::vector <sKbActionNode> keyDownActions_,
			keyUpActions_;
};	

#endif
