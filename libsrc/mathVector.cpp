#include "mathVector.hpp"

cVector2::cVector2 (void): cMatrix(2,1) {}

cVector2::cVector2 (const double& x, const double& y): cMatrix(2,1) {
	set(0,0) = x;
	set(1,0) = y;
}

cVector2::cVector2 (const cVector2& vector): cMatrix(vector) {}

cVector2::cVector2 (const cMatrix& matrix) {
	matrix.getSize(&nRows_,&nCols_);
	if (nRows_ != 2 && nCols_ != 1) {
		//Throw an error
		;
	}
	for (int i = 0; i < nRows_; ++i) {
		set(i,0) = matrix.get(i,0);
	}
}

cVector2::~cVector2 (void) {}

double cVector2::getX (void) const {
	return get(0,0);
}

double cVector2::getY (void) const {
	return get(1,0);
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

double angleDeg (const cVector2& v1, const cVector2& v2) {
	return vAngleRad(v1,v2)*(180.0/3.14159265);
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

cVector2 vNormal (const cVector2& v1) {
	return cVector2(v1.get(1,0),-v1.get(0,1));
}

cVector2 vVecProj (const cVector2& projVec, const cVector2& projAxis) {
	// Scalar Projection: s = A dot uB, s = scalar projection, A
	// projected Vector, uB = unit vector of axis
	// Vector Projection: v = s * uB
	cVector2 unitProjAxis = vUnitVector(projAxis);
	return cVector2((vDotProd(projVec,unitProjAxis)*unitProjAxis));
}
