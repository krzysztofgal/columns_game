#include "CNAPIS.h"


LPSTR NAPIS::Text(void){

	return text;
};

LPCSTR NAPIS::CText(){

	return text;
};

unsigned short NAPIS::Lenght(void){

	return dl;
};


void NAPIS::Alokuj(short ile){

	text=new char[ile+1];
	dl=ile;
};


NAPIS::NAPIS(){
	dl=0,text="";
};

NAPIS::NAPIS(LPCSTR txt){

		Alokuj(strlen(txt));
		strcpy(text,txt);

};


NAPIS::NAPIS(const NAPIS& nap){

	Alokuj(nap.dl);
	strcpy(text,nap.text);
};

int LiczbaCyfr(int liczba)
{
 if(liczba==0)return 1;
 div_t wyn;
 int liczbaCyfr=0;
 while(liczba!=0)
 {
  wyn=div(liczba,10);
  liczba=wyn.quot;
  liczbaCyfr+=1;
 }
 return liczbaCyfr;
};

NAPIS::NAPIS(int val){

	char buff[20];
	itoa(val,buff,10);
	Alokuj(LiczbaCyfr(val));
	strcpy(text,buff);
};

NAPIS& NAPIS::operator =(int val){

	char buff[20];
	itoa(val,text,10);
	Alokuj(LiczbaCyfr(val));
	strcpy(text,buff);

	return *this;
};

NAPIS& NAPIS::operator =(LPCSTR txt){

	if(this->text==txt)return *this;
	if(dl==strlen(txt))strcpy(text,txt);else
		Alokuj(dl=strlen(txt));
		strcpy(text,txt);
		return *this;

};



NAPIS& NAPIS::operator =(const NAPIS& nap){

	if(this->text==nap.text)return *this;
	if(this->dl==nap.dl)strcpy(text,nap.text);else
		Alokuj(dl=nap.dl);
		strcpy(text,nap.text);
		return *this;
};














