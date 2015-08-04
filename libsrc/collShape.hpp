#ifndef COLLSHAPE_HPP
#define COLLSHAPE_HPP

#include <vector>

#include "mathMatrix.hpp"
#include "mathVector.hpp"

enum class eShapeType {
	AABB,
	LINE
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

class cCollLine : public cCollShape {
	public:
		//coll|no coll
		//    |
		//    |
		//    |-> right normal
		//    |
		//    |
		cCollLine (const cVector2& p1, const cVector2& p2);
		cCollLine (const cVector2& dir);
		cVector2 getDir (void) const;

	private:
		cVector2 dir_;
};

bool operator== (const cCollShape& lhs, const cCollShape& rhs);

#endif
