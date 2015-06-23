#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include <forward_list>
#include <map>
#include <vector>
#include <SDL2/SDL.h>

template <class T>
class cKbCommandHandler {
	public:
		~cKbCommandHandler (void) {
			for (auto& commandItr : commandList_) {
				commandItr->keyStates_.clear();
				delete commandItr;
			}
			kbWatchKeys_.clear();
		}

		void addCommand (T action, SDL_Keycode keyCode, SDL_Keymod modCode=KMOD_NONE) {
			std::vector<SDL_Keycode> commandVec(1,keyCode);
			addCommand(action,commandVec,modCode);
		}

		void addCommand (T action, std::vector<SDL_Keycode>& keyCodes, SDL_Keymod modCode=KMOD_NONE) {
			sCommandInfo* commandInfo = new sCommandInfo;
			commandInfo->linkedAction_ = action;
			for (const auto& itr : keyCodes) {
				auto wKeyItr = kbWatchKeys_.insert(std::pair<SDL_Keycode,bool>(itr,false));
				commandInfo->keyStates_.push_front(&(wKeyItr.first->second));
			}
			commandInfo->modcode_ = modCode;
			commandList_.push_back(commandInfo);
		}

		void checkCommand (SDL_KeyboardEvent& key, std::vector<T>* returnCommands) {
			updateWatchKey(key);

			returnCommands->clear();
			for (const auto& commandItr : commandList_) {
				if ((commandItr->modcode_^key.keysym.mod) == 0) {
					bool isValidCommand = true;
					for (const auto& keyStateItr : commandItr->keyStates_) {
						isValidCommand = isValidCommand && (*keyStateItr);
						if (isValidCommand == false) {
							break;
						}
					}
					if (isValidCommand == true) {
						returnCommands->push_back(commandItr->linkedAction_);
					}
				}
			}
		}
	private:
		void updateWatchKey (SDL_KeyboardEvent& key) {
			auto itr = kbWatchKeys_.find(key.keysym.sym);
			if (itr != kbWatchKeys_.end()) {
				if (key.state == SDL_PRESSED)
					itr->second = true;
				else if (key.state == SDL_RELEASED)
					itr->second = false;
			}
		}

		struct sCommandInfo {
			T linkedAction_;
			std::forward_list<bool*> keyStates_;
			SDL_Keymod modcode_;
		};

		std::vector<sCommandInfo*> commandList_;
		std::map<SDL_Keycode,bool> kbWatchKeys_;
};

#endif
