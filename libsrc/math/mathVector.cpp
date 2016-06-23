#include "mathVector.hpp"

cVector2::cVector2 (void): cMatrix(2,1) {}

cVector2::cVector2 (double x, double y): cMatrix(2,1) {
	set(0,0) = x;
	set(1,0) = y;
}

cVector2::cVector2 (const cVector2& vector): cMatrix(vector) {}

cVector2::cVector2 (const cMatrix& matrix): cMatrix(2,1) {
	matrix.getSize(&nRows_,&nCols_);
	if (nRows_ != 2 && nCols_ != 1)
		throw(std::range_error("Matrix dimensions are wrong"));
	set(0,0) = matrix.get(0,0);
	set(1,0) = matrix.get(1,0);
}

cVector2::~cVector2 (void) {}

double cVector2::getX (void) const {
	return get(0,0);
}

double cVector2::getY (void) const {
	return get(1,0);
}

void cVector2::setX (double x) {
	set(0,0) = x;
}

void cVector2::setY (double y) {
	set(1,0) = y;
}

cVector3::cVector3 (void): cMatrix(3,1) {}

cVector3::cVector3 (double x, double y, double z): cMatrix(3,1) {
	set(0,0) = x;
	set(1,0) = y;
	set(2,0) = z;
}

cVector3::cVector3 (const cVector3& vector): cMatrix(vector) {}

cVector3::cVector3 (const cMatrix& matrix): cMatrix(3,1) {
	matrix.getSize(&nRows_,&nCols_);
	if (nRows_ != 3 && nCols_ != 1)
		throw(std::range_error("Matrix dimensions are wrong"));
	set(0,0) = matrix.get(0,0);
	set(1,0) = matrix.get(1,0);
	set(2,0) = matrix.get(2,0);
}

cVector3::~cVector3 (void) {}

double cVector3::getX (void) const {
	return get(0,0);
}

double cVector3::getY (void) const {
	return get(1,0);
}

double cVector3::getZ (void) const {
	return get(2,0);
}

void cVector3::setX (double x) {
	set(0,0) = x;
}

void cVector3::setY (double y) {
	set(1,0) = y;
}

void cVector3::setZ (double z) {
	set(2,0) = z;
}

cVector4::cVector4 (void): cMatrix(4,1) {}

cVector4::cVector4 (double w, double x, double y, double z): cMatrix(4,1) {
	set(0,0) = w;
	set(1,0) = x;
	set(2,0) = y;
	set(3,0) = z;
}

cVector4::cVector4 (const cVector4& vector): cMatrix(vector) {}

cVector4::cVector4 (const cMatrix& matrix): cMatrix(4,1) {
	matrix.getSize(&nRows_,&nCols_);
	if (nRows_ != 4 && nCols_ != 1)
		throw(std::range_error("Matrix dimensions are wrong"));
	set(0,0) = matrix.get(0,0);
	set(1,0) = matrix.get(1,0);
	set(2,0) = matrix.get(2,0);
	set(3,0) = matrix.get(3,0);
}

cVector4::~cVector4 (void) {}

double cVector4::getW (void) const {
	return get(0,0);
}

double cVector4::getX (void) const {
	return get(1,0);
}

double cVector4::getY (void) const {
	return get(2,0);
}

double cVector4::getZ (void) const {
	return get(3,0);
}

void cVector4::setW (double w) {
	set(0,0) = w;
}

void cVector4::setX (double x) {
	set(1,0) = x;
}

void cVector4::setY (double y) {
	set(2,0) = y;
}

void cVector4::setZ (double z) {
	set(3,0) = z;
}

double vSqMagnitude (const cVector2& v1) {
	double sqSum = 0;
	int numRows = 0,
		numCols = 0;
	v1.getSize(&numRows,&numCols);
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			sqSum += v1.get(i,j)*v1.get(i,j);
		}
	}
	return sqSum;
};

double vMagnitude (const cVector2& v1) {
	return std::sqrt(vSqMagnitude(v1));
}

double vDotProd (const cVector2& v1, const cVector2& v2) {
	int rows, cols;
	v1.getSize(&rows,&cols);
	if (rows != v2.getRowSize() || cols != v2.getColSize()) {
		//throw exception
	}
	double dotProduct = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			dotProduct += v1.get(i,j)*v2.get(i,j);
		}
	}
	return dotProduct;
}

double vAngleRad (const cVector2& v1, const cVector2& v2) {
	return std::acos(vDotProd(v1,v2)/(vMagnitude(v1)*vMagnitude(v2)));
}

