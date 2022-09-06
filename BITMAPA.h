//dzi�ki sortowaniu bitmap klasa BITMAPA jest odpowidnio przygotowana do silnika izometrycznego
#include "SURFACE.h"
#include <time.h>
#include <stdlib.h>
#include "CNapis.h"
#include "Flagi.h"

// ANIMACJA jest cz�ci� bitmapy nie wystepuje samodzielnie
struct ANIMACJA
{
 ANIMACJA();
 int* klatki;											//warto�ci tablicy klatek
 DWORD flaga;											//typ animacji
 int klatka,Czas,X,Y,ileklatek,predkosc,pozycja,poziom;	//dane do przeliczania kolejnych klatek animacji
 clock_t ostatniCzas,staryCzas;							//dane o up�ywie czasu mi�dzy zmian� klatki
 bool raz;												//czy animacja zosta�a wy�wietlona w ca�o�ci
 void WyzerujPozycje();									//zeruje pozycje tylko dla CONDITION_SCROOL
 void ZmienKlatke(void);								//w odpowiedniej chwili zmienia dane o kadrze klatki
														// w zale�ni�ci od typu animacji
};
// SCHEMAT jest potrzebny do zainicjowania ANIMACJI
struct SCHEMAT
{
 int* klatki;						
 DWORD flaga;
 int X,Y,Czas,poziom,ileklatek,predkosc,pozycja;	//te same dane co animacji
 SCHEMAT(int,int,int,int,int,DWORD);				//konstruktor(ile klatek,czas zmiany,kadrX,kadrY,poziomY,typ animacji)
 void Wartosci(int,...);							//uzupe�nia tablice klatek nie potrzebne dla SCROOL i CONDITION_SCROOL
};

// wa�na cz�� ca�ego silnika
class BITMAPA
{
 public:
 static LPDIRECTDRAWSURFACE7 bufor;						//wska�nik do bufora ekranu
 static void UchwytDoBuforaEkranu(LPDIRECTDRAWSURFACE7);//pobiera wska�nik do bufora ekranu
 BITMAPA();				
 SURFACE BMP;											//powierzchnia do rysowania
 ANIMACJA anim;											//animacja przypisana do bitmapy
 NAPIS nazwa_pliku;										//nazwa pliku bitmapy
 DWORD kolor_kluczowany;								//warto�� kluczowanego koloru
 bool sortowana;										//czy bitmapa jest sortowana
 bool animowana;										//czy jest animowana
 bool rysowana;											//czy ma by� wyswietlona
 void UstawKadr(int=0,int=0,int=0,int=0);
 int wysokosc,szerokosc,X,Y,ID;							//dane o po�o�eniu i ID potrzebne do sortowania
 int kx,ky,kx2,ky2;	
 void WczytajBMP(NAPIS,DWORD,bool);						//wczytuje bitmape z pliku(nazwa,kolor kluczowany,czy ma by� wczytana do tablicy sortowanych bitmap)
 void RysujBMP(int,int,bool);							//rysuje bitmape(x,y,wy�wiela� z kluczowaniem)
 void ZwolnijBMP();										//zwalnia bitmape
 void Koordynaty(int,int);								//zmienia po�o�enie (potrzebne do sortowanych bitmap)
 void Schemat(SCHEMAT);									//przypisuje SCHEMAT animacji do ANIMACJI BIMAPY
 //sortowane bmp
 static void SortujBMP(void);							//sortuje bitmapy z tablicy sortowanych wzgl�dem po�o�enia x i y
 static void RysujSortowaneBMP(void);					//rysuje bitmapy z tablicy sortowanych
 static BITMAPA sortowaneBMP[500];						//tablica sortowanych bitmap
 static int ile_bitmap;									//optymalizacja sortowania i rysowania
};