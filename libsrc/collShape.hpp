#ifndef COLLSHAPE_HPP
#define COLLSHAPE_HPP

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
		cCollAabb (double hw, double hh); //This needs to throw in case negative values are given
		~cCollAabb (void);

		double getHW (void) const;
		double getHH (void) const;
	private:
		double hw_,
			   hh_;
};

bool operator== (const cCollShape& lhs, const cCollShape& rhs);

#endif
