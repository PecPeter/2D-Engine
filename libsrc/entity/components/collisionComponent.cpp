#include "collisionComponent.hpp"

cCollComp::cCollComp (const cCollShape& collShape) :
		collShape_(collShape) {}

const cCollShape& cCollComp::getCollShape (void) const {
	return collShape_;
}
