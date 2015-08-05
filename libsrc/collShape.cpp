#include "collShape.hpp"

cCollShape::cCollShape (eShapeType shapeType, int numNorms): shapeType_(shapeType) {
	normList_.resize(numNorms);
}

cCollShape::~cCollShape (void) {
	normList_.clear();
}

const eShapeType& cCollShape::getShapeType (void) const {
	return shapeType_;
}

const std::vector<cVector2>& cCollShape::getNormList (void) const {
	return normList_;
}

cCollLine::cCollLine (const cVector2& p1, const cVector2& p2):
		cCollShape(eShapeType::LINE,1) {
	cVector2 dv = p2-p1;
	dir_ = vUnitVector(dv);
}

cCollLine::cCollLine (const cVector2& dir): cCollShape(eShapeType::LINE,1),
	dir_(dir) {}

cVector2 cCollLine::getDir (void) const {
	return dir_;
};

cCollTri::cCollTri (const cVector2& pt1, const cVector2& pt2, const cVector2& pt3):
		cCollShape(eShapeType::TRI,3) {
	// "Normalize the points, making it so that the centroid is at 0,0
	std::vector<cVector2> pts = {pt1,pt2,pt3,pt1};
	cVector2 centroid = polygonCentroid(pts);
	ptList_.resize(3);
	ptList_.at(0) = pt1-centroid;
	ptList_.at(1) = pt2-centroid;
	ptList_.at(2) = pt3-centroid;

	// Calculate Normals
	normList_.at(0) = vNormal(pt2-pt1);
	normList_.at(1) = vNormal(pt3-pt2);
	normList_.at(2) = vNormal(pt1-pt3);
}

cCollTri::cCollTri (double x1, double y1, double x2, double y2, double x3, double y3):
		cCollTri(cVector2(x1,y1),cVector2(x2,y2),cVector2(x3,y3)) {}

cCollTri::~cCollTri (void) {
	ptList_.clear();
}

const std::vector<cVector2>& cCollTri::getPtList (void) const {
	return ptList_;
}

cCollAabb::cCollAabb (double hw, double hh): cCollShape(eShapeType::AABB,2),
		hw_(hw), hh_(hh) {
	normList_.at(0) = cVector2(1,0);
	normList_.at(1) = cVector2(0,1);
}

cCollAabb::~cCollAabb (void) {}

double cCollAabb::getHW (void) const {
	return hw_;
}

double cCollAabb::getHH (void) const {
	return hh_; 
}

//Incorporate an epsilon value
cCollPoly::cCollPoly (const std::vector<cVector2>& pts): cCollShape(eShapeType::POLY,0) {
	// "Normalize" points around the centroid, which is set to 0,0.
	cVector2 centroid = polygonCentroid(pts);
	ptList_.resize(pts.size()-1);
	for (std::size_t i = 0; i < ptList_.size(); ++i)
		ptList_.at(i) = pts.at(i)-centroid;
	
	// Calculate unique normals
	for (std::size_t i = 0; i < pts.size()-1; ++i) {
		cVector2 normal = vNormal(pts.at(i+1)-pts.at(i));
		bool uniqueNormal = true;
		for (auto& normListItr : normList_)
			if (vAbsolute(normal) == vAbsolute(normListItr))
				uniqueNormal = false;
		if (uniqueNormal == true)
			normList_.push_back(normal);
	}
}

cCollPoly::~cCollPoly (void) {
	ptList_.clear();
}

const std::vector<cVector2>& cCollPoly::getPtList (void) const {
	return ptList_;
}

//Incorporate an epsilon value
bool operator== (const cCollShape& lhs, const cCollShape& rhs) {
	const eShapeType shape1 = lhs.getShapeType(),
		  shape2 = rhs.getShapeType();
	if (shape1 != shape2)
		return false;
	if (shape1 == eShapeType::POINT) {
		return true;
	}
	else if (shape1 == eShapeType::LINE) {
		const cCollLine& line1 = static_cast<const cCollLine&>(lhs);
		const cCollLine& line2 = static_cast<const cCollLine&>(rhs);
		if (line1.getDir() == line2.getDir())
			return true;
	}
	else if (shape1 == eShapeType::TRI) {
		const cCollTri& tri1 = static_cast<const cCollTri&>(lhs);
		const cCollTri& tri2 = static_cast<const cCollTri&>(rhs);
		if (tri1.getPtList() == tri2.getPtList())
			return true;
	}
	else if (shape1 == eShapeType::AABB) {
		const cCollAabb& aabb1 = static_cast<const cCollAabb&>(lhs);
		const cCollAabb& aabb2 = static_cast<const cCollAabb&>(rhs);
		if (aabb1.getHW() == aabb2.getHW() &&
				aabb1.getHH() == aabb2.getHH())
			return true;
	}
	else if (shape1 == eShapeType::OOBB) {
		return true;
	}
	else if (shape1 == eShapeType::POLY) {
		return true;
	}
	else if (shape1 == eShapeType::CIRCLE) {
		return true;
	}
	return false;
}

cVector2 polygonCentroid (const std::vector<cVector2>& pts) {
	// This makes use of the formula presented on wikipedia
	// https://en.wikipedia.org/wiki/Centroid#Centroid_of_polygon
	//
	// Cx = (1/6A)*Σ(N-1,i=0)[x(i)+x(i+1))(x(i)*y(i+1)-(x(i+1)*y(i)))]
	// Cy = (1/6A)*Σ(N-1,i=0)[y(i)+y(i+1))(x(i)*y(i+1)-(x(i+1)*y(i)))]
	// A  = (1/2)*Σ(N-1,i=0)[x(i)*y(i+1)-x(i+1)*y(i)]
	double commonTerm = 0,
		   cX = 0,
		   cY = 0,
		   area = 0;
	for (std::size_t i = 0; i < (pts.size()-1); ++i) {
		commonTerm = pts.at(i).getX()*pts.at(i+1).getY()-pts.at(i+1).getX()*pts.at(i).getY();
		area += commonTerm;
		cX += (pts.at(i).getX()+pts.at(i+1).getX())*commonTerm;
		cY += (pts.at(i).getY()+pts.at(i+1).getY())*commonTerm;
	}
	area *= 0.5;
	double multiplier = 1.0/(6.0*area);
	return cVector2(multiplier*cX,multiplier*cY);
}
