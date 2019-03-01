#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;
typedef struct object_s {
	float cost;
	char name[100];
} object;//cost artarak devam edeceği için structa tanımladım.


int isNumber(char temp[100]);//stringin numerikliğine bakan fonksiyon
int isNumberchar(char temp);//character'in sayı olup olmadığını kontrol eden fonksiyon
void parser(char temp[100],object& objectx,int piece);//stringi parçayalan fonksiyon

int main()
{
	char temp[100];
	object nesne;
	nesne.cost=0;// ilk costa 0 atıyorum
	cout << "> Define the object:"<<endl<<"> ";
	cin.getline(nesne.name,100);// nesne adını soruyorum
	cout << "> What is "<<nesne.name<<"?:";
	strcpy(temp,nesne.name);// nesne.name değişkenini ileride kullanacağım için ilk objenin adını bir temp stringinde tutuyorum
	parser(nesne.name,nesne,1);
	strcpy(nesne.name,temp);// işlemler sonuçlandığında yazdırmak için geri alıyorum değişkeni
	cout<<" > Total cost of "<<nesne.name<<" is "<<nesne.cost<<endl;

}

void parser(char temp[100],object& objectx,int piece){
//Recursion olarak sorarak sırayla gidiyor. Sayı gördüğünde ise costa ekleyip ordaki dallanmayı(fonksiyonu) bitirip, diğer daldan devam ediyor.
//Gördüğü şey bir polinom tarzı girişse(2*tekerlek+1*gövde gibi) tempnum stringine sayıları alıp inte çeviriyor, temp2 arrayinede kelimeyi alıyor what is sorusunu soruyor
//daha sonra tekrar teemp arrayinde işleme devam ediyor( Recursionu temp2 arrayinle çağırma sebebim).

int size,a=0,b=0;//size stringin boyutu, a değişkeni ilk girilen string sayacı, b değişkeni ise parçaların(kelime,çarpan sayı) sayacı
char tempnum[10],temp2[100];//tempnum çarpan sayacı sayı 11 haneliyse sorun çıkabilir ben size'ı 10 verdim, temp2 ise kelime stringim

cout<<"\n"<<"> ";//pdfte istenen gibi olması için ekrana yazdırdığım detaylar
cin.getline(temp,100);	//aldığım cevap(soruyu recursionı çağırmadan önce soruyorum aşağıda yani
	
	if(isNumber(temp)==1){	//sayıysa direk costa topluoyrum
		objectx.cost=objectx.cost+piece*atof(temp);		
	}
	else if(isNumber(temp)==0){//sayı değilse parçalıyorum
			size=strlen(temp);
			while(temp[a]==' '){//Boşluk ilerletici(baştaki boşlukiçin)
				a=a+1;
			}
			while(a<size){
				while(temp[a]==' '){//Boşluk ilerletici(kelime başlarındaki boşluk için)
					a=a+1;
				}
				while(temp[a]!='+'&&a<size){//eğer artı değil ve string içindeyse girip sayı veya kelimeyi parçalıyorum		
					while(temp[a]!='*'&&isNumberchar(temp[a])==1){//ilk çarpma işaretine kadar sayıyı buluyorum
						tempnum[b]=temp[a];
						tempnum[b+1]='\0';
						a++;
						b++;
						
					}
					//tempnum[b]='\0';
					while(temp[a]==' '){//Boşluk ilerletici(sayıdan sonra yıldızdan önce boşluk için)
						a=a+1;
					}
					if(temp[a]=='*'){
						a=a+1;
						b=0;
					}
					//tempnum[b]='\0';
					while(temp[a]==' '){//Boşluk ilerletici(yıldız sonrası boşluk)
						a=a+1;
					}		
						temp2[b]=temp[a];//kelimeyi alıyorum
						b++;
						a++;
						temp2[b]='\0';
					while(temp[a]==' '){//Boşluk ilerletici(kelime sonu boşluk +dan önce)
						a=a+1;
					}	
				}
				a++;//+gördüğünde döngüden çıkacağı için bir arttırıp string bitmediyse devam ettiriyorum
				while(temp[a]==' '){//Boşluk ilerletici(kelime sonu boşluk)
						a=a+1;
				}
				b=0;//byi sıfırlıyorum yeni kelime ve ya sayı alacağım için.
				cout << "> What is "<<temp2<<"?:";
				piece=piece*atoi(tempnum);//çarpan katsayısını alıp alt dallar için recursionu çağrıyorum
				parser(temp2,objectx,piece); //fonksiyonu tekrar çağrıyorum.
				piece=piece/atoi(tempnum);//bağlantısı olmayan diğer dallarda normal çarpanla devam etmesi için çarptığım sayııy bölüyorum.
			}	
	}
}

int isNumber(char temp[100]){ //Stringin sayı olup olmadığına bakıyor, eğer her eleman sayıysa b sayacı ve size eşit olucak
	int size,a=0,b=0;
	size=strlen(temp);
	while(1){
		if(temp[a]=='0'||temp[a]=='1'||temp[a]=='2'||temp[a]=='3'||temp[a]=='4'||temp[a]=='5'||temp[a]=='6'||temp[a]=='7'||temp[a]=='8'||temp[a]=='9')
		{
			b++;
		}
		else if(temp[a]=='.')
		{
			b++;	
		}
	
		a++;
		if(b==size){
			return 1;
		}
		else if(a==size){
			return 0;
		}
	}
}
int isNumberchar(char temp){ // karakterin sayı olup olmadığına bakıyor
	if(temp=='0'||temp=='1'||temp=='2'||temp=='3'||temp=='4'||temp=='5'||temp=='6'||temp=='7'||temp=='8'||temp=='9')
		{
			return 1;
		}
	else
			return 0;

}
