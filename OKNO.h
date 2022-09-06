#include <Windows.h>

class OKNO
{
 HWND hOkno;										//uczwyt okna programu
 WNDCLASS wd;										//klasa okna
 HINSTANCE hInstance;								//instancja programu
 public:
 static bool koniecProgramu;										
 void UtworzKlaseOkna(HINSTANCE,WNDPROC);			//tworzy klase okna odpowiedni� dla DD(instancja programu,petla komunikat�w) 
 void UtworzOkno(LPCSTR,unsigned int,unsigned int);	//tworzy okno na podstawie klasy
 HWND ZwrocUchwytOkna(void);						//zwraca hOkno
 static void Wiadomosc(HWND,LPSTR);					//wy�wietla wiadomo�� w stylu MB_OK
 static void Petla(void(*funkcja)(void));			//petla g��wna programu pobiera wska�nik do innej funkcji (wygodne)
 void ZniszczOkno();								//niszczy okno
 OKNO();
};