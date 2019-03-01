#ifndef MOVIE_CATALOG_H
#define MOVIE_CATALOG_H
#include <iostream>
#include <string>
#include "Catalog.h"
using namespace std;

class MovieCatalog : public Catalog {
public:
	MovieCatalog();//default constructor
	string getDirector() const;
	string getStarring() const;
	string getGenre() const;
	void setDirector(const string& newDirector);
	void setStarring(const string& newStarring);
	void setGenre(const string& newGenre);
	void setDataFields(const vector<string>& elements);// gelen vektördeki elemanları sırasıyla yerlerine yerleştiriyor(title year vs)
	void search(const string type,const string target) const;
	friend ostream& operator<<(ostream& out, const MovieCatalog& obj); //dosyaya yazdırmayı kolaylaştırmak için
protected:
	string director;
	string starring;
	string genre;
};
#endif
