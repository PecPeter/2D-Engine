#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include <exception>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <tinyxml2.h>

// General struct for frame info
// Param:
// 	topLeftX  - Where to begin the blit on the surface (x-axis)
// 	topLeftY  - Where to begin the blit on the surface (y-axis)
// 	width	  - Width of the frame
// 	height	  - Height of the frame
// 	dx_centre - dx from the topLeftX which needs to line up with the x
// 				position of the entity
// 	dy_centre - dy from the topLeftY which needs to line up with the y
// 				position of the entity
struct sFrameInfo {
	int topLeftX,
		topLeftY,
		width,
		height,
		dx_centre,
		dy_centre;
};

class cAnimComp {
	public:
		cAnimComp (std::string spriteSheetPath,
				std::string spriteSheetInfoPath);
		~cAnimComp (void);
	private:
		SDL_Surface* spriteSheet_;
		int animStartTime_,
			fps_;	// Use these to calculate the current frame to render

		// This holds the info for rendering the different frames.
		// Param:
		// 	int 					- The id for the animation to render
		// 	std::vector<sFrameInfo> - contains offsets for each frame
		std::map<int,std::vector<sFrameInfo>> animMap_;
};

#endif
