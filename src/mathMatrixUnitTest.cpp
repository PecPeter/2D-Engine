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
	std::cout << m1;

	cMatrix m2(2,3);
	m2.set(0,0) = 1;
	m2.set(0,1) = 2;
	m2.set(0,2) = 3;
	m2.set(1,0) = 4;
	m2.set(1,1) = 5;
	m2.set(1,2) = 6;
	
	compareMatrices(m2,m1);
	
	std::cout << "\t...Using cMatrix(const cMatrix&): ";
	cMatrix m3(m1);
	compareMatrices(m3,m1);

	std::cout << "\t...Using assignment operator: ";
	cMatrix m4(5,5);
	m4 = m1;
	compareMatrices(m4,m1);

	cMatrix m5,m6,m7,m8,m9,m0;
	std::cout << "\nTesting cMatrix member functions:\n";
	std::cout << "\t...Testing resize/getSize:\n";
	std::cout << "\t\t...getSize: ";
	int nRows = -1, nCols = -1;
	m5.resize(10,10);
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
	std::cout << "\t\t...getRowSize: ";
	if (m5.getRowSize() == 3)
		std::cout << "PASSED\n";
	std::cout << "\t\t...getColSize: ";
	if (m5.getColSize() == 3)
		std::cout << "PASSED\n";
	std::cout << "\nTesting operator functions:\n";
	m3 = m1;
	m4 = m1;
	m1.set(0,0) = 1.5;
	m1.set(0,1) = 3;
	m1.set(0,2) = 4.5;
	m1.set(1,0) = 6;
	m1.set(1,1) = 7.5;
	m1.set(1,2) = 9;
	std::cout << "\t...operator* (cMatrix, double): ";
	m2 = m2 * 1.5;
	compareMatrices(m2,m1);
	std::cout << "\t...operator* (double, cMatrix): ";
	m3 = 1.5*m3;
	compareMatrices(m3,m1);
	std::cout << "\t...operator* (cMatrix, cMatrix): ";
	m4.resize(3,2);
	m4.set(0,0) = 1.5;
	m4.set(0,1) = 3;
	m4.set(1,0) = 4.5;
	m4.set(1,1) = 6;
	m4.set(2,0) = 7.5;
	m4.set(2,1) = 9;

	m5.resize(2,2);
	m5.set(0,0) = 49.5;
	m5.set(0,1) = 63;
	m5.set(1,0) = 110.25;
	m5.set(1,1) = 144;
	m6 = m1*m4;
	compareMatrices(m6,m5);
