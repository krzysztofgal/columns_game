#include "BITMAPA.h"
#include <math.h>

class EKRAN
{
 public:
 static SURFACE ekran,bufor;				//powiezrzchnia g≥Ûwna i bufor ekranu
 LPDIRECTDRAWCLIPPER lpDDC;					//clipper	
 DDBLTFX ddbltfx;							//opis efektu do czyszczenia ekranu na jeden kolor
 static LPDIRECTDRAW DDraw;					//g≥Ûwny obiekt DD tylko do inicjowania
 static LPDIRECTDRAW7 DDraw7;				//j/w tylko øe uøywany
 static HWND Okno;							//uczwyt do okna programu
 static HDC hdc;							//kontekst ekranu potrzebny do SetPixel
 static double Kats[360];					//tablica wartosci cosinus
 static double Katc[360];					// j/w sinus
 void Inicjuj(HWND,int,int,int);			//inicjowanie DD (okno,wys,szer,bpp)
 void OdwrocBufory(void);					//zamienia wskaüniki ekranu z buforem
 void CzyscEkran(DWORD);					//czyúci ekran na wybrany kolor
 void Zwolnij(void);						//zwalnia powierzchnie i obiekty DD
 static void PutPix(int,int,DWORD);			//wyúwietla punkt na ekranie(x,y,kolor)
 static void PutCircle(int,int,int,DWORD);	//rysuje ko≥o(x,y,r,kolor)
 static void PutLine(int,int,int,int,DWORD);//do napisania
 static void PutText(NAPIS,int,int,DWORD);
 EKRAN();
};