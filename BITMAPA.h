//dziêki sortowaniu bitmap klasa BITMAPA jest odpowidnio przygotowana do silnika izometrycznego
#include "SURFACE.h"
#include <time.h>
#include <stdlib.h>
#include "CNapis.h"
#include "Flagi.h"

// ANIMACJA jest czêœci¹ bitmapy nie wystepuje samodzielnie
struct ANIMACJA
{
 ANIMACJA();
 int* klatki;											//wartoœci tablicy klatek
 DWORD flaga;											//typ animacji
 int klatka,Czas,X,Y,ileklatek,predkosc,pozycja,poziom;	//dane do przeliczania kolejnych klatek animacji
 clock_t ostatniCzas,staryCzas;							//dane o up³ywie czasu miêdzy zmian¹ klatki
 bool raz;												//czy animacja zosta³a wyœwietlona w ca³oœci
 void WyzerujPozycje();									//zeruje pozycje tylko dla CONDITION_SCROOL
 void ZmienKlatke(void);								//w odpowiedniej chwili zmienia dane o kadrze klatki
														// w zale¿niœci od typu animacji
};
// SCHEMAT jest potrzebny do zainicjowania ANIMACJI
struct SCHEMAT
{
 int* klatki;						
 DWORD flaga;
 int X,Y,Czas,poziom,ileklatek,predkosc,pozycja;	//te same dane co animacji
 SCHEMAT(int,int,int,int,int,DWORD);				//konstruktor(ile klatek,czas zmiany,kadrX,kadrY,poziomY,typ animacji)
 void Wartosci(int,...);							//uzupe³nia tablice klatek nie potrzebne dla SCROOL i CONDITION_SCROOL
};

// wa¿na czêœæ ca³ego silnika
class BITMAPA
{
 public:
 static LPDIRECTDRAWSURFACE7 bufor;						//wskaŸnik do bufora ekranu
 static void UchwytDoBuforaEkranu(LPDIRECTDRAWSURFACE7);//pobiera wskaŸnik do bufora ekranu
 BITMAPA();				
 SURFACE BMP;											//powierzchnia do rysowania
 ANIMACJA anim;											//animacja przypisana do bitmapy
 NAPIS nazwa_pliku;										//nazwa pliku bitmapy
 DWORD kolor_kluczowany;								//wartoœæ kluczowanego koloru
 bool sortowana;										//czy bitmapa jest sortowana
 bool animowana;										//czy jest animowana
 bool rysowana;											//czy ma byæ wyswietlona
 void UstawKadr(int=0,int=0,int=0,int=0);
 int wysokosc,szerokosc,X,Y,ID;							//dane o po³o¿eniu i ID potrzebne do sortowania
 int kx,ky,kx2,ky2;	
 void WczytajBMP(NAPIS,DWORD,bool);						//wczytuje bitmape z pliku(nazwa,kolor kluczowany,czy ma byæ wczytana do tablicy sortowanych bitmap)
 void RysujBMP(int,int,bool);							//rysuje bitmape(x,y,wyœwielaæ z kluczowaniem)
 void ZwolnijBMP();										//zwalnia bitmape
 void Koordynaty(int,int);								//zmienia po³o¿enie (potrzebne do sortowanych bitmap)
 void Schemat(SCHEMAT);									//przypisuje SCHEMAT animacji do ANIMACJI BIMAPY
 //sortowane bmp
 static void SortujBMP(void);							//sortuje bitmapy z tablicy sortowanych wzglêdem po³o¿enia x i y
 static void RysujSortowaneBMP(void);					//rysuje bitmapy z tablicy sortowanych
 static BITMAPA sortowaneBMP[500];						//tablica sortowanych bitmap
 static int ile_bitmap;									//optymalizacja sortowania i rysowania
};