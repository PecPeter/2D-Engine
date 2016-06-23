#ifndef MATHMATRIX_HPP
#define MATHMATRIX_HPP

// Remove iostream when testing is completed
#include <iostream>
#include <vector>
#include <cmath>

class cMatrix {
	public:
		cMatrix (void);
		cMatrix (const cMatrix& matrix);
		cMatrix (int nRows, int nCols);
		cMatrix& operator= (const cMatrix& rhs);
		virtual ~cMatrix (void);

		double& set (int rowIndex, int colIndex);
		double get (int rowIndex, int colIndex) const;
		void resize (int nRows, int nCols);
		void getSize (int* nRows, int* nCols) const;
		int getRowSize (void) const;
		int getColSize (void) const;

	protected:
		int nRows_, nCols_;
		std::vector<double> matrix_;
};

bool operator== (const cMatrix& lhs, const cMatrix& rhs);
bool operator!= (const cMatrix& lhs, const cMatrix& rhs);
cMatrix operator* (const cMatrix& lhs, const cMatrix& rhs);
cMatrix operator* (const double& lhs, const cMatrix& rhs);
cMatrix operator* (const cMatrix& lsh, const double& rhs);
cMatrix& operator*= (cMatrix& lhs, const cMatrix& rhs);
cMatrix& operator*= (cMatrix& lhs, const double& rhs);
cMatrix operator+ (const cMatrix& lhs, const cMatrix& rhs);
cMatrix operator+ (const double& lhs, const cMatrix& rhs);
cMatrix operator+ (const cMatrix& lhs, const double& rhs);
cMatrix& operator+= (cMatrix& lhs, const cMatrix& rhs);
cMatrix& operator+= (cMatrix& lhs, const double& rhs);
cMatrix operator- (const cMatrix& lhs, const cMatrix& rhs);
cMatrix operator- (const double& lhs, const cMatrix& rhs);
cMatrix operator- (const cMatrix& lhs, const double& rhs);
cMatrix& operator-= (cMatrix& lhs, const cMatrix& rhs);
cMatrix& operator-= (cMatrix& lhs, const double& rhs);
std::ostream& operator<< (std::ostream& outstream, const cMatrix& m1);
cMatrix mTranspose (const cMatrix& m1);
cMatrix mCoeffMult (const cMatrix& m1, const cMatrix& m2);

#endif
