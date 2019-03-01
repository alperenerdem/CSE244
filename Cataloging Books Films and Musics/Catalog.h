#ifndef CATALOG_H
#define CATALOG_H
#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <fstream>
using namespace std; 

class Catalog {
public:
	Catalog();
	string getTitle() const;
	string getYear() const;
	virtual void setDataFields(const vector<string>& elements) = 0;//objesi oluşturulamasın
	virtual void search(const string type,const string target) const = 0;
	void setTitle(const string& newTitle);
	void setYear(const string& newYear);	
protected:
	string title;
	string year;
};
#endif
