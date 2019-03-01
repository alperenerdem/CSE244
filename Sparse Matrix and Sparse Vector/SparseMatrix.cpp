
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "SparseMatrix.h"


SparseMatrix& SparseMatrix::operator=(const SparseMatrix &m1){
	int a=0;
 // ilk önce kendi matrisimizi clearlıyorum
	while(this->SparMat.size()>a){
		this->SparMat[a].clear();
		this->SparMatData[a].clear();
		a++;
	}
	this->SparMat.clear();
	this->SparMatData.clear();
	this->SparMatRowData.clear();

	a=0;
	//sonra sırayla değerleri alıyorum
	while(m1.SparMat.size()>a){
		this->SparMat.push_back(m1.SparMat[a]);
		this->SparMatData.push_back(m1.SparMatData[a]);
		a++;
	}
	a=0;
	while(m1.SparMatRowData.size()>a){
		this->SparMatRowData.push_back(m1.SparMatRowData[a]);
		a++;
	
	}
}


SparseMatrix operator-(const SparseMatrix &m1){
	
	SparseMatrix resMat;
	vector <double> temp; // tuttuğum row,2d vectote pushbackliyorum
	vector <int> tempData; //tuttuğum rowdatalar, 2d vectore pushbackliyorum
	int a=0,b=0;//a üst boyut(satırın sayısı) için, b satır içindeki sayaç
 	while(a<m1.SparMat.size()){//rowlar bitene kadar
 			while(b<m1.SparMatData[a].size())//row bitene kadar
 			{
 				temp.push_back(0-m1.SparMat[a][b]);//0dan çıkarıp temp ve tempDataya atıyorum
				tempData.push_back(m1.SparMatData[a][b]);
				b++;
			}	
	 	resMat.SparMatRowData.push_back(m1.SparMatRowData[a]);//templeri resultMatrixine atıyorum
	 	resMat.SparMat.push_back(temp);
	 	resMat.SparMatData.push_back(tempData);
	 	temp.clear();
	 	tempData.clear();
		b=0;
 		a++;
 	}
 	return resMat;	


}
SparseMatrix operator+(const SparseMatrix &m1, const SparseMatrix &m2){
	SparseMatrix resMat;
	vector <double> temp; // tuttuğum row,2d vectote pushbackliyorum
	vector <int> tempData; //tuttuğum rowdatalar, 2d vectore pushbackliyorum
	int a=0,b=0,c=0,d=0;
	//a(m1) ve b(m2) üst boyut(satırın sayısı) için, c(m1) ve d(m2) satır içindeki sayaç
 	while(a<m1.SparMat.size()||b<m2.SparMat.size()){//büyük sizelar kadar ilk döngü

 		if(b==m2.SparMat.size()||m1.SparMatRowData[a]<m2.SparMatRowData[b]){
 		//eğer m2 işlemleri bittiyse veya m1'in satır sayısı m2'den büyükse sadece m1den işlem yapıyorum
 			resMat.SparMatRowData.push_back(m1.SparMatRowData[a]);
 			resMat.SparMat.push_back(m1.SparMat[a]);
 			resMat.SparMatData.push_back(m1.SparMatData[a]);
 			a++;
 		}
 		else if(a==m1.SparMat.size()||m1.SparMatRowData[a]>m2.SparMatRowData[b]){
 		//eğer m1 işlemleri bittiyse veya m2'in satır sayısı m2'den büyükse sadece m2den işlem yapıyorum
 			resMat.SparMatRowData.push_back(m2.SparMatRowData[b]);
 			resMat.SparMat.push_back(m2.SparMat[b]);
 			resMat.SparMatData.push_back(m2.SparMatData[b]);
 		
 			b++;
 		}
 		else if(m1.SparMatRowData[a]==m2.SparMatRowData[b]){
 		//eğer satır sayıları eşitse, sparsevector '+' operatorunun overloadingin aynısın yapıyorum
 			while(c<m1.SparMatData[a].size()||d<m2.SparMatData[b].size())
 			{
		 		if(d==m2.SparMat.size()||c<m1.SparMat.size()&&m1.SparMatData[a][c]<m2.SparMatData[b][d]){
					temp.push_back(m1.SparMat[a][c]);
					tempData.push_back(m1.SparMatData[a][c]);
					c++;
				}
				else if(c==m1.SparMat.size()||m1.SparMatData[a][c]>m2.SparMatData[b][d]){
					temp.push_back(m2.SparMat[b][d]);
					tempData.push_back(m2.SparMatData[b][d]);
					d++;

				}
				else if(m1.SparMatData[a][c]==m2.SparMatData[b][d]){
					if(m1.SparMat[a][c]+m2.SparMat[b][d]!=0){// toplam sıfırsa almıyorum, çünkü sparse.
						temp.push_back(m1.SparMat[a][c]+m2.SparMat[b][d]);
						tempData.push_back(m1.SparMatData[a][c]);
						c++;d++;
					}	
				}	
 			}
 			if(temp.size()!=0){
	 			resMat.SparMatRowData.push_back(m1.SparMatRowData[a]);
	 			resMat.SparMat.push_back(temp);
	 			resMat.SparMatData.push_back(tempData);
	 			temp.clear();
	 			tempData.clear();
 			}
 			a++;b++;
 			c=0;d=0;
 		}
 	}
 	return resMat;		
}

