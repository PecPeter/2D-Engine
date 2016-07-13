#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#include "../../collision/collShape.hpp"

// This component may be unnecessary. If it is, move the collShape to the node
// itself

class cCollComp {
	public:
		cCollComp (const cCollShape& collShape);

		const cCollShape& getCollShape (void) const;
	private:
		cCollShape collShape_;
};

#endif
