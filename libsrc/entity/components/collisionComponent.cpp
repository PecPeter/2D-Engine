#include "collisionComponent.hpp"

cCollComp::cCollComp (std::shared_ptr<cCollShape> collShape) :
		collShape_(collShape) {}

std::shared_ptr<cCollShape> cCollComp::getCollShape (void) const {
	return collShape_.lock();
}
