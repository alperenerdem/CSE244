#ifndef CIRCUIT_H
#define CIRCUIT_H
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
class Gates;

class Circuit
{
	public:
		Circuit(){
			//cout<<"default";
		}
		Circuit(string filename);//devreyi açıp kuruyor
		~Circuit();
		void solve(string name){solver(name);}//çözüyücü dışarıdan çağırmak için bir getter
	private:
		void gateAdder(string gatename,string labels,int target);//gate ekleyici
		void findinputs(string inputs);//inputları devreye gönderici
		void showOutputs();//outputgösterici
		void resetGates();//gate sıfırlayıcı
		int gateCounter(string filename);//gatelene dönen değer
		Gates ** data;//ÖNEMLİ DATAMIZ
		int gateLen;//gate sayısı
		void solver(string name);//çözücü
	   
};

#endif
