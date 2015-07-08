#ifndef COLLSHAPE2D_HPP
#define COLLSHAPE2D_HPP

#include <vector>

#include "mathMatrix.hpp"
#include "mathVector.hpp"

enum class eShapeType {
	AABB
};

class cCollShape {
	public:
		cCollShape (eShapeType shapeType);
		virtual ~cCollShape (void);
		const eShapeType& getShapeType (void) const {return shapeType_;}
	protected:
		eShapeType shapeType_;
};

class cCollAabb : public cCollShape {
	public:
		cCollAabb (double hw, double hh);
		~cCollAabb (void);

		double getHalfWidth (void) const;
		double getHalfHeight (void) const;
	private:
		double halfWidth_,
			   halfHeight_;
};

#endif
