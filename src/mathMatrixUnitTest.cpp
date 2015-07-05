#include "mathMatrixUnitTest.hpp"

void mathMatrixTest (void) {
	std::cout << "Testing cMatrix constructors:\n";
	std::cout << "\t...Using cMatrix(int,int): ";
	cMatrix m1(2,3);
	m1.set(0,0) = 1;
	m1.set(0,1) = 2;
	m1.set(0,2) = 3;
	m1.set(1,0) = 4;
	m1.set(1,1) = 5;
	m1.set(1,2) = 6;

	cMatrix m2(2,3);
	m2.set(0,0) = 1;
	m2.set(0,1) = 2;
	m2.set(0,2) = 3;
	m2.set(1,0) = 4;
	m2.set(1,1) = 5;
	m2.set(1,2) = 6;
	
	if (m1 == m2)
		std::cout << "PASSED\n";
	else
		std::cout << "FAILED\n";
	
	std::cout << "\t...Using cMatrix(const cMatrix&): ";
	cMatrix m3(m1);
	if (m1 == m3)
		std::cout << "PASSED\n";
	else
		std::cout << "FAILED\n";

	std::cout << "\t...Using assignment operator: ";
	cMatrix m4(5,5);
	m4 = m1;
	if (m1 == m4)
		std::cout << "PASSED\n";
	else
		std::cout << "FAILED\n";

	std::cout << "\nTesting cMatrix member functions:\n";
	std::cout << "\t...Testing resize/getSize:\n";
	std::cout << "\t\t...getSize: ";
	int nRows = -1, nCols = -1;
	cMatrix m5(10,10);
	m5.getSize(&nRows,&nCols);
	if (nRows == 10 && nCols == 10)
		std::cout << "PASSED\n";
	else
		std::cout << "FAILED\n";
	std::cout << "\t\t...resize: ";
	m5.resize(3,3);
	m5.getSize(&nRows,&nCols);
	if (nRows == 3 && nCols == 3)
		std::cout << "PASSED\n";
	else
		std::cout << "FAILED\n";
}
