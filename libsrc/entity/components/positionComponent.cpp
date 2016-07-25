#include "positionComponent.hpp"

cPosComp::cPosComp (void): cPosComp(0,0,0) {}

cPosComp::cPosComp (double x, double y, double rotn) :
		cPosComp(cVector2(x,y),rotn) {}

cPosComp::cPosComp (const cVector2& pos, const double& rotn) :
		compPos_(pos), compRotn_(rotn) {}

cPosComp::cPosComp (const cPosComp& posComp) {
	compPos_ = posComp.getPos();
	compRotn_ = posComp.getRotn();
}

void cPosComp::addPos (const double& dx, const double& dy) {
	compPos_ += cVector2(dx,dy);
}

void cPosComp::addPos (const cVector2& dv) {
	compPos_ += dv;
}

void cPosComp::setPos (const double& x, const double& y) {
	compPos_ = cVector2(x,y);
}

void cPosComp::setPos (const cVector2& v) {
	compPos_ = v;
}

const cVector2& cPosComp::getPos (void) const {
	return compPos_;
}

void cPosComp::addRotn (const double& dr) {
	compRotn_ += dr;
	int numRotn = compRotn_ / PI_2;
	compRotn_ -= static_cast<double>(numRotn)*PI_2;
}

void cPosComp::setRotn (const double& rotn) {
	int numRotn = rotn / PI_2;
	compRotn_ = rotn - static_cast<double>(numRotn)*PI_2;
}

double cPosComp::getRotn (void) const {
	return compRotn_;
}

cPosComp operator+ (const cPosComp& lhs, const cPosComp& rhs) {
	return cPosComp(lhs.getPos() + rhs.getPos(), lhs.getRotn() + rhs.getRotn());
}

cPosComp operator- (const cPosComp& lhs, const cPosComp& rhs) {
	return cPosComp(lhs.getPos() - rhs.getPos(), lhs.getRotn() - rhs.getRotn());
}
