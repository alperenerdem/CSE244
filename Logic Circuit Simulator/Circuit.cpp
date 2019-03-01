#include "Circuit.h"
#include "Gates.h"
Circuit::~Circuit(){
	int i=0;
	while(i<gateLen){
		if(data[i]!=NULL){
			delete data[i];
		}	
		i++;
	}		
		delete[] data;
}
void Circuit::findinputs(string inputs){//INPUT classındaki labellere input değerlerini alıyor
	int i=0,j=0,cursor=0,pos=0;
	while(i<gateLen){
		if(data[i]->type=="INPUT"){
			 while(1){
				pos = inputs.find(' ',cursor);
				if(pos<0)
					break;
				data[i]->initInOut(j,stoi(inputs.substr(cursor,pos-cursor)));
				cursor=pos+1;
				j++;
			}
				data[i]->initInOut(j,stoi(inputs.substr(cursor,pos-cursor)));
		}
		i++;	
	}
}
void Circuit::resetGates(){//INPUT VE OUTPUT hariç tüm gatesleri sonraki inputlar için resetliyor(algoritmam için)
int i=0,j=0;
	while(i<gateLen){
		if(data[i]->type!="OUTPUT"&&data[i]->type!="INPUT"){
		  	data[i]->reset();
		}
		i++; 
	}


}
void Circuit::solver(string name){
	int i=0,j=0,k=0,l=0,cursor=0,pos=0,flag,bigflag;
	//i ve j ile k ve l gates arrayinde input labellerini araştırdığım sayaçlar,i ve k gates sayaçları
	//j ve l ise gateler içindeki küçük arraylerdeki sayaçlar
	
	//Mesela and1 a and2 diye bir gate'de durdum i sayacıyla
	//a labeldeki bir değişkeni baştan tüm gatelerin output arrayinde, bulursa değerini gate[i]deki ilk input değerine atıyor 
	//and2'ye bakıyor label arrayinde değeri yoksa değeri 3'tür, 3 ise flagı 1liyor çünkü şuan bildiklerimle bu devreyi çözemem,
	//and2'nin değeri daha sonra gelecek demekki
	//flag 0 kaldıysa devreyi çözüp devrenin ordaki outputuna 0 veriyor.
	
	//big flag ise tüm devreye baktığımda 3(yani çözülmemiş) değer varsa 1 oluyor, devreye baktığımda bigflag 0'sa  tekrardan bakmaya gerek yok
	// tüm değerler çözülmüş demektir.
	
	ifstream cinfromfile;
	cinfromfile.open(name);
	string s;
	while(getline(cinfromfile, s)){//ilk önce inputları alıyorum, ne kadar satır varsam devreyi o kadar çözücem
		findinputs(s);
		i=0;//devre sayacımı sıfırlıyorum(gates* arrayi sayacı)
		while(i<gateLen){//gateLen kadar bakıyorum
			if(data[i]->type!="OUTPUT"&&data[i]->type!="INPUT"){//OUTPUT ve INPUT gateleri hariç bakıyorum
				flag=0;	//flagı her küçük devre için baktığım için sıfırlıyorum
				while(j<(data[i]->inputsizeReturner())){//j o datadaki inputsizelarından küçükse(and or için 2, not flipflop için 1)

						while(k<gateLen){//şimdi o gatedeki inputlabellerin,başka gatelerin outputlabellerinde araştıracağım
							while(data[k]->type!="OUTPUT"&&l<(data[k]->sizeReturner())){//OUTPUT değilse bakıyorum,çünkü orda değeri çözümlenmiş değil
								if(data[i]->inputlabels[j]==data[k]->label[l]){//Eğer gates*[i]deki j indexindeki inputlabelim, herhangi bir gate'nin outputuysa

									if(data[k]->values[l]<2){//ve değeri varsa(yani 3 değilse)
										data[i]->inputvalues[j]=data[k]->values[l];//değerini alıyorum

									}
									else{//değeri yoksa devrem tamamlanmamış, iki flagide birliyorum
										flag=1;
										bigflag=1;
									}	
								
								
								}
								l++;
							}
							l=0;
							k++;	
						}
					k=0;	
					j++;
				}
				if(flag==0){//değerler geldiyse o devreyi çözüyorum
					data[i]->initInOut(0,0);
				}		
			}
			j=0;
			i++;
			if(bigflag==1&&i==gateLen){// herhangi bir yerde çözümlenmemiş değerim varsa ve bakmam bittiyse tekrar bakmak için
									   // i'yi sıfırlıyorum,bigflag'ide tekrar bakacağım için 0 lıyorum
				bigflag=0;
				i=0;	
			}
		}
		showOutputs(); //ilk inputlar için devre bitti, outputu görmek için fonksiyonu çağrıyorum
		resetGates(); // Gateleri tekrar 0lamak için çağrıyorum(çünkü 3 değilse bakan bir kod var, eski değerler ile çözecek eğer resetlemezsem)
	}

}

