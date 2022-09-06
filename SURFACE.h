//podstawowa klasa niemal ca≥ego silnika
#include <DDraw.h>
#include <Windows.h>

class SURFACE
{
 public:
 SURFACE();
 static HWND okno;						//Uczwyt do okna programu
 static void UchwytOkna(HWND);			//pobiera uczwyt do okna i przypisuje na okno
 static LPDIRECTDRAW7 lpDD;				//wskaünik do g≥Ûwnego obiektu DD
 LPDIRECTDRAWSURFACE7 surface;			//powierzchnia do rysowania
 DDSURFACEDESC2 ddsd;					//opis powierzchni uzupe≥niany rÍcznie bez funkcji
 static void ObiektDD(LPDIRECTDRAW7);	//pobiera wskaünik do lpDD
 void UtworzPowierzchnie(void);			//tworzy powierzchnie
 void UstawKolorKeying(DWORD);			//ustawia kolorkeying
 void Zwolnij();						//zwalnia powierzchnie
 void Blur(int);
};