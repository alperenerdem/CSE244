#include "MusicCatalog.h"
using namespace std;
void MusicCatalog::search(const string type,const string target) const{
		ofstream myfile;
 		 myfile.open ("output.txt",ofstream::app);// dosyaya üzerine yazmamak için devamına eklemek için böyle açmamız gerekiyormuş
		
		if(type=="title"){// string içinde varsa dosyaya yaz
				if (title.find(target) != std::string::npos) {
  					  myfile << *this << '\n';
				}
		}
		else if(type=="year"){// string içinde varsa dosyaya yaz
				if (year.find(target) != std::string::npos) {
  					  myfile << *this << '\n';
				}
		}
		else if(type=="artists"){// string içinde varsa dosyaya yaz
				if (artists.find(target) != std::string::npos) {
  					  myfile << *this << '\n';
				}
		}
		else if(type=="genre"){// string içinde varsa dosyaya yaz
				if (genre.find(target) != std::string::npos) {
  					  myfile << *this << '\n';
				}
		}
		else
			throw type;	
		myfile.close();	

}

MusicCatalog::MusicCatalog() 
			: Catalog(), artists(""), genre("")
{ }

string MusicCatalog::getArtists() const {
	return (artists);
}

string MusicCatalog::getGenre() const {
	return (genre);
}

void MusicCatalog::setArtists(const string& newArtists) {
	artists = newArtists;
}

void MusicCatalog::setGenre(const string& newGenre) {
	genre = newGenre;
}

void MusicCatalog::setDataFields(const vector<string>& elements) {
	if (elements.size() != 4)
		throw title;
	//eğer size ideal değilse exception fırlat(ben string fırlatıyorum string yakalyıorum sonra
	title = elements[0];
	artists = elements[1];
	year = elements[2];
	genre = elements[3];
}


ostream& operator<<(ostream& out, const MusicCatalog& obj){
    out << '"' << obj.title << "\" \"" << obj.artists <<  "\" \"" 
        << obj.year << "\" \"" << obj.genre<< '"';//dosyaya yazdırma formatı
    return out;
}
