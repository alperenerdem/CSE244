#include "BookCatalog.h"
using namespace std;
void BookCatalog::search(const string type,const string target) const{
		ofstream myfile;
 		 myfile.open ("output.txt",ofstream::app);// dosyaya üzerine yazmamak için devamına eklemek için böyle açmamız gerekiyormuş
		if(type=="title"){
				if (title.find(target) != std::string::npos){// string içinde varsa dosyaya yaz
  					  myfile << *this << '\n';
				}
		}
		else if(type=="year"){
				if (year.find(target) != std::string::npos){// string içinde varsa dosyaya yaz
  					  myfile << *this << '\n';

				}
		}
		else if(type=="authors"){
				if (authors.find(target) != std::string::npos){// string içinde varsa dosyaya yaz
  					  myfile << *this << '\n';

				}
		}
		else if(type=="tags"){
				if (tags.find(target) != std::string::npos){// string içinde varsa dosyaya yaz
  					  myfile << *this << '\n';
				}
		}
		else
			throw type;	
		myfile.close();	
		

}

BookCatalog::BookCatalog() : Catalog(), authors(""), tags("")
{ } 
	
string BookCatalog::getAuthors() const {
	return (authors);
}

string BookCatalog::getTags() const {
	return (tags);
}

void BookCatalog::setAuthors(const string& newAuthors) {
	authors = newAuthors;
}

void BookCatalog::setTags(const string& newTags) {
	tags = newTags;
}

void BookCatalog::setDataFields(const vector<string>& elements) {
	if (elements.size() != 4)
		throw title;
	//eğer size ideal değilse exception fırlat(ben string fırlatıyorum string yakalyıorum sonra
	title = elements[0];
	authors = elements[1];
	year = elements[2];
	tags = elements[3];
}

ostream& operator<<(ostream& out, const BookCatalog& obj){
    out << '"' << obj.title << "\" \"" << obj.authors <<  "\" \"" 
        << obj.year << "\" \"" << obj.tags<< '"';//dosyaya yazdırma formatı
    return out;
}
