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
  KLOCEK* plansza;								//wskaŸnik do obiektu KLOCEK
  KLOCEK* kopiaPlanszy;							// j/w
  int wysokosc,szerokosc;						//wysokosæ i szerokoœæ planszy
  unsigned short left,right;					//potrzebne do przesuwania klocka
  BITMAPA zestaw;								//BITMAPA zawieraj¹ca klocki
  clock_t ostatniCzas,obecnyCzas,czasAnim;		//zmienne przechowuj¹ce czas
  int predkosc,predkosc_tmp;					//prêdkoœæ opadania klocka
  bool trwaGra,pauza,gameOver;					//do zorganizowania ca³ego systemu
  bool kasowane;								//u¿yte przy kasowaniu
  int kolor,punkty,level;						//kolor kasowanego klocka ¿eby przy drugim
												//etapie kasowania nie pisaæ tego samego 5 razy   
  int kol,pozycja;								//do losowania klocka									
  void inicjuj(int,int);						//funkcja inicjuje tablicê jednowymiarow¹
    
  void losujKlocka(void);						//funkcja losuj¹ca klocki
  void przesunKolory(void);						//przesuwanie koloru
  void opuscWDol();								//jesli pod klockiem jest wolne miejsce to przenosi go na nie
  void opuscWDolKlocka();						// j/w tylko dla sterowanedo klocka
  void przesunKlocka();							// w lewo lub prawo + reszta obs³ugi klawiatury
  void kasuj();									//algoytm kasuj¹cy klocki
  
  void skanuj();								//g³ówna funkcja programu steruje wszystkimi innymi
  void rysuj(void);								//rysowanie planszy
};

class Button//u³atwienie do zrobienia MENU g³ównego
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