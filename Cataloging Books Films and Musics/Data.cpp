#include "Data.h"
#include "Catalog.h"
#include "BookCatalog.h"
#include "MovieCatalog.h"
#include "MusicCatalog.h"
using namespace std;

Data::Data(string filename,string commandFileName){
	ifstream cinFromFile(filename);//Okumak için açtığım dosya
	getline(cinFromFile, type);//ana objedeki tipe çekiyorum
	ofstream myfile;//output için
	myfile.open ("output.txt");//ilk defa açtığım yer, diğer fonksiyonlarda devamına yazdığım için"myfile.open ("output.txt",ofstream::app);" şeklinde açıcam
	myfile<<"Catalog Read: "<<type<<endl;
	readDataFromTheFile(cinFromFile);//okuduğumz dosyayı dataları yeirne koymak için buraya gönderiyorum
	commandsTaker(commandFileName,type);//komut dosyasısını burda açmaya gerek yok
	cinFromFile.close();
	myfile.close();
}


void Data::readDataFromTheFile(ifstream& cinFromFile){
	int pos,pos2,cursor=0;// tırnak (") işaretine göre bölme string::substr ve string::find'te kullanacağım değişkenler
	string line;
	vector<string> element;//elementlere sırasıyla istenilen değişkenler için stringler gelecek, mesela title,year,genre..
	ofstream myfile;
 	myfile.open ("output.txt",ofstream::app);//devamına eklemek için böyle açıyorum
	while(getline(cinFromFile, line)){//alabildiği kadar satır
		element.clear();//elementi önceki işlemlerde doluysa boşaltıyorum
		while(1){
			pos = line.find('"',cursor);//2 adet tırnak arasında olcağı için pos2'de var burada, arasındakileri bölerek alıyorum
			if(pos<0)
				break;
			cursor=pos+1;
			pos2=line.find('"',cursor);
			cursor=pos2+1;
			element.push_back(line.substr(pos+1,(pos2-pos)-1));
		}
		try{//Size az ise içindenden string throw ediliyor, eğer title containerimizde daha önce bulunduysa,5(int) throwluyor (iterator yardımıyla gezerek kontrol ediyorum)
			if (type == "book") {
				for (auto iter = catalogs.begin(); iter != catalogs.end(); ++iter){ 	
					if (element[0] == (*iter)->getTitle())
						throw 5;
				}		
				BookCatalog *var = new BookCatalog();//vectörün sonuna eklemek için yeni bir dynamic class oluşturuyorum
				var->setDataFields(element);//clasın elemanlarına burda böldüğümüz satırın elamanlarını koyuyuorum
				catalogs.push_back(var);//hala exception throwlanmadıysa, vectöre ekliyorum classı
				
				//altta aynı şeyleri diğer türler için ypaıyorum
			
			} else if (type == "music") {
				for (auto iter = catalogs.begin(); iter != catalogs.end(); ++iter) {	
					if (element[0] == (*iter)->getTitle())
						throw 5;
				}		
				MusicCatalog *var = new MusicCatalog();
				var->setDataFields(element);
				catalogs.push_back(var);
				
			} else if (type == "movie") {
				for (auto iter = catalogs.begin(); iter != catalogs.end(); ++iter){ 	
					if (element[0] == (*iter)->getTitle())
						throw 5;
				}		
				MovieCatalog *var = new MovieCatalog();
				var->setDataFields(element);		
			
				catalogs.push_back(var);
			}	
		}
		catch(const string ErrorTypes){//string yakalarsa missing field exceptionu
					myfile << "Exception: missing field \n"<<line<<endl;
		}
		catch(int error){//int yakalarsa dublicate exceptionu
					myfile << "Exception: Dublicate entry \n"<<line<<endl;
		}
		cursor=0;	
	}
	myfile << catalogs.size()<<" unique entries"<<endl;//kaçtane hatasız satır varsa onları dosyaya yaz
	myfile.close();
}


