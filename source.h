#include "EKRAN.h"
#include "INPUT.h"

struct KLOCEK
{
 int kolor;
 bool sterowany;
};

class PLANSZA
{
 public:
  KLOCEK* plansza;								//wska�nik do obiektu KLOCEK
  KLOCEK* kopiaPlanszy;							// j/w
  int wysokosc,szerokosc;						//wysokos� i szeroko�� planszy
  unsigned short left,right;					//potrzebne do przesuwania klocka
  BITMAPA zestaw;								//BITMAPA zawieraj�ca klocki
  clock_t ostatniCzas,obecnyCzas,czasAnim;		//zmienne przechowuj�ce czas
  int predkosc,predkosc_tmp;					//pr�dko�� opadania klocka
  bool trwaGra,pauza,gameOver;					//do zorganizowania ca�ego systemu
  bool kasowane;								//u�yte przy kasowaniu
  int kolor,punkty,level;						//kolor kasowanego klocka �eby przy drugim
												//etapie kasowania nie pisa� tego samego 5 razy   
  int kol,pozycja;								//do losowania klocka									
  void inicjuj(int,int);						//funkcja inicjuje tablic� jednowymiarow�
    
  void losujKlocka(void);						//funkcja losuj�ca klocki
  void przesunKolory(void);						//przesuwanie koloru
  void opuscWDol();								//jesli pod klockiem jest wolne miejsce to przenosi go na nie
  void opuscWDolKlocka();						// j/w tylko dla sterowanedo klocka
  void przesunKlocka();							// w lewo lub prawo + reszta obs�ugi klawiatury
  void kasuj();									//algoytm kasuj�cy klocki
  
  void skanuj();								//g��wna funkcja programu steruje wszystkimi innymi
  void rysuj(void);								//rysowanie planszy
};

class Button//u�atwienie do zrobienia MENU g��wnego
{
 public:
 Button();
 BITMAPA ob;
 int x,y;
 bool aktywny;
 bool dostepny;
 void ZmienStan();
 void Pozycja(int,int);
 void Rysuj(int,int,NAPIS,DWORD);
};