//	m6 = m4*m1;		//THIS SHOULD THROW AN ERROR

	std::cout << "\t...operator*= (cMatrix, cMatrix): ";
	m1 *= m4;
	compareMatrices(m1,m5);
	std::cout << "\t...operator*= (cMatrix, double): ";
	m1.resize(2,3);
	m1.set(0,0) = 1.5;
	m1.set(0,1) = 3;
	m1.set(0,2) = 4.5;
	m1.set(1,0) = 6;
	m1.set(1,1) = 7.5;
	m1.set(1,2) = 9;
	m4.resize(2,3);
	m4.set(0,0) = 1;
	m4.set(0,1) = 2;
	m4.set(0,2) = 3;
	m4.set(1,0) = 4;
	m4.set(1,1) = 5;
	m4.set(1,2) = 6;
	m4 = 1.5*m4;
	compareMatrices(m4,m1);

	std::cout << "\t...operator+ (cMatrix, cMatrix): ";
	m2.set(0,0) = 50;
	m2.set(0,1) = 3.14567;
	m2.set(0,2) = 9.9999;
	m2.set(1,0) = 0.0001;
	m2.set(1,1) = 6;
	m2.set(1,2) = 988948;
	
	m3.set(0,0) = 51.5;
	m3.set(0,1) = 6.14567;
	m3.set(0,2) = 14.4999;
	m3.set(1,0) = 6.0001;
	m3.set(1,1) = 13.5;
	m3.set(1,2) = 988957;
	m5 = m2+m1;
	compareMatrices(m5,m3);

	std::cout << "\t...operator+ (double, cMatrix): ";
	m4.set(0,0) = 0.5;
	m4.set(0,1) = 2;
	m4.set(0,2) = 3.5;
	m4.set(1,0) = 5;
	m4.set(1,1) = 6.5;
	m4.set(1,2) = 8;
	m5 = 1+m4;
	compareMatrices(m5,m1);

	std::cout << "\t...operator+ (cMatrix, double): ";
	m5 = m4+1;
	compareMatrices(m5,m1);

	std::cout << "\t...operator+= (cMatrix, double): ";
	m4 += 1;
	compareMatrices(m4,m1);

	std::cout << "\t...operator- (cMatrix, cMatrix): ";
	m1.resize(2,3);
	m1.set(0,0) = 1.5;
	m1.set(0,1) = 3;
	m1.set(0,2) = 4.5;
	m1.set(1,0) = 6;
	m1.set(1,1) = 7.5;
	m1.set(1,2) = 9;

	m2.resize(2,3);
	m2.set(0,0) = 1;
	m2.set(0,1) = 2.5;
	m2.set(0,2) = 4;
	m2.set(1,0) = 5.5;
	m2.set(1,1) = 7;
	m2.set(1,2) = 8.5;

	m3.resize(2,3);
	m3.set(0,0) = 0.5;
	m3.set(0,1) = 0.5;
	m3.set(0,2) = 0.5;
	m3.set(1,0) = 0.5;
	m3.set(1,1) = 0.5;
	m3.set(1,2) = 0.5;
	
	m4 = m1-m2;
	compareMatrices(m4,m3);

	std::cout << "\t...operator- (double, cMatrix): ";
	m4 = -3-m1;

	m3.set(0,0) = -4.5;
	m3.set(0,1) = -6;
	m3.set(0,2) = -7.5;
	m3.set(1,0) = -9;
	m3.set(1,1) = -10.5;
	m3.set(1,2) = -12;
	compareMatrices(m4,m3);

	std::cout << "\t...operator- (cMatrix, double): ";
	m4 = m1-3;
	m3.set(0,0) = -1.5;
	m3.set(0,1) = 0;
	m3.set(0,2) = 1.5;
	m3.set(1,0) = 3;
	m3.set(1,1) = 4.5;
	m3.set(1,2) = 6;
	compareMatrices(m4,m3);

	std::cout << "\t...operator-= (cMatrix, cMatrix): ";
	m1.resize(2,3);
	m1.set(0,0) = 1.5;
	m1.set(0,1) = 3;
	m1.set(0,2) = 4.5;
	m1.set(1,0) = 6;
	m1.set(1,1) = 7.5;
	m1.set(1,2) = 9;

	m2.resize(2,3);
	m2.set(0,0) = 1;
	m2.set(0,1) = 2.5;
	m2.set(0,2) = 4;
	m2.set(1,0) = 5.5;
	m2.set(1,1) = 7;
	m2.set(1,2) = 8.5;

	m3.resize(2,3);
	m3.set(0,0) = 0.5;
	m3.set(0,1) = 0.5;
	m3.set(0,2) = 0.5;
	m3.set(1,0) = 0.5;
	m3.set(1,1) = 0.5;
	m3.set(1,2) = 0.5;

	m1-=m2;
	compareMatrices(m1,m3);

	std::cout << "\t...operator-= (cMatrix, double): ";
	m4.resize(2,3);
	m4.set(0,0) = 0;
	m4.set(0,1) = 0;
	m4.set(0,2) = 0;
	m4.set(1,0) = 0;
	m4.set(1,1) = 0;
	m4.set(1,2) = 0;

	m3-=0.5;
	compareMatrices(m3,m4);

	std::cout << "Testing mTranspose (cMatrix): ";
	m1 = mTranspose(m2);
	m3.resize(3,2);
	m3.set(0,0) = 1;
	m3.set(0,1) = 5.5;
	m3.set(1,0) = 2.5;
	m3.set(1,1) = 7;
	m3.set(2,0) = 4;
	m3.set(2,1) = 8.5;
	compareMatrices (m1,m3);

	std::cout << "Testing mCoeffMult (cMatrix, cMatrix): ";

	m1.resize(2,3);
	m1.set(0,0) = 1;
	m1.set(0,1) = 2;
	m1.set(0,2) = 3;
	m1.set(1,0) = 4;
	m1.set(1,1) = 5;
	m1.set(1,2) = 6;

	m2.resize(2,3);
	m2.set(0,0) = 6;
	m2.set(0,1) = 5;
	m2.set(0,2) = 4;
	m2.set(1,0) = 3;
	m2.set(1,1) = 2;
	m2.set(1,2) = 1;

	m3.resize(2,3);
	m3.set(0,0) = 6;
	m3.set(0,1) = 10;
	m3.set(0,2) = 12;
	m3.set(1,0) = 12;
	m3.set(1,1) = 10;
	m3.set(1,2) = 6;
	m4 = mCoeffMult(m1,m2);
	compareMatrices(m4,m3);
}

void compareMatrices (const cMatrix& calculatedMatrix,
		const cMatrix& solutionMatrix) {
	if (calculatedMatrix == solutionMatrix)
		std::cout << "PASSED\n";
	else {
		std::cout << "FAILED. CALCULATED MATRIX:\n" << calculatedMatrix <<
			"\n\tSOLUTION MATRIX:\n" << solutionMatrix << "\n";
	}
}
