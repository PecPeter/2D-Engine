#ifndef POSITIONCOMPONENT_HPP
#define POSITIONCOMPONENT_HPP

#include "./mathLib/mathVector.hpp"

class cPosComp {
	public:
		cPosComp (void);
		cPosComp (double x, double y, double rotn);
		cPosComp (const cVector2& pos, const double& rotn);
		cPosComp (const cPosComp& posComp);

		void addPos (const double& dx, const double& dy);
		void addPos (const cVector2& dv);
		void setPos (const double& x, const double& y);
		void setPos (const cVector2& v);

		const cVector2& getPos (void) const;

		void addRotn (const double& dr);
		void setRotn (const double& rotn);

		double getRotn (void) const;

	private:
		cVector2 compPos_;
		double compRotn_;
};

cPosComp operator+ (const cPosComp& lhs, const cPosComp& rhs);
cPosComp operator- (const cPosComp& lhs, const cPosComp& rhs);

#endif
