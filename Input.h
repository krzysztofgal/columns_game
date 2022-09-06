#include <Dinput.h>
#include <time.h>

struct MOUSESTATE
{
 MOUSESTATE();
 int x,y;
 BYTE b[4];
};

class DINPUT
{
 private:
 static LPDIRECTINPUT8 lpDI8;					//g��wny obiekt Direct Input
 static LPDIRECTINPUTDEVICE8 klawiatura;		//urz�dzenie DI
 static LPDIRECTINPUTDEVICE8 mysz;				// j/w
 static DIMOUSESTATE mouse_state;				//przesuni�cie myszy i stan guzik�w
 static unsigned char keystate[256];			//tablica klawiszy
 public:
 static clock_t ostatniCzasK,ostatniCzasM;
 static MOUSESTATE stan_myszy;					//po�o�enie myszy i stan guzik�w na podstawie DIMOUSESTATE
 static HINSTANCE hInstance;					//uczwyt do instancji programu
 static HWND Okno;								//uczwyt do okna programu
 static void Inicjuj(HINSTANCE,HWND);			//inicjuje lpDI8, klawiature i mysz
 static void SprawdzStan(void);					//aktualizuje DIMOUSESTATE i tablice klawiszy
 static bool KEYDOWN(int,int);						//sprawdza czy zosta� naci�ni�ty dany klawisz
 static bool ButtonDown(int,int);				//sprawdza czy zosta� naci�ni�ty dany guzik myszy
 static bool MouseOnPos(int,int,int,int);		//sprawdza czy mysz znajduje si� w odpowiednim kadrze
 static void Zwolnij(void);						//zwalnia obiekty DI
 static int MyszX(void){return stan_myszy.x;};
 static int MyszY(void){return stan_myszy.y;};
 static BYTE MyszB(void);
};