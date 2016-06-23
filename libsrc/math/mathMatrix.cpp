#include "mathMatrix.hpp"

cMatrix::cMatrix (void): nRows_(0), nCols_(0) {}

cMatrix::cMatrix (const cMatrix& matrix): nRows_(matrix.getRowSize()),
		nCols_(matrix.getColSize()) {
	matrix_.resize(nRows_*nCols_);
	for (int i = 0; i < nRows_; ++i) {
		for (int j = 0; j < nCols_; ++j) {
			matrix_.at(i*nCols_+j) = matrix.get(i,j);
		}
	}
}

cMatrix::cMatrix (int nRows, int nCols): nRows_(nRows), nCols_(nCols) {
	matrix_.resize(nRows_*nCols_);
}

cMatrix& cMatrix::operator= (const cMatrix& rhs) {
	int nRows, nCols;
	rhs.getSize(&nRows,&nCols);
	//Change this so that in the event of an error, nothing changes
	matrix_.resize(nRows*nCols);
	nRows_ = nRows;
	nCols_ = nCols;
	for (int i = 0; i < nRows_; i++) {
		for (int j = 0; j < nCols_; j++) {
			matrix_.at(j+i*nCols_) = rhs.get(i,j);
		}
	}
	return *this;
}

cMatrix::~cMatrix (void) {
	matrix_.clear();
}

double& cMatrix::set (int rowIndex, int colIndex) {
	if (colIndex >= nCols_ || rowIndex >= nRows_)
		//Throw an error here
		;
	return matrix_.at(rowIndex*nCols_+colIndex);
}

double cMatrix::get (int rowIndex, int colIndex) const {
	if (colIndex >= nCols_ || rowIndex >= nRows_)
		//Throw an error here
		;
	return matrix_.at(rowIndex*nCols_+colIndex);
}

void cMatrix::resize (int nRows, int nCols) {
	if (nRows_ != nRows || nCols_ != nCols) {
		nRows_ = nRows;
		nCols_ = nCols;
		matrix_.resize(nRows_*nCols_,0);
	}
}

void cMatrix::getSize (int* nRows, int* nCols) const {
	*nRows = nRows_;
	*nCols = nCols_;
}

int cMatrix::getRowSize (void) const {
	return nRows_;
}

int cMatrix::getColSize (void) const {
	return nCols_;
}

bool operator== (const cMatrix& lhs, const cMatrix& rhs) {
	int nRowsL, nColsL,
		nRowsR, nColsR;
	lhs.getSize(&nRowsL,&nColsL);
	rhs.getSize(&nRowsR,&nColsR);
	if (nRowsL != nRowsR || nColsL != nColsR) {
		return false;
	}
	for (int i = 0; i < nRowsL; ++i) {
		for (int j = 0; j < nColsL; ++j) {
			if ((std::isnan(lhs.get(i,j)) == true) &&
					(std::isnan(rhs.get(i,j)) == true))
				;
			else if (lhs.get(i,j) != rhs.get(i,j))
				return false;
		}
	}
	return true;
}

bool operator!= (const cMatrix& lhs, const cMatrix& rhs) {
	return !(lhs == rhs);
}

cMatrix operator* (const cMatrix& lhs, const cMatrix& rhs) {
	if (lhs.getColSize() != rhs.getRowSize()) {
		//Throw error
		;
	}
	int rows = lhs.getRowSize(),
		cols = rhs.getColSize(),
		colMax = lhs.getColSize();
	cMatrix temp(rows,cols);
	for (int rItr = 0; rItr < rows; rItr++) {
		for (int cItr = 0; cItr < cols; cItr++) {
			for (int itr = 0; itr < colMax; itr++) {
				temp.set(rItr,cItr) += lhs.get(rItr,itr)*rhs.get(itr,cItr);
			}
		}
	}
	return temp;
}

cMatrix operator* (const double& lhs, const cMatrix& rhs) {
	int rows, cols;
	rhs.getSize(&rows,&cols);
	cMatrix temp(rows,cols);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			temp.set(i,j) = lhs*rhs.get(i,j);
		}
	}
	return temp;
}

cMatrix operator* (const cMatrix& lhs, const double& rhs) {
	int rows, cols;
	lhs.getSize(&rows,&cols);
	cMatrix temp(rows,cols);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			temp.set(i,j) = lhs.get(i,j)*rhs;
		}
	}
	return temp;
}

cMatrix& operator*= (cMatrix& lhs, const cMatrix& rhs) {
	if (lhs.getColSize() != rhs.getRowSize()) {
		//Throw error
		;
	}
	int rows = lhs.getRowSize(),
		cols = rhs.getColSize(),
		colMax = lhs.getColSize();
	cMatrix temp(rows,cols);
	for (int rItr = 0; rItr < rows; rItr++) {
		for (int cItr = 0; cItr < cols; cItr++) {
			for (int itr = 0; itr < colMax; itr++) {
				temp.set(rItr,cItr) += lhs.get(rItr,itr)*rhs.get(itr,cItr);
			}
		}
	}
	lhs = temp;
	return lhs;
}
	
cMatrix& operator*= (cMatrix& lhs, const double& rhs) {
	int rows, cols;
	lhs.getSize(&rows,&cols);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			lhs.set(i,j) *= rhs;
		}
	}
	return lhs;
}

