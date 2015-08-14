#include "mathVectorUnitTest.hpp"

void mathVectorUnitTest (void) {
	std::cout << "Testing cVector2 constructors:\n" <<
		"\t...cVector2 (void):\n";
	cVector2 v1;
	std::cout << v1 << "\nShould be:\n0\n0\n";

	std::cout << "\t...cVector2 (double, double): ";
	cVector2 v2(-3.2,9999);
	v1.set(0,0) = -3.2;
	v1.set(1,0) = 9999;
	compareVectors(v2,v1);

	std::cout << "\t...cVector2 (cVector2): ";
	cVector2 v3(v1);
	compareVectors(v3,v1);

	std::cout << "\t...cVector2 (cMatrix): ";
	cMatrix m1(2,1);
	m1.set(0,0) = 10;
	m1.set(1,0) = -10;
	cVector2 v4(m1);
	v1.set(0,0) = 10;
	v1.set(1,0) = -10;
	compareVectors(v4,v1);

	v1.set(0,0) = 4;
	v1.set(1,0) = -9.4;
	v2.set(0,0) = 0.3;
	v2.set(1,0) = 5;
	std::cout << "Using vectors:\n" << v1 << "\nAnd:\n" << v2 << "\n";
	std::cout << "Testing vector functions:\n" <<
		"\t...vSqMagnitude: " << vSqMagnitude(v1) << "\n" <<
		"\t...vMagnitude: " << vMagnitude(v1) << "\n" <<
		"\t...vDotProd: " << vDotProd(v1,v2) << "\n" <<
		"\t...vAngleRad: " << vAngleRad(v1,v2) << "\n" <<
		"\t...vAngleDeg: " << vAngleDeg(v1,v2) << "\n" <<
		"\t...vScalProj: " << vScalProj(v1,v2) << "\n" <<
		"\t...vUnitVector:\n" << vUnitVector(v1) << "\n" <<
		"\t...vAbsolute:\n" << vAbsolute(v1) << "\n" <<
		"\t...vNormalR:\n" << vNormalR(v1) << "\n" <<
		"\t...vNormalL:\n" << vNormalL(v1) << "\n" <<
		"\t...vVecProj:\n" << vVecProj(v1,v2) << "\n";
	std::cout << "Testing line intersection solver:\n";
	v1.set(0,0) = 5;
	v1.set(1,0) = 0;
	v2.set(0,0) = 0;
	v2.set(1,0) = -10;
	cVector2 dir1(1,1),
			 dir2(1,1);
	std::cout << "\tIntersection point using pt1: " <<
		v1 << "\n\tdir1: " << dir1 << "\n\tpt2: " <<
		v2 << "\n\tdir2: " << dir2;
	cVector2 intersectionPt = intersectionLineLine(v1,dir1,v2,dir2);
	std::cout << "\n\tPoint: " << intersectionPt;
}

void compareVectors (const cVector2& calculatedVector,
		const cVector2& solutionVector) {
	if (calculatedVector == solutionVector)
		std::cout << "PASSED\n";
	else {
		std::cout << "FAILED. CALCULATED VECTOR:\n" <<
			calculatedVector << "\nSOLUTION VECTOR:\n" <<
			solutionVector;
	}
}
