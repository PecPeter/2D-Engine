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
