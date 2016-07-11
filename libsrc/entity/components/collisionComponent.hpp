#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#include <memory>

#include "../../collision/collShape.hpp"
#include "../../math/mathMatrix.hpp"
#include "../../math/mathVector.hpp"
#include "../../math/mathConstants.hpp"
#include "../../math/mathLinAlgebra.hpp"

class cCollComp {
	public:
		cCollComp (std::shared_ptr<cCollShape> collShape);

		std::shared_ptr<cCollShape> getCollShape (void) const;
	private:
		std::weak_ptr<cCollShape> collShape_;
};

#endif
