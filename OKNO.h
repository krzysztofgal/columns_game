#include <Windows.h>

class OKNO
{
 HWND hOkno;										//uczwyt okna programu
 WNDCLASS wd;										//klasa okna
 HINSTANCE hInstance;								//instancja programu
 public:
 static bool koniecProgramu;										
 void UtworzKlaseOkna(HINSTANCE,WNDPROC);			//tworzy klase okna odpowiedni¹ dla DD(instancja programu,petla komunikatów) 
 void UtworzOkno(LPCSTR,unsigned int,unsigned int);	//tworzy okno na podstawie klasy
 HWND ZwrocUchwytOkna(void);						//zwraca hOkno
 static void Wiadomosc(HWND,LPSTR);					//wyœwietla wiadomoœæ w stylu MB_OK
 static void Petla(void(*funkcja)(void));			//petla g³ówna programu pobiera wskaŸnik do innej funkcji (wygodne)
 void ZniszczOkno();								//niszczy okno
 OKNO();
};