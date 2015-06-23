#ifndef COLLSHAPE2D_HPP
#define COLLSHAPE2D_HPP

#include "mathMatrix.hpp"
#include "mathVector.hpp"

enum class eShapeType {
	CIRCLE,
	AABB
};

class cCollShape {
	public:
		cCollShape (eShapeType shapeType);
		cCollShape (const eShapeType shapeType, const cMatrix& shapeDim);
		virtual ~cCollShape (void);
		const eShapeType& getShapeType (void) const {return shapeType_;}
		const cMatrix& getShapeDim (void) const {return shapeDim_;}

		bool operator== (const cCollShape& rhs) const;
	protected:
		eShapeType shapeType_;
		cMatrix shapeDim_;
};

class cCollCircle : public cCollShape {
	public:
		cCollCircle (double radius);
		cCollCircle (const cCollCircle& ref);
		~cCollCircle (void);
};

class cCollAabb : public cCollShape {
	public:
		cCollAabb (double hw, double hh);
		cCollAabb (const cCollAabb& ref);
		~cCollAabb (void);
};

#endif
