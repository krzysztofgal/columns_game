#include <windows.h>
#include "OKNO.h"
//#include "EKRAN.h"
#include "source.h"

OKNO okno;
EKRAN ekran; 
PLANSZA plansza;
Button graj,wyjdz,gra,powroc;
BITMAPA kursor,title,tlo,gameOver;
SCHEMAT but(4,150,35,40,0,LOOP);//shematy animacji dla guzik�w i kursora
SCHEMAT but2(4,150,35,40,1,LOOP);
SCHEMAT kur(4,300,20,20,0,LOOP);
void Core(void);
void Menu(void);
void GameOver(void);
 
int WINAPI WinMain(HINSTANCE program, HINSTANCE, LPSTR, int)
{
 but.Wartosci(0,1,2,3);//uzupe�nianie schemat�w warto�ciami poszczeg�lnych klatek
 but2.Wartosci(0,1,2,3);
 kur.Wartosci(0,1,2,1);
 //inicjalizacja okna pod DDraw
 okno.UtworzKlaseOkna(program,DefWindowProc);
 okno.UtworzOkno("COLUMNS by KG",800,600);
 SURFACE::UchwytOkna(okno.ZwrocUchwytOkna());
 ekran.Inicjuj(okno.ZwrocUchwytOkna(),800,600,32);
 DINPUT::Inicjuj(program,okno.ZwrocUchwytOkna());
 //wczytanie Bitmap dla guzik�w, napis�w i t�a
 graj.ob.WczytajBMP("BUTTON.bmp",0,false);
 gra.ob.WczytajBMP("BUTTON.bmp",0,false);
 powroc.ob.WczytajBMP("BUTTON.bmp",0,false);
 wyjdz.ob.WczytajBMP("BUTTON.bmp",0,false);
 kursor.WczytajBMP("kursor.bmp",0,false);
 title.WczytajBMP("Title.bmp",0,false);
 tlo.WczytajBMP("t�o.bmp",0,false);
 gameOver.WczytajBMP("gameOver.bmp",0,false);
 //pozycje guzik�w 
 wyjdz.Pozycja(20,500);
 gra.Pozycja(20,200);
 powroc.Pozycja(300,300);
 graj.Pozycja(300,200);
 kursor.Schemat(kur);
 powroc.ob.Schemat(but);
 graj.ob.Schemat(but);
 //
 OKNO::Petla(Core);//g��wna p�tla programu pobiera wska�nik do funkcji typu void f(void)
 //ko�czenie pracy programu
 DINPUT::Zwolnij();
 ekran.Zwolnij();
 return 0;
}

void Core(void)
{ 
 DINPUT::SprawdzStan();//sprawdzenie stanu klawiszy i myszy
 ekran.CzyscEkran(0x000000);//czyszczenie ekranu na czarno
 tlo.RysujBMP(0,0,false);	//rysowanie t�a
 //dzi�ki programowaniu obiektowemu tak wygl�da podstawowy algorytm gry
 if(graj.aktywny || powroc.aktywny)
 {
  plansza.skanuj();
  if(DINPUT::KEYDOWN(DIK_ESCAPE,0))graj.aktywny=false,powroc.aktywny=false; 
 }else Menu();
 if(plansza.gameOver)GameOver(); 
 //tu si� ko�czy 
 ekran.OdwrocBufory();//potrzebne do podw�jnego buforowania
 if(wyjdz.aktywny)OKNO::koniecProgramu=true;//czy program ma by� zako�czony
};

void Menu(void)//menu g��wne
{
 title.RysujBMP(230+rand()%5,10+rand()%5,true);//rysowanie logo gry
 if(DINPUT::MouseOnPos(gra.x,gra.y,gra.x+100,gra.y+50))//je�li najedziesz kursorem na miejsce
 {													   //podane jako parametry to guzik zmienia schemat animacji
  gra.ob.Schemat(but2);
  if(DINPUT::ButtonDown(0,300))gra.ZmienStan();
 }else gra.ob.Schemat(but);
 if(DINPUT::MouseOnPos(wyjdz.x,wyjdz.y,wyjdz.x+100,wyjdz.y+50))
 {
  wyjdz.ob.Schemat(but);
  if(DINPUT::ButtonDown(0,300))wyjdz.ZmienStan();
 }else wyjdz.ob.Schemat(but2);
 if(gra.aktywny)
 {  
  graj.Rysuj(40,5,"Nowa Gra",0x00FF00);
  if(DINPUT::MouseOnPos(graj.x,graj.y,graj.x+100,graj.y+50))
  {
  graj.ob.Schemat(but2);
  if(DINPUT::ButtonDown(0,300))
  {
  graj.ZmienStan();
  plansza.inicjuj(10,15);
  plansza.losujKlocka();
  }
  }else graj.ob.Schemat(but);  
  if(plansza.trwaGra)powroc.Rysuj(40,5,"Powr�t do gry",0x00FF00);else powroc.Rysuj(40,5,"Powr�t do gry",0x999999);
  if(DINPUT::MouseOnPos(powroc.x,powroc.y,powroc.x+100,powroc.y+50) && plansza.trwaGra)
  {
   powroc.ob.Schemat(but2);
   if(DINPUT::ButtonDown(0,300))powroc.ZmienStan();
  }else powroc.ob.Schemat(but);
 }
 gra.Rysuj(40,5,"GRA",0x00FF00);
 wyjdz.Rysuj(40,5,"WYJD�",0x00FF00);
 kursor.RysujBMP(DINPUT::MyszX(),DINPUT::MyszY(),true);
 EKRAN::PutText("Made by Ga� Krzysztof",10,580,0x00FF00);
};

void GameOver(void)
{
 gameOver.RysujBMP(150+rand()%10,200+rand()%10,true);
 EKRAN::PutText("Punkty:",200,400,0x00FF00);
 EKRAN::PutText(plansza.punkty,300,400,0x00FF00);
 EKRAN::PutText("Level:",400,400,0x00FF00);
 EKRAN::PutText(plansza.level,500,400,0x00FF00);
 if(DINPUT::KEYDOWN(DIK_ESCAPE,0))graj.aktywny=false,powroc.aktywny=false,plansza.gameOver=false;
};