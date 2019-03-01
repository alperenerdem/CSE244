#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//transpoz ve *operatorunu yapamadım
using namespace std;
class SparseMatrix
{
	public:
		SparseMatrix();
		SparseMatrix(const char *filename);
		friend SparseMatrix operator+(const SparseMatrix &m1, const SparseMatrix &m2);
		friend SparseMatrix operator-(const SparseMatrix &m1, const SparseMatrix &m2);
		friend SparseMatrix operator-(const SparseMatrix &m1);
		SparseMatrix& operator=(const SparseMatrix &m1);
		friend std::ostream & operator <<(std::ostream & output, SparseMatrix const& m1);
		//friend SparseMatrix operator*(const SparseMatrix &m1, const SparseMatrix &m2);
		//friend SparseMatrix tranpose(const SparseMatrix &m1);
	private:
		vector < vector <double>  > SparMat;
		vector < vector <int> > SparMatData;
		vector <int> SparMatRowData;


};
#endif