double vAngleDeg (const cVector2& v1, const cVector2& v2) {
	return vAngleRad(v1,v2)*RAD_TO_DEG;
}

double vScalProj (const cVector2& projVec, const cVector2& projAxis) {
	cVector2 unitProjAxis = vUnitVector(projAxis);
	return vDotProd(projVec,unitProjAxis);
}

cVector2 vUnitVector (const cVector2& v1) {
	cVector2 tmpVec(v1);
	tmpVec *= 1.0/vMagnitude(v1);
	return tmpVec;
}

cVector2 vAbsolute (const cVector2& v1) {
	return cVector2(std::abs(v1.get(0,0)),std::abs(v1.get(1,0)));
}

cVector2 vNormalR (const cVector2& v1) {
	return vUnitVector(cVector2(v1.get(1,0),-v1.get(0,0)));
}

cVector2 vNormalL (const cVector2& v1) {
	return vUnitVector(cVector2(-v1.get(1,0),v1.get(0,0)));
}

cVector2 vVecProj (const cVector2& projVec, const cVector2& projAxis) {
	// Scalar Projection: s = A dot uB, s = scalar projection, A
	// projected Vector, uB = unit vector of axis
	// Vector Projection: v = s * uB
	cVector2 unitProjAxis = vUnitVector(projAxis);
	return cVector2((vDotProd(projVec,unitProjAxis)*unitProjAxis));
}

cVector2 vRotate (const cVector2& v1, const double& rotRad) {
	cMatrix rotMatrix(2,2);
	rotMatrix.set(0,0) = std::cos(rotRad);
	rotMatrix.set(0,1) = -std::sin(rotRad);
	rotMatrix.set(1,0) = -rotMatrix.get(0,1);
	rotMatrix.set(1,1) = rotMatrix.get(0,0);
	return cVector2(rotMatrix*v1);
}

cVector2 vMirror (const cVector2& v1, const cVector2& vMirror) {
	return cVector2((2*vVecProj(v1,vMirror))-v1);
}

cVector2 intersectionLineLine (const cVector2& pt1, const cVector2& lineDir1,
		const cVector2& pt2, const cVector2& lineDir2) {
	double m1, m2, b1, b2, xInt, yInt;
	m1 = m2 = b1 = b2 = xInt = yInt = std::nan("");
	if ((lineDir1.getX() == 0 && lineDir2.getX() == 0) ||
			(lineDir1.getY() == 0 && lineDir2.getY() == 0))
		// throw an error, lines are parallel
		throw(std::runtime_error("Lines are parallel"));
	if (lineDir1.getX() == 0) {
		// Vertical asymptote
		xInt = pt1.getX();
		m1 = 1;
		b1 = 0;
	}
	if (lineDir1.getY() == 0) {
		// Horizontal asymptote
		yInt = pt1.getY();
		m1 = 0;
	}
	if (lineDir2.getX() == 0) {
		// Vertical asymptote
		xInt = pt2.getX();
		m2 = 1;
		b2 = 0;
	}
	if (lineDir2.getY() == 0) {
		// Horizontal asymptote
		yInt = pt2.getY();
		m2 = 0;
	}
	if (std::isnan(m1) == true)
		m1 = lineDir1.getY()/lineDir1.getX();
	if (std::isnan(m2) == true)
		m2 = lineDir2.getY()/lineDir2.getX();
	if (m1 == m2)
		throw(std::runtime_error("Lines are parallel"));
	if (std::isnan(b1) == true)
		b1 = pt1.getY()-m1*pt1.getX();
	if (std::isnan(b2) == true)
		b2 = pt2.getY()-m2*pt2.getX();
	if (std::isnan(xInt) == true && std::isnan(yInt) == true) {
		xInt = (b2-b1)/(m1-m2);
		yInt = m1*xInt+b1;
	}
	if (std::isnan(xInt) == false && std::isnan(yInt) == true) {
		yInt = m1*xInt+b1;
	}
	if (std::isnan(xInt) == true && std::isnan(yInt) == false) {
		xInt = (yInt-b1)/m1;
	}
	return cVector2(xInt,yInt);
}

double distPtToLine (const cVector2& pt, const cVector2& lineDir,
		const cVector2& ptLine) {
	cVector2 normDir = vNormalR(lineDir);
	return vMagnitude(intersectionLineLine(pt,normDir,ptLine,lineDir));
}
