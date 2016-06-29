#include "collisionComponent.hpp"

cCollComp::cCollComp (std::shared_ptr<cCollShape> collShape) :
		collShape_(collShape) {}

const std::weak_ptr<cCollShape>& cCollComp::getCollShape (void) const {
	return collShape_;
}
