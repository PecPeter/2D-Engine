#ifndef GAMESTATETYPES_HPP
#define GAMESTATETYPES_HPP

// Add a new entry for any game state that is created. Also add a switch case
// for the new state that is created/added
enum eStateAction {
	NONE,
	REMOVE_STATE,	//Add new state entries after this point
	COMMAND_STATE
};

#endif
