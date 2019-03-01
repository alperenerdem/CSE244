#ifndef SPARSE_VECTOR_H
#define SPARSE_VECTOR_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
class SparseVector
{
	public:
		SparseVector();
		SparseVector(const char *filename);
		friend SparseVector operator+(const SparseVector &v1, const SparseVector &v2);
		friend SparseVector operator-(const SparseVector &v1, const SparseVector &v2);
		friend SparseVector operator-(const SparseVector &v1);
		SparseVector& operator=(const SparseVector &v1);
		friend std::ostream & operator <<(std::ostream & output, SparseVector const& v1);
		double dot(const SparseVector &v1,const SparseVector &v2);
	private:
		vector <double> SparVec;
		vector <int> SparVecData;


};

#endif
