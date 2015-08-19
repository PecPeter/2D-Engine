#include "mathLinAlgebra.hpp"

cMatrix rotnTransform (double rotnRad) {
	cMatrix rotnMatrix(2,2);
	rotnMatrix.set(0,0) = std::cos(rotnRad);
	rotnMatrix.set(0,1) = -std::sin(rotnRad);
	rotnMatrix.set(1,0) = std::sin(rotnRad);
	rotnMatrix.set(1,1) = std::cos(rotnRad);
	return rotnMatrix;
}