cMatrix operator+ (const cMatrix& lhs, const cMatrix& rhs) {
	int nRowsL, nColsL,
		nRowsR, nColsR;
	lhs.getSize(&nRowsL,&nColsL);
	rhs.getSize(&nRowsR,&nColsR);
	if (nRowsL != nRowsR || nColsL != nColsR) {
		//Throw exception
	}
	cMatrix temp(nRowsL,nColsL);
	for (int i = 0; i < nRowsL; ++i) {
		for (int j = 0; j < nColsL; ++j) {
			temp.set(i,j) = lhs.get(i,j)+rhs.get(i,j);
		}
	}
	return temp;
}

cMatrix operator+ (const double& lhs, const cMatrix& rhs) {
	int nRows, nCols;
	rhs.getSize(&nRows,&nCols);
	cMatrix temp(nRows,nCols);
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			temp.set(i,j) = lhs+rhs.get(i,j);
		}
	}
	return temp;
}

cMatrix operator+ (const cMatrix& lhs, const double& rhs) {
	int nRows, nCols;
	lhs.getSize(&nRows,&nCols);
	cMatrix temp(nRows,nCols);
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			temp.set(i,j) = lhs.get(i,j)+rhs;
		}
	}
	return temp;
}

cMatrix& operator+= (cMatrix& lhs, const cMatrix& rhs) {
	int nRowsL, nColsL,
		nRowsR, nColsR;
	lhs.getSize(&nRowsL,&nColsL);
	rhs.getSize(&nRowsR,&nColsR);
	if (nRowsL != nRowsR || nColsL != nColsR) {
		//Throw exception
	}
	for (int i = 0; i < nRowsL; ++i) {
		for (int j = 0; j < nColsL; ++j) {
			lhs.set(i,j) += rhs.get(i,j);
		}
	}
	return lhs;
}

cMatrix& operator+= (cMatrix& lhs, const double& rhs) {
	int nRows, nCols;
	lhs.getSize(&nRows,&nCols);
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			lhs.set(i,j) += rhs;
		}
	}
	return lhs;
}

cMatrix operator- (const cMatrix& lhs, const cMatrix& rhs) {
	int nRowsL, nColsL,
		nRowsR, nColsR;
	lhs.getSize(&nRowsL,&nColsL);
	rhs.getSize(&nRowsR,&nColsR);
	if (nRowsL != nRowsR || nColsL != nColsR) {
		//Throw exception
	}
	cMatrix temp(nRowsL,nColsL);
	for (int i = 0; i < nRowsL; ++i) {
		for (int j = 0; j < nColsL; ++j) {
			temp.set(i,j) = lhs.get(i,j)-rhs.get(i,j);
		}
	}
	return temp;
}

cMatrix operator- (const double& lhs, const cMatrix& rhs) {
	int nRows, nCols;
	rhs.getSize(&nRows,&nCols);
	cMatrix temp(nRows,nCols);
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			temp.set(i,j) = lhs-rhs.get(i,j);
		}
	}
	return temp;
}

cMatrix operator- (const cMatrix& lhs, const double& rhs) {
	int nRows, nCols;
	lhs.getSize(&nRows,&nCols);
	cMatrix temp(nRows,nCols);
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			temp.set(i,j) = lhs.get(i,j)-rhs;
		}
	}
	return temp;
}

cMatrix& operator-= (cMatrix& lhs, const cMatrix& rhs) {
	int nRowsL, nColsL,
		nRowsR, nColsR;
	lhs.getSize(&nRowsL,&nColsL);
	rhs.getSize(&nRowsR,&nColsR);
	if (nRowsL != nRowsR || nColsL != nColsR) {
		//Throw exception
	}
	for (int i = 0; i < nRowsL; ++i) {
		for (int j = 0; j < nColsL; ++j) {
			lhs.set(i,j) -= rhs.get(i,j);
		}
	}
	return lhs;
}

cMatrix& operator-= (cMatrix& lhs, const double& rhs) {
	int nRows, nCols;
	lhs.getSize(&nRows,&nCols);
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			lhs.set(i,j) -= rhs;
		}
	}
	return lhs;
}

std::ostream& operator<< (std::ostream& outstream, const cMatrix& m1) {
	int nRows, nCols;
	m1.getSize(&nRows,&nCols);
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			outstream << m1.get(i,j) << " ";
		}
		outstream << "\n";
	}
	return outstream;
}

cMatrix mTranspose (const cMatrix& m1) {
	int nRows,
		nCols;
	m1.getSize(&nRows,&nCols);
	cMatrix temp(nCols,nRows);
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			temp.set(j,i) = m1.get(i,j);
		}
	}
	return temp;
}

cMatrix mCoeffMult (const cMatrix& m1, const cMatrix& m2) {
	int nRows,
		nCols;
	m1.getSize(&nRows,&nCols);
	if (nRows != m2.getRowSize() ||
			nCols != m2.getColSize()) {
		//Throw error
		;
	}
	cMatrix temp(nRows,nCols);
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			temp.set(i,j) = m1.get(i,j)*m2.get(i,j);
		}
	}
	return temp;
}
