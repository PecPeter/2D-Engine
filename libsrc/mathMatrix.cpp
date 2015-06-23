#include "mathMatrix.hpp"

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

bool cMatrix::operator== (const cMatrix& rhs) const {
	int nRows, nCols;
	rhs.getSize(&nRows,&nCols);
	if (nRows_ != nRows || nCols_ != nCols) {
		return false;
	}
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			if (get(i,j) != rhs.get(i,j))
				return false;
		}
	}
	return true;
}

bool cMatrix::operator!= (const cMatrix& rhs) const {
	return !(*this == rhs);
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

cMatrix cMatrix::operator* (const cMatrix& rhs) const {
	if (getColSize() != rhs.getRowSize()) {
		//Throw error
		;
	}
	int rows = getRowSize(),
		cols = rhs.getColSize(),
		colMax = getColSize();
	cMatrix temp(rows,cols);
	for (int rItr = 0; rItr < rows; rItr++) {
		for (int cItr = 0; cItr < cols; cItr++) {
			for (int itr = 0; itr < colMax; itr++) {
				temp.set(rItr,cItr) += get(rItr,itr)*rhs.get(itr,cItr);
			}
		}
	}
	return temp;
}

cMatrix& cMatrix::operator*= (const cMatrix& rhs) {
	if (getColSize() != rhs.getRowSize()) {
		//Throw error
		;
	}
	int rows = getRowSize(),
		cols = rhs.getColSize(),
		colMax = getColSize();
	cMatrix temp(rows,cols);
	for (int rItr = 0; rItr < rows; rItr++) {
		for (int cItr = 0; cItr < cols; cItr++) {
			for (int itr = 0; itr < colMax; itr++) {
				temp.set(rItr,cItr) += get(rItr,itr)*rhs.get(itr,cItr);
			}
		}
	}
	*this = temp;
	return *this;
}

cMatrix cMatrix::operator+ (const cMatrix& rhs) const {
	int rows, cols;
	rhs.getSize(&rows,&cols);
	if (nRows_ != rows || nCols_ != cols) {
		//Throw exception
	}
	cMatrix temp(rows,cols);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			temp.set(i,j) = get(i,j)+rhs.get(i,j);
		}
	}
	return temp;
}

cMatrix& cMatrix::operator+= (const cMatrix& rhs) {
	int rows, cols;
	rhs.getSize(&rows,&cols);
	if (nRows_ != rows || nCols_ != cols) {
		//Throw exception
	}
	cMatrix temp(rows,cols);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			temp.set(i,j) = get(i,j)+rhs.get(i,j);
		}
	}
	*this = temp;
	return *this;
}

cMatrix cMatrix::operator- (const cMatrix& rhs) const {
	int rows, cols;
	rhs.getSize(&rows,&cols);
	if (nRows_ != rows || nCols_ != cols) {
		//Throw exception
	}
	cMatrix temp(rows,cols);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			temp.set(i,j) = get(i,j)-rhs.get(i,j);
		}
	}
	return temp;
}

cMatrix& cMatrix::operator-= (const cMatrix& rhs) {
	int rows, cols;
	rhs.getSize(&rows,&cols);
	if (nRows_ != rows || nCols_ != cols) {
		//Throw exception
	}
	cMatrix temp(rows,cols);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			temp.set(i,j) = get(i,j)-rhs.get(i,j);
		}
	}
	*this = temp;
	return *this;
}

void cMatrix::transpose (void) {
	int swap = nRows_;
	nRows_ = nCols_;
	nCols_ = swap;

	std::vector<double> swapMatrix = matrix_;
	for (int i = 0; i < nCols_; ++i) {
		for (int j = 0; j < nRows_; ++j) {
			set(j,i) = swapMatrix.at(i*nRows_+j);
		}
	}
}

void cMatrix::scalarMult (const double& scalar) {
	for (int i = 0; i < nRows_; ++i) {
		for (int j = 0; j < nCols_; ++j) {
			set(i,j) = get(i,j)*scalar;
		}
	}
}

cMatrix mtrxMultPw (const cMatrix& m1, const cMatrix& m2) {
	if (m1.getColSize() != m2.getColSize() ||
			m1.getRowSize() != m2.getRowSize()) {
		//Throw error
		;
	}
	cMatrix temp(m1.getRowSize(),m1.getColSize());
	int nRows, nCols;
	temp.getSize(&nRows,&nCols);
	for (int rItr = 0; rItr < nRows; rItr++) {
		for (int cItr = 0; cItr < nCols; cItr++) {
			temp.set(rItr,cItr) = m1.get(rItr,cItr)*m2.get(rItr,cItr);
		}
	}
	return temp;
}

cMatrix transpose (const cMatrix& m1) {
	int rows, cols;
	m1.getSize(&rows,&cols);
	cMatrix temp(cols,rows);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			temp.set(j,i) = m1.get(i,j);
		}
	}
	return temp;
}
