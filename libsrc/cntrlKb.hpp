#ifndef CNTRLKB_HPP
#define CNTRLKB_HPP

#include <forward_list>
#include <map>
#include <vector>
#include <SDL2/SDL.h>

template <class T>
class cCntrlKb {
	public:
		~cCntrlKb (void);

		void addCommand (T action, SDL_Keycode keyCode, bool repeatCommand=true, SDL_Keymod modCode=KMOD_NONE);
		void addCommand (T action, std::vector<SDL_Keycode>& keyCodes, bool repeatCommand=true, SDL_Keymod modCode=KMOD_NONE);
		void checkCommand (SDL_KeyboardEvent& key, std::vector<T>* returnCommands);
	private:
		void updateWatchKey (SDL_KeyboardEvent& key);

		struct sCommandInfo {
			T linkedAction_;
			std::forward_list<bool*> keyStates_;
			SDL_Keymod modcode_;
		};

		std::vector<sCommandInfo*> commandList_;
		std::map<SDL_Keycode,bool> kbWatchKeys_;
		std::map<T,bool> nonRepeatCommands_;
};

template <class T>
cCntrlKb<T>::~cCntrlKb (void) {
	for (auto& commandItr : commandList_) {
		commandItr->keyStates_.clear();
		delete commandItr;
	}
	commandList_.clear();
	kbWatchKeys_.clear();
}

template <class T>
void cCntrlKb<T>::addCommand (T action, SDL_Keycode keyCode, bool repeatCommand, SDL_Keymod modCode) {
	std::vector<SDL_Keycode> commandVec(1,keyCode);
	addCommand(action,commandVec,repeatCommand,modCode);
}
	
template <class T>
void cCntrlKb<T>::addCommand (T action, std::vector<SDL_Keycode>& keyCodes, bool repeatCommand, SDL_Keymod modCode) {
	sCommandInfo* commandInfo = new sCommandInfo;
	commandInfo->linkedAction_ = action;
	for (auto& itr : keyCodes) {
		auto watchKeyItr = kbWatchKeys_.insert(std::pair<SDL_Keycode,bool>(itr,false));
		commandInfo->keyStates_.push_front(&(watchKeyItr.first->second));
	}
	commandInfo->modcode_ = modCode;
	commandList_.push_back(commandInfo);
	
	if (repeatCommand == false)
		nonRepeatCommands_[action] = false;
}

// Preventing repeated actions doesnt work as intended yet. It's either too
// slow or doesnt trigger at all...still working on this feature
template <class T>
void cCntrlKb<T>::checkCommand (SDL_KeyboardEvent& key, std::vector<T>* returnCommands) {
	updateWatchKey(key);
	returnCommands->clear();
	for (const auto& commandItr : commandList_) {
		if ((commandItr->modcode_^key.keysym.mod) == 0) {
			bool isValidCommand = true;
			for (const auto& keyStateItr : commandItr->keyStates_) {
				isValidCommand = isValidCommand && (*keyStateItr);
				if (isValidCommand == false) {
					auto itr = nonRepeatCommands_.find(commandItr->linkedAction_);
					if (itr != nonRepeatCommands_.end())
						itr->second = false;
					break;
				}
			}
			if (isValidCommand == true) {
				auto itr = nonRepeatCommands_.find(commandItr->linkedAction_);
				if (itr != nonRepeatCommands_.end()) {
					if (itr->second == false) {
						returnCommands->push_back(commandItr->linkedAction_);
						itr->second = true;
					}
				}
				else
					returnCommands->push_back(commandItr->linkedAction_);
			}
		}
	}
}

template <class T>
void cCntrlKb<T>::updateWatchKey (SDL_KeyboardEvent& key) {
	auto itr = kbWatchKeys_.find(key.keysym.sym);
	if (itr != kbWatchKeys_.end()) {
		if (key.type == SDL_KEYDOWN)
			itr->second = true;
		else if (key.type == SDL_KEYUP)
			itr->second = false;
	}
}

#endif
