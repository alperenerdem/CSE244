
#include "SparseVector.h"
//dot function class içinde belirtilmiş gibi pdfte, kullanılırken de class dışı kullanılmış, emin olamadığım için ilk halini yolladım, yani class içinden erişmek gerekiyor v1.dot(v1,v2) gibi

double SparseVector::dot(const SparseVector &v1,const SparseVector &v2){
	double total=0;
	int a=0,b=0;
	//0 olanları çarpmaya gerek olmadığı için ikisininde eşit olduğu yerleri çarparak
	//totale ekledim. 0 olanlar yerlerde sadece arttırdım
	while(a<v1.SparVec.size()||b<v2.SparVec.size()){
		if(a==v1.SparVec.size()||(a<v1.SparVec.size()&&v1.SparVecData[a]<v2.SparVecData[b])){
			a++;
		}
		else if(a==v1.SparVec.size()||v1.SparVecData[a]>v2.SparVecData[b]){
			b++;
		}
		
		else if(v1.SparVecData[a]==v2.SparVecData[b]){
			total=total+(v1.SparVec[a]*v2.SparVec[b]);
			 a++;b++;				
		}
	}
	return total;
}
SparseVector& SparseVector::operator=(const SparseVector &v1){
 int a=0;
 	//ilk önce tüm değerleri pop_backledim sonra üstüne v1dekileri atadım
	while(this->SparVec.size()>0){
		this->SparVec.pop_back();
		this->SparVecData.pop_back();
	 }
 	while(v1.SparVec.size()>a){
		this->SparVec.push_back(v1.SparVec[a]);
		this->SparVecData.push_back(v1.SparVecData[a]);
		a++;
	 }
}
std::ostream & operator <<(std::ostream & output, SparseVector const& v1){
	int a=0;
	//size kadar outputa sırayla indis ve sayıları atadım
	while(a<v1.SparVec.size()){
		output<<v1.SparVecData[a]<<':'<<v1.SparVec[a]<<' ';
		a++;
	}
	return output;
}

SparseVector operator+(const SparseVector &v1, const SparseVector &v2){
	int a=0,b=0;
	SparseVector ResVec;
	
	while(a<v1.SparVec.size()||b<v2.SparVec.size()){
		//v1'in tüm elemanlarına ulaşıldığı ve a'nın indisinn b'den küçük olduğu yerlerde direk a'yı atadım sonuca
		if(b==v2.SparVec.size()||(a<v1.SparVec.size()&&v1.SparVecData[a]<v2.SparVecData[b])){
			ResVec.SparVec.push_back(v1.SparVec[a]);
			ResVec.SparVecData.push_back(v1.SparVecData[a]);
			a++;
		}
		//v2'in tüm elemanlarına ulaşıldığı ve b'nin indisinn a'dan küçük olduğu yerlerde ise b'yi sonuca atadım.
		else if(a==v1.SparVec.size()||v1.SparVecData[a]>v2.SparVecData[b]){
			ResVec.SparVec.push_back(v2.SparVec[b]);
			ResVec.SparVecData.push_back(v2.SparVecData[b]);
			b++;

		}
		//indisleirn eşit olduğu durumlarda topladım
		else if(v1.SparVecData[a]==v2.SparVecData[b]){
			ResVec.SparVec.push_back(v1.SparVec[a]+v2.SparVec[b]);
			ResVec.SparVecData.push_back(v1.SparVecData[a]);
			a++;b++;
		}
	}
	return ResVec;
}
SparseVector operator-(const SparseVector &v1, const SparseVector &v2){
	int a=0,b=0;
	SparseVector ResVec;
	//+'ın aynısı, sadece v2de olup,ilk vectörün o indisinde değer bulunmadığı durumlarda v2'Nin eksilisini atadım
	while(a<v1.SparVec.size()||b<v2.SparVec.size()){
		if(a<v1.SparVec.size()&&v1.SparVecData[a]<v2.SparVecData[b]){
			ResVec.SparVec.push_back(v1.SparVec[a]);
			ResVec.SparVecData.push_back(v1.SparVecData[a]);
			a++;
		}
		else if(a==v1.SparVec.size()||v1.SparVecData[a]>v2.SparVecData[b]){
			ResVec.SparVec.push_back(0-v2.SparVec[b]);
			ResVec.SparVecData.push_back(v2.SparVecData[b]);
			b++;

		}
		else if(v1.SparVecData[a]==v2.SparVecData[b]){
			ResVec.SparVec.push_back(v1.SparVec[a]-v2.SparVec[b]);
			ResVec.SparVecData.push_back(v1.SparVecData[a]);
			a++;b++;
		}
	}
	return ResVec;
}
SparseVector operator-(const SparseVector &v1){
	int a=0;
	SparseVector ResVec;
	//sırayla tüm değerleri 0dan çıkardım
		while(a<v1.SparVec.size()){
			ResVec.SparVec.push_back(0-v1.SparVec[a]);
			ResVec.SparVecData.push_back(v1.SparVecData[a]);
			a++;
		}
	return ResVec;	
	
}

SparseVector::SparseVector(){
//default
}

SparseVector::SparseVector(const char *filename){

	ifstream cinfromfile;
	cinfromfile.open(filename);
	int a;
	double b;
	char c;
	while(1){
	//pdfteki gibi aldım, dosya sonunda döngüden çıkıyor
		cinfromfile>>a>>c>>b;
		if(cinfromfile.eof()){
			break;
		}
		SparVecData.push_back(a);
		SparVec.push_back(b);
		if(cinfromfile.eof()){
			break;
		}
	}
}

