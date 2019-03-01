#include <iostream>
#include <cstdlib>
//Kodum eksik, X ve Y'yi oyun alanında doğru ve eksiksiz hareket ettirebilecek algoritmayı kuramadım, 
//teker teker yazabilirdim fakat doğru olmayacağını düşündüm ve kod fazla uzardı. Bu yüzden win koşuluda eksik.
//X ve Y'yi oyun alanına oynatmaya olayına kadar(x ve y oynamıyor yani) diğer şeyleri yapması lazım kodun.
using namespace std;

void randomHand(int playerHand[3],int trash[9]);//ele random kart seçiyor, trashta eski kartların indexi var ki onlar gelmesin birdaha
void gameBoard(char** board,int h,int w,int position,int rotate,int portaldata[9]);//oyun boardına kartı yerleştiriyor
void printBoard(char** board,int h,int w);//oyun boardını yazdırıyor
void initBoard(char** board,int h,int w);//oyun boardına boş değer atıyor
int deletecard(int deletedcard,int trash[9]);//oynanan kartı elden çıkarıp yerine yeni kart alıyor
void initPlayer(char** board,int h,int w,int Player1,int Player2);//oyuncuların başlangıç yerlerini oyun alanına yerleştiriyor
int isNumber(char character);//eleman sayımı diye bakıyor Uncomplete fonksiyonumda kullanacaktım fakat çözemedim
int instructions();//nasıl oynanır

class Tsuro
{
public:
	Tsuro();//kart oluşturuyor
	void Cardsdisplay();//kardı gösteriyor
	int portaldata[8];//Mesela ilk eleman 1'in portalını tutuyor,2.Eleman 2'in portalını
private:
 	void Portals();//carddataya göre portalları oluşturuyor
	int carddata[8];//kartların birbirleriyle bağlantısın tutuyor.2şerli şekilde elemanlar bağlı
	int cardedges[8];//Kart köşeleri	
};

Tsuro::Tsuro(){
	
	int i=0,j=0;
	while(j<8){
		carddata[j]=rand()%8+1;//random sayı oluşturuyorum
		while(i<j){//karttaki eski sayılara bakıyorum
			while(carddata[j]==carddata[i]){//sayı tekrarlıyorsa varsa bir daha oluşturuyor
				carddata[j]=rand()%8+1;
				i=0;	
			}
			i++;
		}
		i=0;
		j++;
	}
	Portals();	//bağlantıları portaldata attığım fonksiyon

}	
void Tsuro::Portals(){
	int i=0,j=1;
	while(j<9){
		if(j==carddata[i]){//1i bulduğu yerde 1in bağlantısını almak için döngüye giriyor
			if(i%2==0){
				portaldata[j-1]=carddata[i+1];//1 eğer tek sayılı bir elemandaysa -1.elemanla bağlantılı, çift sayılı bir elemandaysa +1'in elemanla bağlantılı
			}
			else{
				portaldata[j-1]=carddata[i-1];
			}
			//cout<<"j=="<<j<<"  =="<<portaldata[j-1]<<"  i=="<<i<<endl;
			cardedges[j-1]=j;//elamanı kartın köşelerinin tutulduğu arraye atıyor
			j++;
			i=0;
		}
		else
		i++;
	}
	//Cardsdisplay();
}

void Tsuro::Cardsdisplay(){
	if((portaldata[0]>0&&portaldata[1]<9)&&(portaldata[2]>0&&portaldata[3]<9)&&(portaldata[4]>0&&portaldata[5]<9)){
	cout <<"...."<<cardedges[0]<<".."<<cardedges[1]<<"...."<<endl;
	cout <<":   "<<portaldata[0]<<"  "<<portaldata[1]<<"   :"<<endl;
	cout <<cardedges[7]<<"   "<<portaldata[7]<<"  "<<portaldata[2]<<"   "<<cardedges[2]<<endl;
	cout <<cardedges[6]<<"   "<<portaldata[6]<<"  "<<portaldata[3]<<"   "<<cardedges[3]<<endl;
	cout <<":   "<<portaldata[5]<<"  "<<portaldata[4]<<"   :"<<endl;
	cout <<"...."<<cardedges[5]<<".."<<cardedges[4]<<"...."<<endl<<endl;
	}
	else
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl;

}



