#ifndef MUSIC_CATALOG_H
#define MUSIC_CATALOG_H
#include <iostream>
#include <string>
#include "Catalog.h"
using namespace std;

class MusicCatalog : public Catalog {
public:
	MusicCatalog();//default constructor
	string getArtists() const;
	string getGenre() const;
	void setArtists(const string& newArtists);
	void setGenre(const string& newGenre);
	void setDataFields(const vector<string>& elements);// gelen vektördeki elemanları sırasıyla yerlerine yerleştiriyor(title year vs)
	friend ostream& operator<<(ostream& out, const MusicCatalog& obj);
	void search(const string type,const string target) const;//dosyaya yazdırmayı kolaylaştırmak için
protected:
	string artists;
	string genre;
};
#endif
