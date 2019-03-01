#include "MovieCatalog.h"
#include "Catalog.h"
using namespace std;
void MovieCatalog::search(const string type,const string target) const{
	ofstream myfile;
 	 myfile.open ("output.txt",ofstream::app);// dosyaya üzerine yazmamak için devamına eklemek için böyle açmamız gerekiyormuş
		if(type=="title"){// string içinde varsa dosyaya yaz
				if (title.find(target) != std::string::npos)
  					  myfile << *this << '\n';
		}
		else if(type=="year"){// string içinde varsa dosyaya yaz
				if (year.find(target) != std::string::npos)
  					  myfile << *this << '\n';
		}
		else if(type=="director"){// string içinde varsa dosyaya yaz
				if (director.find(target) != std::string::npos)
  					  myfile << *this << '\n';

		}
		else if(type=="genre"){// string içinde varsa dosyaya yaz
				if (genre.find(target) != std::string::npos)
  					  myfile << *this << '\n';
		}
		else if(type=="starring"){// string içinde varsa dosyaya yaz
				if (starring.find(target) != std::string::npos)
  					  myfile<< *this << '\n';
		}
		else
			throw type;	
		myfile.close();	
}

MovieCatalog::MovieCatalog() : Catalog(), 
				           director(""), starring(""), genre("")
{ }

string MovieCatalog::getDirector() const {
	return (director);
}

string MovieCatalog::getStarring() const {
	return (starring);
}

string MovieCatalog::getGenre() const {
	return (genre);
}

void MovieCatalog::setDirector(const string& newDirector) {
	director = newDirector;
}

void MovieCatalog::setStarring(const string& newStarring) {
	starring = newStarring;
}

void MovieCatalog::setGenre(const string& newGenre) {
	genre = newGenre;
}

void MovieCatalog::setDataFields(const vector<string>& elements) {
	if (elements.size() != 5)
		throw title;
	//eğer size ideal değilse exception fırlat(ben string fırlatıyorum string yakalyıorum sonra
	title = elements[0];
	director = elements[1];
	year = elements[2];
	genre = elements[3];
	starring = elements[4];
}
ostream& operator<<(ostream& out, const MovieCatalog& obj){
    out << '"' << obj.title << "\" \"" << obj.director <<  "\" \"" 
        << obj.year << "\" \"" << obj.genre<< "\" \"" << obj.starring << '"';//dosyaya yazdırma formatı
    return out;
}
