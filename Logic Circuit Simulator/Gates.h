#ifndef GATES_H
#define GATES_H
#include <iostream>
#include <string>
using namespace std;
class Gates
{	
	public:
		Gates(){ /*def */;};
		~Gates();
		virtual void initInOut(int target,int value) = 0;//inputları outputları ayarlıyor, birnevi çözüyor
		virtual void reset() = 0;//devreyi resetliyor
		Gates(int number);//INPUT ve OUTPUT arrayinde kaç labels girileceğini belirsiz olduğu için burdaki number size belirliyor.

		 string type;//Input ve outputları tüm arrayde aramak için type'larına bakıyorum
		 			// aslında class tipi aratmak istedim fakat işlediğimiz bir kaynakta bulamadım
		 			//bu yüzden type tuttum, sadece INPUT ve OUTPUTta kullandım
		 string* label;//output labels for gates
		 string* inputlabels;//input labels for gates
		 int* values;//output values for gates
		 int* inputvalues;//input values for gates
		 int sizeReturner(){return size;}//outputsize returner
		 int inputsizeReturner(){return inputsize;}//inputsize returner
	protected:
		 int size;//outputsize
    	 int inputsize;//inputsize
};

//alttaki classlar gates'den inherit ediyolar ve constructları hariç farklı birşeyleri yok
class AND: public Gates
{
	public:
		AND(string labels);
		void initInOut(int target,int value);
	private:
		void reset();	
};
class OR: public Gates
{
	public:
		OR(string labels);
		void initInOut(int target,int value);
		
	private:	
		void reset();
};
class NOT: public Gates
{
	public:
		NOT(string labels);
		void initInOut(int target,int value);
	private:	
		void reset();
};
class DECODER: public Gates
{
	public:
		DECODER(string labels);
		void initInOut(int target,int value);
	private:	
		void reset();	
};
class FLIPFLOP: public Gates
{
	public:
		FLIPFLOP(string labels);
		void initInOut(int target,int value);
	private:	
		void reset();	 
};
class INPUT: public Gates
{
	public:
		INPUT(){ /*def */;}
		void initInOut(int target,int value);
		INPUT(int number,string labels);
	private:	
		void reset(){/*def */};	

};
class OUTPUT: public Gates
{
	public:
		OUTPUT(){ /*def */;}
		
		OUTPUT(int number,string labels);

		void initInOut(int target,int value);
		
	private:	
		void reset(){/*def */};	
};

#endif

