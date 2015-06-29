#include "mathVector.hpp"

cVector2::cVector2 (double x, double y): cMatrix(2,1) {
	set(0,0) = x;
	set(1,0) = y;
}

cVector2::cVector2 (const cVector2& vector): cMatrix(vector) {}

cVector2::~cVector2 (void) {}

/*
cVector2 cVector2::projection (const cVector2& projAxis) {
	return;
	return cVector2();
}
*/
double cVector2::sqMagnitude (void) const {
	double sqSum = 0;
	for (int i = 0; i < nRows_; ++i) {
		for (int j = 0; j < nCols_; ++j) {
			sqSum += get(i,j)*get(i,j);
		}
	}
	return sqSum;
};

double cVector2::magnitude (void) const {
	return sqMagnitude();
}

double dotProd (const cVector2& v1, const cVector2& v2) {
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

double angleRad (const cVector2& v1, const cVector2& v2) {
	return std::acos(dotProd(v1,v2)/(v1.magnitude()*v2.magnitude()));
}

double angleDeg (const cVector2& v1, const cVector2& v2) {
	return angleRad(v1,v2)*(180.0/3.14159265);
}

cVector2 unitVector (const cVector2& v1) {
	cVector2 tmpVec(v1);
	tmpVec.scalarMult(1.0/v1.magnitude());
	return tmpVec;
}

cVector2 absolute (const cVector2& v1) {
	return cVector2(std::abs(v1.get(0,0)),std::abs(v1.get(1,0)));
}
