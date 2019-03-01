#include "Catalog.h"
using namespace std; 

Catalog::Catalog() : title(""), year("") 
{ }

string Catalog::getTitle() const {
	return (title);
}

string Catalog::getYear() const {
	return (year);
}

void Catalog::setYear(const string& newYear) {
	year = newYear;
}

void Catalog::setTitle(const string& newTitle) {
	title = newTitle;
}
