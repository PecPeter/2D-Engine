/*
 * THIS CONTAINS ALL OF THE STATE HEADERS AND THE STATE ENUM, USED BY CENGINE.
 * 
 */
#ifndef GAMESTATETYPES_HPP
#define GAMESTATETYPES_HPP

// Add a new entry for any game state that is created. Also add a switch case
// for the new state that is created/added
enum class eStateAction {
	NONE,
	REMOVE_STATE,	//Add new state entries after this point
	INTRO_STATE
};

#endif
