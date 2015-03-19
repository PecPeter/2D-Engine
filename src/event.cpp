#include "event.hpp"

eKbAction cKbActionList::getAction (SDL_KeyboardEvent& key) {
	//TODO: possibly change the search algorithm so that it doesn't go through
	//every entry
	if (key.type == SDL_KEYDOWN) {
		if (keyDownActions_.size() > 0)
			for (auto it = keyDownActions_.begin(); it != keyDownActions_.end(); ++it)
				if (compareEventVsNode(key,*it) == true)
					return it->kbAction_;
	}
	else if (key.type == SDL_KEYUP) {
		if (keyUpActions_.size() > 0)
			for (auto it = keyUpActions_.begin(); it != keyUpActions_.end(); ++it)
				if (compareEventVsNode(key,*it) == true)
					return it->kbAction_;
	}
	return eKbAction::NO_ACTION;;
}

void cKbActionList::addAction (SDL_KeyboardEvent key, eKbAction kbAction, bool isRepeatable) {
	if (key.type == SDL_KEYDOWN) {
		if (keyDownActions_.size() == 0)
			keyDownActions_.push_back(sKbActionNode(key.keysym.sym,SDL_Keymod(key.keysym.mod),
						kbAction,isRepeatable));
		else {
			bool actionExists = false;
			for (auto it = keyDownActions_.begin(); it != keyDownActions_.end(); ++it)
				if (key.keysym.sym == it->keyCode_ && key.keysym.mod == it->modCode_) actionExists = true;
			// Current key not defined
			if (!actionExists)
				keyDownActions_.push_back(sKbActionNode(key.keysym.sym,SDL_Keymod(key.keysym.mod),
							kbAction,isRepeatable));
		}
	}
	else {
		if (keyUpActions_.size() == 0)
			keyUpActions_.push_back(sKbActionNode(key.keysym.sym,SDL_Keymod(key.keysym.mod),
						kbAction,isRepeatable));
		else {
			bool actionExists = false;
			for (auto it = keyUpActions_.begin(); it != keyUpActions_.end(); ++it)
				if (key.keysym.sym == it->keyCode_ && key.keysym.mod == it->modCode_) actionExists = true;
			// Current key not defined
			if (!actionExists)
				keyUpActions_.push_back(sKbActionNode(key.keysym.sym,SDL_Keymod(key.keysym.mod),
							kbAction,isRepeatable));
		}
	}
}

void cKbActionList::addAction (Uint32 type, SDL_Keycode keyCode, SDL_Keymod modCodes,
		eKbAction kbAction, bool isRepeatable) {
	if (type == SDL_KEYDOWN) {
		if (keyDownActions_.size() == 0)
			keyDownActions_.push_back(sKbActionNode(keyCode,modCodes,kbAction,isRepeatable));
		else {
			bool actionExists = false;
			for (auto it = keyDownActions_.begin(); it != keyDownActions_.end(); ++it)
				if (keyCode == it->keyCode_ && modCodes == it->modCode_) actionExists = true;
			// Current key not defined
			if (!actionExists)
				keyDownActions_.push_back(sKbActionNode(keyCode,modCodes,kbAction,isRepeatable));
		}
	}
	else {
		if (keyUpActions_.size() == 0)
			keyUpActions_.push_back(sKbActionNode(keyCode,modCodes,kbAction,isRepeatable));
		else {
			bool actionExists = false;
			for (auto it = keyUpActions_.begin(); it != keyUpActions_.end(); ++it)
				if (keyCode == it->keyCode_ && modCodes == it->modCode_) actionExists = true;
			// Current key not defined
			if (!actionExists)
				keyUpActions_.push_back(sKbActionNode(keyCode,modCodes,kbAction,isRepeatable));
		}
	}
}

bool cKbActionList::compareEventVsNode (SDL_KeyboardEvent& kbEvent, sKbActionNode& kbNode) {
	if ((kbEvent.keysym.sym == kbNode.keyCode_)&&(kbEvent.keysym.mod == kbNode.modCode_)) {
		if ((kbEvent.repeat == true)&&(kbNode.isRepeatableAction_ == false))
			return false;
		return true;
	}
	return false;
}