void Data::commandsTaker(string filename,string type){
	int pos,pos2,cursor=0;// boşluk ( ) işaretine göre bölme string::substr ve string::find'te kullanacağım değişkenler
	string line,kommand,area,target;//line satırımız, kommand komutumuz, area nerede veya nereye göre yapılacağı, targette search'te aramamız istenen değişken olucak
	vector<string> command;//command line'ları buraya alıyorum
	ifstream cinFromFile(filename);//komut dosyayısını açıyorum
	 ofstream myfile;
 	 myfile.open ("output.txt",ofstream::app);//devamına ekleyeceğim için bu formatta açıyorum

	while(getline(cinFromFile, line)){//line alana kadar
		myfile<<line<<endl;//dosyaya komut satırını yazdıryıroum
		pos = line.find(' ',cursor);
		kommand=line.substr(cursor,pos-cursor);//komut satırını boşluklara göre bölüyorum
		cursor=pos+1;
		while(1){
			pos = line.find(' ',cursor);//pos sağında bulamadığında eksi döndürüyor o yüzden eksi dönünce son kelimeyi alıyor
			if(pos<0){
				area=line.substr(cursor+1,(line.size()-cursor)-2);//son kelime daima area oluyor
				break;	
			}	
			if(line.substr(cursor,pos-cursor)!="in"&&kommand=="search")//in değilken ve search'ken targete eleman alıyorum
				target=line.substr(cursor+1,(pos-cursor)-2);
			cursor=pos+1;
		}	
		cursor=0;
		try{//searchde aranan area uygun değilse exception fırlatılıyor, onun için try catch bloğu
			if(kommand=="search"){
				if(type=="book"){//teker teker containerdeki tüm elemanlara bakıp içlerindeki search fonksiyonuyla arama yapıyor, bulduysa orada yazdırıyor dosyaya
								 //iterator yardımıyla
						for (auto iter = catalogs.begin(); iter != catalogs.end(); ++iter) 
							(*iter)->search(area,target);
				}
				else if(type=="movie"){
						for (auto iter = catalogs.begin(); iter != catalogs.end(); ++iter) 
							(*iter)->search(area,target);	
				}
				else if(type=="music"){
						for (auto iter = catalogs.begin(); iter != catalogs.end(); ++iter) 
							(*iter)->search(area,target);
				}
		 	} 
		 	else if(kommand=="sort"){ 
		 		if (type == "movie") {
						if(area=="year"){//Sortu internette hazır sort kullanmak için konuma uygun aramalar yaparak buldum ve koduma uygun hale getirdim.
							sort(catalogs.begin(), catalogs.end(), [](Catalog *c1, Catalog *c2) {
								return dynamic_cast<MovieCatalog *>(c1)->getYear() < dynamic_cast<MovieCatalog *>(c2)->getYear();
							});
						}
						else if(area=="title"){	 		
							sort(catalogs.begin(), catalogs.end(), [](Catalog *c1, Catalog *c2) {
								return dynamic_cast<MovieCatalog *>(c1)->getTitle() < dynamic_cast<MovieCatalog *>(c2)->getTitle();
							});
						}
						else if(area=="director"){	 		
							sort(catalogs.begin(), catalogs.end(), [](Catalog *c1, Catalog *c2) {
								return dynamic_cast<MovieCatalog *>(c1)->getDirector() < dynamic_cast<MovieCatalog *>(c2)->getDirector();
							});
						}
						else if(area=="starring"){	 		
							sort(catalogs.begin(), catalogs.end(), [](Catalog *c1, Catalog *c2) {
								return dynamic_cast<MovieCatalog *>(c1)->getStarring() < dynamic_cast<MovieCatalog *>(c2)->getStarring();
							});
						}
						else if(area=="genre"){	 		
							sort(catalogs.begin(), catalogs.end(), [](Catalog *c1, Catalog *c2) {
								return dynamic_cast<MovieCatalog *>(c1)->getGenre() < dynamic_cast<MovieCatalog *>(c2)->getGenre();
							});
						}
					for (int i = 0; i < catalogs.size(); ++i)//sorttan sonra yazdırıyorum, ve alttada türüne göre devamlı aynı şeyler yapılıyor
		 				myfile << *dynamic_cast<MovieCatalog *>(catalogs[i]) << endl; //burada iteratör kullanınca adresini yazdırıyordu çözemediğim için böyle gönderdim
					}		
				else if (type == "book") {
						if(area=="year"){	 		
							sort(catalogs.begin(), catalogs.end(), [](Catalog *c1, Catalog *c2) {
								return dynamic_cast<BookCatalog *>(c1)->getYear() < dynamic_cast<BookCatalog *>(c2)->getYear();
							});
						}
						else if(area=="title"){	 		
							sort(catalogs.begin(), catalogs.end(), [](Catalog *c1, Catalog *c2) {
								return dynamic_cast<BookCatalog *>(c1)->getTitle() < dynamic_cast<BookCatalog *>(c2)->getTitle();
							});
						}
						else if(area=="director"){	 		
							sort(catalogs.begin(), catalogs.end(), [](Catalog *c1, Catalog *c2) {
								return dynamic_cast<BookCatalog *>(c1)->getAuthors() < dynamic_cast<BookCatalog *>(c2)->getAuthors();
							});
						}
						else if(area=="starring"){	 		
							sort(catalogs.begin(), catalogs.end(), [](Catalog *c1, Catalog *c2) {
								return dynamic_cast<BookCatalog *>(c1)->getTags() < dynamic_cast<BookCatalog *>(c2)->getTags();
							});
						}
					for (int i = 0; i < catalogs.size(); ++i)
		 				myfile << *dynamic_cast<BookCatalog *>(catalogs[i]) << endl;	
					}
				else if (type == "music") {
						if(area=="year"){	 		
							sort(catalogs.begin(), catalogs.end(), [](Catalog *c1, Catalog *c2) {
								return dynamic_cast<MusicCatalog *>(c1)->getYear() < dynamic_cast<MusicCatalog *>(c2)->getYear();
							});
						}
						else if(area=="title"){	 		
							sort(catalogs.begin(), catalogs.end(), [](Catalog *c1, Catalog *c2) {
								return dynamic_cast<MusicCatalog *>(c1)->getTitle() < dynamic_cast<MusicCatalog *>(c2)->getTitle();
							});
						}
						else if(area=="artists"){	 		
							sort(catalogs.begin(), catalogs.end(), [](Catalog *c1, Catalog *c2) {
								return dynamic_cast<MusicCatalog *>(c1)->getArtists() < dynamic_cast<MusicCatalog *>(c2)->getArtists();
							});
						}
						else if(area=="genre"){	 		
							sort(catalogs.begin(), catalogs.end(), [](Catalog *c1, Catalog *c2) {
								return dynamic_cast<MusicCatalog *>(c1)->getGenre() < dynamic_cast<MusicCatalog *>(c2)->getGenre();
							});
						}	
					for (int i = 0; i < catalogs.size(); ++i)
		 				myfile << *dynamic_cast<MusicCatalog *>(catalogs[i]) << endl;
					}
						
		 	} 
		 }
	 	catch(string ErrorTypes){//eğer aranan area/type yanlışsa onu catchliyip dosyaya yazyıor
					myfile << "Exception: command is wrong-> " << ErrorTypes << '\n';
		}
	 	target.clear();	
	}
	myfile.close();
}


Data::~Data(){
	for (auto iter = catalogs.begin(); iter != catalogs.end(); ++iter)
		delete *iter;
}