SparseMatrix operator-(const SparseMatrix &m1, const SparseMatrix &m2){
	SparseMatrix resMat;
	vector <double> temp;
	vector <int> tempData;
	int a=0,b=0,c=0,d=0;
	// + operatörünün aynısı, farklı olan yerin yorumun yazıcam sadece
 	while(a<m1.SparMat.size()||b<m2.SparMat.size()){
 		if(b==m2.SparMat.size()||m1.SparMatRowData[a]<m2.SparMatRowData[b]){
 			resMat.SparMatRowData.push_back(m1.SparMatRowData[a]);
 			resMat.SparMat.push_back(m1.SparMat[a]);
 			resMat.SparMatData.push_back(m1.SparMatData[a]);
 			a++;
 		}
 		else if(a==m1.SparMat.size()||m1.SparMatRowData[a]>m2.SparMatRowData[b]){
 			resMat.SparMatRowData.push_back(m2.SparMatRowData[b]);
 			//eğer 0dan çıkarıyorsak, ordaki rowu teker teker0dan çıkarıp yeni bir tempe atıyorum
 			// sonra sonuç matrixine pushbackliyorum
 			while(d<m2.SparMat[b].size()){
 				temp.push_back(0-m2.SparMat[b][d]);
 				d++;
 			}
 			resMat.SparMat.push_back(temp);
 			temp.clear(); d=0;
 			resMat.SparMatData.push_back(m2.SparMatData[b]);
 		
 			b++;
 		}
 		else if(m1.SparMatRowData[a]==m2.SparMatRowData[b]){
 			while(c<m1.SparMatData[a].size()||d<m2.SparMatData[b].size())
 			{// sparsevectordeki işlemlerin aynısı
		 		if(d==m2.SparMatData[b].size()||(c<m1.SparMat.size()&&m1.SparMatData[a][c]<m2.SparMatData[b][d])){
		 		//eğer  m2'de gezeceğim yerler bittiyse veya m1deki indis, m2den küçükse buraya giriyor
		 		//m1in rowundaki elemanı direk pushbackliyor
					temp.push_back(m1.SparMat[a][c]);
					tempData.push_back(m1.SparMatData[a][c]);
					c++;
				}
				else if(c==m1.SparMat.size()||m1.SparMatData[a][c]>m2.SparMatData[b][d]){

					temp.push_back(0-m2.SparMat[b][d]);
					tempData.push_back(m2.SparMatData[b][d]);
					d++;

				}
				else if(m1.SparMatData[a][c]==m2.SparMatData[b][d]){
					if(m1.SparMat[a][c]-m2.SparMat[b][d]!=0){// 0 değilse işlem yapıyorum
						temp.push_back(m1.SparMat[a][c]-m2.SparMat[b][d]);
						tempData.push_back(m1.SparMatData[a][c]);
					}
					c++;d++;
				}	
 			}
 			if(temp.size()!=0){
	 			resMat.SparMatRowData.push_back(m1.SparMatRowData[a]);
	 			resMat.SparMat.push_back(temp);
	 			resMat.SparMatData.push_back(tempData);
	 			temp.clear();
	 			tempData.clear();
 			}
 			a++;b++;
 			c=0;d=0;
 		}
 	}
 	return resMat;		
}



std::ostream & operator <<(std::ostream & output, SparseMatrix const& m1){
	int a=0,b=0;
	//sırayla elemanları ostreame gönderecek şekilde topluyorum, sonra ostreami return ediyorum
	
	while(a<m1.SparMat.size()){
		output<<m1.SparMatRowData[a]<<' ';
		while(b<m1.SparMatData[a].size()){
			output<<m1.SparMatData[a][b]<<':'<<m1.SparMat[a][b]<<' ';
			b++;
		}
		b=0;
		output<<'\n';
		a++;
	}
	return output;
	


}

SparseMatrix::SparseMatrix(){
//default
}


SparseMatrix::SparseMatrix(const char *filename){
	ifstream cinfromfile;
	cinfromfile.open(filename);
	int countStr=0,counter=0,a;//line sayacı=countStr,line içinde counter
	double b;
	char c;
	vector <int> rowsData;//Rowun içindekie elemanların indisi
	vector <double> rows;//rowun içindeki elemanlar
	vector <string> lines;//lineleri string vectorüne alıyorum
	string line,temp;
	while(1){
		if(cinfromfile.eof()){
			break;
		}
		getline(cinfromfile,line);

		if(cinfromfile.eof()){
			break;
			
		}
		lines.push_back(line);
		
	}
	//şimdi string vectorünü parsere gönderiyorum
	while(countStr<lines.size()){//line sayısı kadar bölücem
		while(lines[countStr][counter]!=' '&&counter<lines[countStr].size()){
					temp.push_back(lines[countStr][counter]);//ilk önce row sayısını alıyorum boşluk görene kadar
					counter++;
		}
		counter++;//boşluğu geçiyorum
		a = stoi(temp);//row sayısnı integere çevirip rowdataya atıyorum
		SparMatRowData.push_back(a);

		temp.clear();//tempi clearliyorum sonra kullanıcam
		
		while(counter<lines[countStr].size()){//line'ın size'ı kadar sayaçla geziyorum 
			while(lines[countStr][counter]!=':'&&counter<lines[countStr].size()){
					temp.push_back(lines[countStr][counter]);
					counter++;//':' görene kadar indisi alıyorum
			}
			a = stoi(temp);//indisi integere çevirim rowdataya atıyorum

			rowsData.push_back(a);
			temp.clear();
			counter++;
			while(lines[countStr][counter]!=' '&&counter<lines[countStr].size()){
					temp.push_back(lines[countStr][counter]);
					counter++;//sayıyı alıp double çevirip rows'a atıyorum
			}
			b = stod(temp);

			rows.push_back(b);
			temp.clear();
			counter++;
		}
			
		SparMat.push_back(rows);//class içindeki datayı burdaki temp dataları atıyrum
		//sonra onları tekrar kullanmakiçin clearlıyorum
		SparMatData.push_back(rowsData);	
		rows.clear();
		rowsData.clear();
		counter=0;
		countStr++;
		
	}

}
