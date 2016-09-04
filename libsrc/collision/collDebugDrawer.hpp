#ifndef COLLDEBUGDRAWER_HPP
#define COLLDEBUGDRAWER_HPP

#include <cmath>
#include <map>
#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "../entity/entity.hpp"
#include "../entity/entityNode.hpp"
#include "../entity/components/positionComponent.hpp"
#include "collShape.hpp"
#include "../math/mathVector.hpp"
#include "../math/mathLinAlgebra.hpp"
#include "../renderFunctions.hpp"

class cCollDebugDrawer {
	public:
		cCollDebugDrawer (int alpha = 255);

		void drawEnt (const SDL_Renderer* rend, const cEntity& ent);
		void drawEnt (const SDL_Renderer* rend, const cEntity& ent,
				const cVector4& col);

	private:
		void drawShape (const SDL_Renderer* rend, const cCollShape& shape,
				const cVector2& shapePos, const double& shapeRotn,
				const cVector4& col);
//		typedef std::pair<eObjectType,eObjectState> colIndex;
//		std::map<colIndex,cVector3> colMap;
		std::map<eEntityType,cVector4> colMap_;
};

#endif
