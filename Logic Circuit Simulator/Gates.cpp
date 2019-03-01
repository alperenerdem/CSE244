#include "Gates.h"
Gates::Gates(int number){
size=number;
}
Gates::~Gates(){
	delete[] label;
	delete[] inputlabels;
	delete[] values;
	delete[] inputvalues;

}
FLIPFLOP::FLIPFLOP(string labels){
	 int cursor=0,pos=0,i=0;
	 inputsize=2;//2 input var, formerout ve normal inpu
	 label= new string[1];//tek çıktı için isim
	 values= new int[1];//tek çıktı
	 inputlabels=new string[inputsize];//inputlar için isim ve value 
	 inputvalues=new int[inputsize];
	 inputvalues[1]=0;//ilk formeroutumuz 0
	 pos = labels.find(' ',cursor);//ismini almam gereken yeri buluyorum
	 label[0]=labels.substr(cursor,pos-cursor);//ismini alıyorum labelsin
	 values[0]=3;//ilk değere 3 veriyorum algroitmam için
	 cursor=pos+1;//cursoru arttırıp inputun adını alyıorum
	 pos = labels.find(' ',cursor);
	 inputlabels[i]=labels.substr(cursor,labels.size()-cursor);
	 size=1;
}

//tüm constructlarda aynı şeyi yaptığım için burda daha net açıklama gereği hissetim
//Substr ve find ile boşluklar aracılığı ile ilk önce output labelini alıp değerine 3 veriyorum(3 ise çözülmemiş demek)
//daha sonra input labels isimleirni alyıruom valuelerine birşey atmıyorum, daha sonra çözerken bakıcam
//Decoder için 4,input ve output için ise size ne kadarsa o kadar outputlabeli için yer alıyorum
NOT::NOT(string labels){
	 int cursor=0,pos=0,i=0;
	 inputsize=1;
	 label= new string[1];
	 values= new int[1];
	 inputlabels=new string[inputsize];
	 inputvalues=new int[inputsize];
	 pos = labels.find(' ',cursor);
	 label[0]=labels.substr(cursor,pos-cursor);
	 values[0]=3;
	 cursor=pos+1;
	 pos = labels.find(' ',cursor);
	 inputlabels[i]=labels.substr(cursor,labels.size()-cursor);
	size=1;
}
OUTPUT::OUTPUT(int number,string labels):Gates(number){
	int cursor=0,pos=0,i=0; 
	type="OUTPUT";
		 values= new int[size];
		 label= new string[size];
		 while(1){
			pos = labels.find(' ',cursor);
			if(pos<0)
				break;
			label[i]=labels.substr(cursor,pos-cursor);
	
			i++;
			cursor=pos+1;
		}
			label[i]=labels.substr(cursor,labels.size()-cursor);
}
DECODER::DECODER(string labels){
	 
	 int cursor=0,pos=0,i=0,j=0;
	 inputsize=2;
	 size=4;
	 label= new string[size];
	 values= new int[size];
	 while(j<size){
	 		 pos = labels.find(' ',cursor);
			 label[j]=labels.substr(cursor,pos-cursor);
			 values[j]=3;
	 		cursor=pos+1;
			j++;
			
		}

	 inputlabels=new string[inputsize];
	 inputvalues=new int[inputsize];
	  
	 while(1){
			pos = labels.find(' ',cursor);
			if(pos<0)
				break;
			inputlabels[i]=labels.substr(cursor,pos-cursor);
			i++;
			cursor=pos+1;
			
		}
			inputlabels[i]=labels.substr(cursor,labels.size()-cursor);
}
AND::AND(string labels){
	 
	 int cursor=0,pos=0,i=0;
	 inputsize=2;
	 label= new string[1];
	 values= new int[1];
	 inputlabels=new string[inputsize];
	 inputvalues=new int[inputsize];
	 pos = labels.find(' ',cursor);
	 label[0]=labels.substr(cursor,pos-cursor);
	 values[0]=3;
	 cursor=pos+1;
	 while(1){
			pos = labels.find(' ',cursor);
			if(pos<0)
				break;
			inputlabels[i]=labels.substr(cursor,pos-cursor);
			i++;
			cursor=pos+1;
			
		}
			inputlabels[i]=labels.substr(cursor,labels.size()-cursor);

	size=1;
}
OR::OR(string labels){
	 int cursor=0,pos=0,i=0;
	 inputsize=2;
	 label= new string[1];
	 values= new int[1];
	 inputlabels=new string[inputsize];
	 inputvalues=new int[inputsize];
	 pos = labels.find(' ',cursor);
	 label[0]=labels.substr(cursor,pos-cursor);
	 values[0]=3;
	 cursor=pos+1;
	 while(1){
			pos = labels.find(' ',cursor);
			if(pos<0)
				break;
			inputlabels[i]=labels.substr(cursor,pos-cursor);
			i++;
			cursor=pos+1;
			
		}
			inputlabels[i]=labels.substr(cursor,labels.size()-cursor);
	size=1;
}

//initInOutlarda çıktı değerlerini hesaplıyorum, girdi değerleri belliyse bunu circuit.cpp içindeki circuitsolverde çağrıyordum.
//hesaplamaları logic eşitlikler ile yaptım && ve || ve değil operatörleriyle
void DECODER::initInOut(int target,int value){

values[3]=(inputvalues[0]&&(inputvalues[1]));
values[2]=(inputvalues[0]&&!(inputvalues[1]));
values[1]=(!(inputvalues[0])&&(inputvalues[1]));
values[0]=(!(inputvalues[0])&&!(inputvalues[1]));
}
void FLIPFLOP::initInOut(int target,int value){
	values[0]=(inputvalues[0]&&!(inputvalues[1]))||(!(inputvalues[0])&&inputvalues[1]);
	inputvalues[1]=values[0];//değeri sonraki kullanım için formeroutu tuttuğum 2.elemana atıyorum
}
void NOT::initInOut(int target,int value){
	values[0]=!(inputvalues[0]);
}
void AND::initInOut(int target,int value){
	values[0]=inputvalues[0]&&inputvalues[1];
}
void OR::initInOut(int target,int value){
	values[0]=inputvalues[0]||inputvalues[1];
}
//resetlerken tüm outputlara 3 atıyorum

void DECODER::reset(){
	values[0]=3;
	values[1]=3;
	values[2]=3;
	values[3]=3;
}
void FLIPFLOP::reset(){
	values[0]=3;
}
void NOT::reset(){
	values[0]=3;
}
void AND::reset(){
	values[0]=3;
}
void OR::reset(){
	values[0]=3;
}


void OUTPUT::initInOut(int target,int value){
//def
}

void INPUT::initInOut(int target,int value){
//gönderilen yere inputun değerini yazıyorum
values[target]=value;

}
INPUT::INPUT(int number,string labels):Gates(number){//input labellerini alıyorum
	int cursor=0,pos=0,i=0; 
	string s;//labels
	type="INPUT";
		 values= new int[size];
		 label= new string[size];
		 while(1){
			pos = labels.find(' ',cursor);
			if(pos<0)
				break;
			label[i]=labels.substr(cursor,pos-cursor);

			i++;
			cursor=pos+1;
		}
			label[i]=labels.substr(cursor,labels.size()-cursor);
}
