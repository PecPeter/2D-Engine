#ifndef MATHVECTORUNITTEST_HPP
#define MATHVECTORUNITTEST_HPP

#include <iostream>
#include "mathVector.hpp"

void mathVectorTest (void) {
	cVector2 v1(1,2.9),
			 v2(v1);
	std::cout << "Printing v1:\n";
//	printMatrix(v1);
	std::cout << "Printing v2:\n";
//	printMatrix(v2);
}

#endif