void Circuit::showOutputs(){//OUTPUTta gelen değerleri, diğer gatelerin outputunda buluyor ve değerlerini ekrana basıyor
	int i=0,j=0,k=0,l=0;
	while(i<gateLen){
		if(data[i]->type=="OUTPUT"){//ilk önce OUTPUT gatelerini buluyor
		   while(j<(data[i]->sizeReturner())){
			   while(k<gateLen){
			   		while(data[k]->type!="OUTPUT"&&l<(data[k]->sizeReturner())){
			   			if(data[k]->label[l]==data[i]->label[j]){
			   				cout<<data[k]->values[l]<<' ';
			   			}	
			   			l++;
			   		}
			   	 l=0;	
			   	 k++;				   
			   }
			 k=0;
			 j++;
		  } 
		}	
		j=0;
		i++;  
	}
	cout<<endl;//diğer input sırası için yeni satır
	
}
Circuit::Circuit(string filename){//INPUT ve OUTPUT için içeride dynamic yer alıyorum, çünkü kaç label olduğu önemli
								 
	gateLen=gateCounter(filename);//kaç gate var onu buluyorum
	string s,labels,gatename;//labels GAte isminden sonra gelenleri tutucak
	int i=0,j=0,pos,cursor=0;//cursor, stringde içinde bölme yapmaya başlayacağım yer, pos ise bölmeyi yapacağım target
							 // yani from cursor to pos bölmesi yapacağım
	data=new Gates*[gateLen];//satır sayısı kadar gates*lik yer alıyorum
	ifstream cinfromfile;
	cinfromfile.open(filename);//dosyayı açıyorum
	
	while(getline(cinfromfile, s)){//dosyadan satır alana kadar devam ediyor
		pos = s.find(' ',cursor);//ilk boşluk nerde buldum
		if(s.substr(cursor,pos-cursor)=="INPUT"){//ilk boşluğa kadar inputsa
			cursor=pos+1;
			labels=s.substr(cursor,s.size()-cursor);			
			while(1){
				pos = s.find(' ',cursor);//kaç tane boşluk olduğunu sayıyorum,1 fazlası label sayısı
				if(pos<0)
					break;
				cursor=pos+1;
				i++;
			}
			data[j]=new INPUT(i+1,labels);//labels arrayini , kaçtane input girildiğiyle beraber yeni bir INPUT constructuruna gönderiyorum
			j++;
			labels.clear();//labelsde junk kalmasın
		}
		else if(s.substr(cursor,pos-cursor)=="OUTPUT"){//ilk boşluğa kadar outputsa
			cursor=pos+1;
			labels=s.substr(cursor,s.size()-cursor);				
			while(1){
				pos = s.find(' ',cursor);//kaç tane boşluk olduğunu sayıyorum,1 fazlası label sayısı
				if(pos<0)
					break;
				cursor=pos+1;
				i++;
			}
			data[j]=new OUTPUT(i+1,labels);//labels arrayini , kaçtane output istendiğiyle beraber yeni bir OUTPUT constructuruna gönderiyorum
			j++;
			labels.clear();//labelsde junk kalmasın
		}
		else{//başka bir gate ise
			gatename=s.substr(cursor,pos-cursor);//ismini tutuyorum

			cursor=pos+1;
			labels=s.substr(cursor,s.size()-cursor);//geri kalanları labelde alıyorum
		
			gateAdder(gatename,labels,j);//gate addera gönderiyorum
			j++;
			labels.clear();//labelsde junk kalmasın
			
		}
		i=0;
		cursor=0;
	}

}
void Circuit::gateAdder(string gatename,string labels,int target){/*Input ve output hariç gateleri gates* arrayine ekliyor */
	int cursor=0,pos=0,j=0;
	if(gatename=="AND"){
		data[target]=new AND(labels);	
		
	}
	else if(gatename=="OR"){
		data[target]=new OR(labels);
	}	
	else if(gatename=="NOT"){
		data[target]=new NOT(labels);
	}	
	else if(gatename=="FLIPFLOP"){
		data[target]=new FLIPFLOP(labels);
	}
	else if(gatename=="DECODER"){
		data[target]=new DECODER(labels);
	}


}

int Circuit::gateCounter(string filename){/*ilk önce dosyada kaç satır var sayıyor */
	int lenght=0;
	ifstream cinfromfile;
	cinfromfile.open(filename);
	string s;
	while(getline(cinfromfile, s)){
		lenght++;
	}
	return lenght;



}
