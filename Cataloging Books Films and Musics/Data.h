#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "BookCatalog.h"
#include "MovieCatalog.h"
#include "MusicCatalog.h"

using namespace std;

class Data {
public:
	Data(string filename,string commandFileName);//data'yı aldığmız txt ve commandları açtığımız txt ile construcctor
	virtual ~Data();
private:
	void readDataFromTheFile(ifstream& cinFromFile);//data alıcı
	void commandsTaker(string filename,string type);//komut uygulayıcı
	vector<Catalog *> catalogs;//catalog türlerini tuttuğum contanier
	string type;//Tür tipi movie book music
};

#endif
