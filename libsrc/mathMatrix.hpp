#ifndef MATHMATRIX_HPP
#define MATHMATRIX_HPP

#include <vector>

class cMatrix {
	public:
		cMatrix (const cMatrix& matrix);
		cMatrix (int nRows, int nCols);
		virtual ~cMatrix (void);

		double& set (int rowIndex, int colIndex);
		double get (int rowIndex, int colIndex) const;
		void resize (int nRows, int nCols);
		void getSize (int* nRows, int* nCols) const;
		int getRowSize (void) const;
		int getColSize (void) const;

		bool operator== (const cMatrix& rhs) const;
		bool operator!= (const cMatrix& rhs) const;
		cMatrix& operator= (const cMatrix& rhs);
		cMatrix operator* (const cMatrix& rhs) const;
		cMatrix& operator*= (const cMatrix& rhs);
		cMatrix operator+ (const cMatrix& rhs) const;
		cMatrix& operator+= (const cMatrix& rhs);
		cMatrix operator- (const cMatrix& rhs) const;
		cMatrix& operator-= (const cMatrix& rhs);

		void transpose (void);
		void scalarMult (const double& scalar);
	protected:
		int nRows_, nCols_;
		std::vector<double> matrix_;
};

cMatrix mtrxMultPw (const cMatrix& m1, const cMatrix& m2);
cMatrix transpose (const cMatrix& m1);

#endif