int main(){
	srand(time (NULL));
	Tsuro c[9];
	char** gameboard;
	gameboard = new char *[20];//Gameboardı oluşturuyorum
	for(int i = 0; i <20; i++){
    	gameboard[i] = new char[38];
	}
	initBoard(gameboard,20,38);
	int starternumber,cardChoosen1,cardChoosen2,boardChoosen,rotate,Posx,Posy,x=0;//starternumber main menu için
	//cardChoosenler seçilen kartlar, boardCHoosen oynanmak istenen yer, rotate döndürülmek istenen yön için tutulan değişken,Posx ve Posy başlangıç yerleri'x' ve'y'için
	int player1hand[3],player2hand[3],trash[9];//trashda eldeki kartlar ve eski kartlar var. Kartlar en fazla 2 kere tekrarlıyor

	while (1){/*oyundan çıkmak kullanıncın kontrolünde olması için while döngüsünü koşulsuz yapıyorum*/
		cout << ("\t\tWelcome the Tsuro GTU Version\n Please enter a number that defines what you want to do\n\t1.Play against friend \n \t2-Instructions \n \t3.Exit\n");
			cin >> starternumber;
		switch(starternumber){
			case 1:
					randomHand(player1hand,trash);//ellere kart çekyiruom
					randomHand(player2hand,trash);
					cout << ("Player1's Turn. Where do you want to start\n");
					cin>>Posx;
					cout << ("Player2's Turn. Where do you want to start\n");
					cin>>Posy;
					if(Posx==Posy){
						cout << ("Its already filled.Choose again please player 2?\n");
						cin>>Posy;
					}
					initPlayer(gameboard,20,38,Posx,Posy);//başlangıç taşlarını boarda koyuyorum
					while(x<9){
						
						c[player1hand[0]].Cardsdisplay();//kartları gösteriyorum sırayla ve seçtiriyorum
						c[player1hand[1]].Cardsdisplay();
						c[player1hand[2]].Cardsdisplay();
						cout << ("Player1's Turn. Choose one card(1-2-3)-Dont choose empty ones\n");
						cin>>cardChoosen1;
						while(cardChoosen1<1||cardChoosen1>3){
							cout << ("Player1' Choose one card again(1-2-3)\n");
							cin>>cardChoosen1;
						}
						cout << "Do you want rotate?\n"<<"1-For original(norotate) 2-For rotate Right 3- For rotate Down 4- For rotate left\n";
						cin>>rotate;//döndürülmek istenen yönü alıyorum
						 while(rotate<1||rotate>4){
							cout << "What are you doing,Wrong number pls try again???\n"<<"1-For original(norotate) 2-For rotate Right 3- For rotate Down 4- For rotate left\n";
							cin>>rotate;
						 }
						printBoard(gameboard,20,38); 
						cout<<"Choose where you want to place your card(gameboard regions(1-9))";
						cin>>boardChoosen;//kartı koymak istediği region
						 while(boardChoosen<1||boardChoosen>9){
							cout << "Wrong number pls try again???\n";
							cin>>boardChoosen;
						 }
						gameBoard(gameboard,20,38,boardChoosen,rotate,c[player1hand[cardChoosen1-1]].portaldata);
						//checkMoves(gameboard,20,38); uncomplete fonksiyon. algoritmayı kuramadım
						player1hand[cardChoosen1-1]=deletecard(player1hand[cardChoosen1-1],trash);
						x++;//hamle sayacı
						
						if(x==9){
							cout<<"\t\tGAME OVER--9 MOVE IS OVER\n";
							break;
						}
						c[player2hand[0]].Cardsdisplay();
						c[player2hand[1]].Cardsdisplay();
						c[player2hand[2]].Cardsdisplay();
						cout << ("Player2's Turn. Choose one card(1-2-3)-Dont choose empty ones\n");
						cin>>cardChoosen2;
						while(cardChoosen2<0||cardChoosen2>3){
							cout << ("Player2' Choose one card again(1-2-3)\n");
							cin>>cardChoosen2;
						}
						cout << "Do you want rotate?\n"<<"1-For original(norotate) 2-For rotate Right 3- For rotate Down 4- For rotate left\n";
						cin>>rotate;
						 while(rotate<1||rotate>4){
							cout << "What are you doing,Wrong number pls try again???\n"<<"1-For original(norotate) 2-For rotate Right 3- For rotate Down 4- For rotate left\n";
							cin>>rotate;
						 }
						printBoard(gameboard,20,38);
						cout<<"Choose where you want to place your card(gameboard regions(1-9))";
						cin>>boardChoosen;
						while(boardChoosen<1||boardChoosen>9){
							cout << "Wrong number pls try again???\n";
							cin>>boardChoosen;
						 }
						gameBoard(gameboard,20,38,boardChoosen,rotate,c[player2hand[cardChoosen2-1]].portaldata);
						//checkMoves(gameboard,20,38); uncomplete fonksiyon. algoritmayı kuramadım
						player2hand[cardChoosen2-1]=deletecard(player2hand[cardChoosen2-1],trash);
						x++;//hamle sayacı
					
					}
			 		break;
			case 2:
					instructions();
					break;
			case 3:
					return 0;
					break;
			default:
					cout << ("Its invalid number. Enter a number again\n");
					break;

		}
	}
	return 0;
}
int instructions(){
int a;
cout << "------------------------TSURO------------------------"<<endl;
	
		cout <<"Tsuro is a game can played with cards,two players and a gameboard. All cards have a portals and enters.\n";
		cout <<"Each player have 3 card.\n";
		cout<<"Example Card"<<endl<<"   1 2   "<<endl<<"   5 3   "<<endl<<"8  7 5  3"<<endl<<"7  8 6  4"<<endl<<"   4 3   "<<endl<<"   6 5    "<<endl; 
		cout <<"In this card 1 is connected to 5, so when players play his 'X' or 'Y' on 1,\n his 'X' or 'Y' will move to 5(bottom of card)\n ";
		cout <<"And when a player place a card bottom of the first card,player must move to the the nearest enter of new card and will move to new portal\n";
		cout <<"When a player our of gameboard, he will lose, And if two player come face-to-face, they both lose\n\n ";
		
	cout<<"Press 1 for next(Gameboard help),other numbers for skip"<<endl;
	cin>>a;
	if(a!=1){
		return 1;
	}
		cout << "GameBoard regions\n";
		cout <<"|-o-o-|\n";
		cout <<"|1-2-3|\n";
		cout <<"|4-5-6|\n";
		cout <<"|7-8-9|\n";
		cout <<"|-o-o-|\n\n\n";
		cout<<"Game enter-place numbers(example)\n";
		cout<<"|-o-o---o--o|\n";
		cout<<"| 1 2   3  4|\n";
		cout<<"o<-5     6->o\n";
		cout<<"o<-7     8->o\n";
		cout<<"|-----------|\n\n";
		
}
void randomHand(int oneHand[3],int trash[9]){
	int i,j=0,l=0;
	static int k=0;
	while(1){
		i=rand()%8+1;
		while(l<k){
			while(i==trash[l]){//eğer kart daha önce kullanıldılysa yeni kart numarası alıyor
				i=rand()%8;		
			}	
		l++;
		}
		oneHand[j]=i;
		j++;
		trash[k]=i;
		k++;
		if(j==3){
			break;
		}	
	}
}
int deletecard(int deletedcard,int trash[9]){
 int i,l=0;//elindeki kartın indexini siliyor ve trashta varsa tekrar o indexi döndürmüyor, yeni index randomluyor
 	while(l<9){
 		while(i==trash[l]){
				i=rand()%9;		
		}
	l++;
	}
	return i;	
}
void printBoard(char** board,int h,int w){
 int i,j;
 for(i=0;i<h;i++)
 {
  for(j=0;j<w;j++)
  	cout<<board[i][j];
  cout<<endl;	
  }
}
void gameBoard(char** board,int h,int w,int position,int rotate,int portaldata[9]){
	 int x,y,i,j;
	 x=((position-1)/3)+1;//region işlemleri,koordinatlar için
	 y=((position-1)%3)+1;
	 i=((x-1)*6)+1;
	 j=((y-1)*12)+1;
	 //belirli bir algoritma kuramadığım için teker teker yerleştirdim oyun alanına
	 if(rotate==1){
		 board[i][j+4]='1';
		 board[i][j+7]='2';
		 board[i+2][j+11]='3';
		 board[i+3][j+11]='4';
		 board[i+5][j+7]='5';
		 board[i+5][j+4]='6';
		 board[i+3][j]='7';
		 board[i+2][j]='8';
		 board[i+1][j+4]=portaldata[0]+'0';
		 board[i+1][j+7]=portaldata[1]+'0';
		 board[i+2][j+7]=portaldata[2]+'0';
		 board[i+3][j+7]=portaldata[3]+'0';
		 board[i+4][j+7]=portaldata[4]+'0';
		 board[i+4][j+4]=portaldata[5]+'0';
		 board[i+3][j+4]=portaldata[6]+'0';
		 board[i+2][j+4]=portaldata[7]+'0';
	 }
	 else if(rotate==2){
		 board[i][j+4]='7';
		 board[i][j+7]='8';
		 board[i+2][j+11]='1';
		 board[i+3][j+11]='2';
		 board[i+5][j+7]='3';
		 board[i+5][j+4]='4';
		 board[i+3][j]='5';
		 board[i+2][j]='6';
		 board[i+1][j+4]=portaldata[6]+'0';
		 board[i+1][j+7]=portaldata[7]+'0';
		 board[i+2][j+7]=portaldata[0]+'0';
		 board[i+3][j+7]=portaldata[1]+'0';
		 board[i+4][j+7]=portaldata[2]+'0';
		 board[i+4][j+4]=portaldata[3]+'0';
		 board[i+3][j+4]=portaldata[4]+'0';
		 board[i+2][j+4]=portaldata[5]+'0';
	 }
	 else if(rotate==3){
		 board[i][j+4]='5';
		 board[i][j+7]='6';
		 board[i+2][j+11]='7';
		 board[i+3][j+11]='8';
		 board[i+5][j+7]='1';
		 board[i+5][j+4]='2';
		 board[i+3][j]='3';
		 board[i+2][j]='4';
		 board[i+1][j+4]=portaldata[4]+'0';
		 board[i+1][j+7]=portaldata[5]+'0';
		 board[i+2][j+7]=portaldata[6]+'0';
		 board[i+3][j+7]=portaldata[7]+'0';
		 board[i+4][j+7]=portaldata[0]+'0';
		 board[i+4][j+4]=portaldata[1]+'0';
		 board[i+3][j+4]=portaldata[2]+'0';
		 board[i+2][j+4]=portaldata[3]+'0';

	 }
	 else  if(rotate==4){
		 board[i][j+4]='3';
		 board[i][j+7]='4';
		 board[i+2][j+11]='5';
		 board[i+3][j+11]='6';
		 board[i+5][j+7]='7';
		 board[i+5][j+4]='8';
		 board[i+3][j]='1';
		 board[i+2][j]='2';
		 board[i+1][j+4]=portaldata[2]+'0';
		 board[i+1][j+7]=portaldata[3]+'0';
		 board[i+2][j+7]=portaldata[4]+'0';
		 board[i+3][j+7]=portaldata[5]+'0';
		 board[i+4][j+7]=portaldata[6]+'0';
		 board[i+4][j+4]=portaldata[7]+'0';
		 board[i+3][j+4]=portaldata[0]+'0';
		 board[i+2][j+4]=portaldata[1]+'0';
	
	 }
	 else
	 cout<<"wrong move,your turn is passed, learn the rules \n";

	printBoard(board,20,38);
}
void initBoard(char** board,int h,int w){
 int i,j;
 for(i=0;i<h;i++)
  for(j=0;j<w;j++)
  	if(((j==5||j==8||j==20||j==17||j==32||j==29)&&(i==0||i==h-1))||((i==3||i==4||i==10||i==9||i==16||i==15)&&(j==0||j==w-1)))//girişleri ayarlıyorum
  		board[i][j]='o';
  	else if(i==0||i==h-1)
  		board[i][j]='-';//üst kenarlara çizgi
  	else if(j==0||j==w-1)	
  		board[i][j]='|';//yan kenarlara dik çizgi
  	else
  		board[i][j]=' ';//geri kalanlar boşluk	
}
void initPlayer(char** board,int h,int w,int Player1,int Player2){
 int i,j,k=0,flag1=0,flag2=0;//flagler sadece bir tane 'x' ve 'y' koyması için
  for(i=0;i<h;i++)
  {	
   for(j=0;j<w;j++)	//girilmek istenen yerin koordinatını bulup taşı oraya koyuyor
   {
    	if(board[i][j]=='o')
			k++;
		if(k==Player1&&flag1==0){
			board[i][j]='X';
			flag1=1;
		}	
		if(k==Player2&&flag2==0){
			board[i][j]='Y';
			flag2=2;
		}	
  }
 }
}

int checkMoves(char** board,int h,int w){//Uncomplete fonksiyon
 int i,j;
 char tempx,tempy;
 int tempXi,tempXj,tempYi,tempYj;
	for(i=0;i<h;i++)
	{	
		for(j=0;j<w;j++)	
	    {
			if(board[j][i]=='X'){
				
		
		
			}
		}
		
	}
}


int isNumber(char temp){ // karakterin sayı olup olmadığına bakıyor, Herhangi biyerde kullanamadım checkmovesde kullanamyı düşünüyordum fakat kısa algoritma kuramadım.
	if(temp=='0'||temp=='1'||temp=='2'||temp=='3'||temp=='4'||temp=='5'||temp=='6'||temp=='7'||temp=='8'||temp=='9')
		{
			return 1;
		}
	else
			return 0;

}
