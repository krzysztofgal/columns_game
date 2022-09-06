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
 static LPDIRECTINPUT8 lpDI8;					//g³ówny obiekt Direct Input
 static LPDIRECTINPUTDEVICE8 klawiatura;		//urz¹dzenie DI
 static LPDIRECTINPUTDEVICE8 mysz;				// j/w
 static DIMOUSESTATE mouse_state;				//przesuniêcie myszy i stan guzików
 static unsigned char keystate[256];			//tablica klawiszy
 public:
 static clock_t ostatniCzasK,ostatniCzasM;
 static MOUSESTATE stan_myszy;					//po³o¿enie myszy i stan guzików na podstawie DIMOUSESTATE
 static HINSTANCE hInstance;					//uczwyt do instancji programu
 static HWND Okno;								//uczwyt do okna programu
 static void Inicjuj(HINSTANCE,HWND);			//inicjuje lpDI8, klawiature i mysz
 static void SprawdzStan(void);					//aktualizuje DIMOUSESTATE i tablice klawiszy
 static bool KEYDOWN(int,int);						//sprawdza czy zosta³ naciœniêty dany klawisz
 static bool ButtonDown(int,int);				//sprawdza czy zosta³ naciœniêty dany guzik myszy
 static bool MouseOnPos(int,int,int,int);		//sprawdza czy mysz znajduje siê w odpowiednim kadrze
 static void Zwolnij(void);						//zwalnia obiekty DI
 static int MyszX(void){return stan_myszy.x;};
 static int MyszY(void){return stan_myszy.y;};
 static BYTE MyszB(void);
};