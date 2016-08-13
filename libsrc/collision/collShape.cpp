#include "collShape.hpp"

cCollShape::cCollShape (eShapeType shapeType, int numNorms): shapeType_(shapeType) {
	normList_.resize(numNorms);
}

cCollShape::~cCollShape (void) {
//	normList_.clear();
//	data_.clear();
}

const eShapeType& cCollShape::getShapeType (void) const {
	return shapeType_;
}

const std::vector<cVector2>& cCollShape::getNormList (void) const {
	return normList_;
}

const std::vector<cVector2> cCollShape::getData (void) const {
	return data_;
}

cCollPoint::cCollPoint (void) : cCollShape(eShapeType::POINT,0) {}

cCollLine::cCollLine (double px1, double py1, double px2, double py2) :
	cCollLine(cVector2(px2-px1,py2-py1)) {}

cCollLine::cCollLine (const cVector2& p1, const cVector2& p2):
	cCollLine(cVector2(p2-p1)) {}

cCollLine::cCollLine (const cVector2& dir): cCollShape(eShapeType::LINE,1) {
	normList_.push_back(vNormalR(dir));
	data_.push_back(vUnitVector(dir));
}

cCollTri::cCollTri (const cVector2& pt1, const cVector2& pt2, const cVector2& pt3):
		cCollShape(eShapeType::POLY,3) {
	// "Normalize the points, making it so that the centroid is at 0,0
	std::vector<cVector2> pts = {pt1,pt2,pt3,pt1};
	cVector2 centroid = polygonCentroid(pts);
	data_ = {pt1-centroid,pt2-centroid,pt3-centroid};

	// Calculate Normals
	normList_ = {vNormalR(pt2-pt1),vNormalR(pt3-pt2),vNormalR(pt1-pt3)};
}

cCollTri::cCollTri (double x1, double y1, double x2, double y2, double x3, double y3):
		cCollTri(cVector2(x1,y1),cVector2(x2,y2),cVector2(x3,y3)) {}

cCollAabb::cCollAabb (double hw, double hh): cCollShape(eShapeType::POLY,2) {
	normList_ = {cVector2(1,0),cVector2(0,1)};
	data_ = {cVector2(hw,hh),cVector2(-hw,hh),cVector2(-hw,-hh),cVector2(hw,-hh)};
}

//Incorporate an epsilon value
cCollPoly::cCollPoly (const std::vector<cVector2>& pts): cCollShape(eShapeType::POLY,0) {
	// "Normalize" points around the centroid, which is set to 0,0.
	cVector2 centroid = polygonCentroid(pts);
	data_.resize(pts.size()-1);
	for (std::size_t i = 0; i < data_.size(); ++i)
		data_.at(i) = pts.at(i)-centroid;
	
	// Calculate unique normals
	for (std::size_t i = 0; i < pts.size()-1; ++i) {
		cVector2 normal = vNormalR(pts.at(i+1)-pts.at(i));
		bool uniqueNormal = true;
		for (auto& normListItr : normList_)
			if ((normal == normListItr) || ((-1*normal) == normListItr))
				uniqueNormal = false;
		if (uniqueNormal == true)
			normList_.push_back(normal);
	}
}

cCollCircle::cCollCircle (double radius): cCollShape(eShapeType::CIRCLE,0) {
	data_.push_back(cVector2(radius,0));
}

//Incorporate an epsilon value
bool operator== (const cCollShape& lhs, const cCollShape& rhs) {
	if (lhs.getShapeType() == rhs.getShapeType() && lhs.getData() == rhs.getData())
		return true;
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
		double curPtX = pts.at(i).getX(),
			   curPtY = pts.at(i).getY(),
			   nextPtX = pts.at(i+1).getX(),
			   nextPtY = pts.at(i+1).getY();
		commonTerm = curPtX*nextPtY-nextPtX*curPtY;
		area += commonTerm;
		cX += (curPtX+nextPtX)*commonTerm;
		cY += (curPtY+nextPtY)*commonTerm;
	}
	area *= 0.5;
	double multiplier = 1.0/(6.0*area);
	return cVector2(multiplier*cX,multiplier*cY);
}
