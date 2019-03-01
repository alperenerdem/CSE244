#ifndef BOOK_CATALOG_H
#define BOOK_CATALOG_H
#include <iostream>
#include <string>
#include "Catalog.h"
using namespace std;

class BookCatalog : public Catalog {
public:
	BookCatalog();//default constructor 
	string getAuthors() const;
	string getTags() const;
	void setDataFields(const vector<string>& elements);// gelen vektördeki elemanları sırasıyla yerlerine yerleştiriyor(title year vs)
	void setAuthors(const string& newAuthors);
	void setTags(const string& newTags);
	friend ostream& operator<<(ostream& out, const BookCatalog& obj);
	void search(const string type,const string target) const;//dosyaya yazdırmayı kolaylaştırmak için
protected:
	string authors;
	string tags;
};
#endif
