#include "source.h"

Button::Button()
{
 aktywny=false;
 x=y=0;
 dostepny=true;
};

void Button::Pozycja(int xx,int yy)
{
 x=xx;
 y=yy;
};

void Button::ZmienStan(void)
{
 if(dostepny)
 {
  if(aktywny)aktywny=false;else aktywny=true;
 }
};

void Button::Rysuj(int nx,int ny,NAPIS tekst,DWORD kolor)
{
 ob.RysujBMP(x,y,true);
 EKRAN::PutText(tekst,x+nx,y+ny,kolor);
};

void PLANSZA::inicjuj(int x,int y)//inicjowanie planszy
{
 wysokosc=y+3;//+3 bo potrzeba jeszcza miejsca na wylosowanie klocka
 szerokosc=x+2;//trzeba jeszcze œciany
 plansza=new KLOCEK[wysokosc*szerokosc];//dynamiczne przydzielenie pamiêci pod tablice kolorów
 kopiaPlanszy=new KLOCEK[wysokosc*szerokosc];//kopia tablicy potrzebna do kasowania
 //przygotowanie planszy do grania
 for(int i=0;i<wysokosc*szerokosc;i++)plansza[i].kolor=-1,plansza[i].sterowany=false;
 for(int r=0;r<wysokosc;r++)plansza[r*szerokosc-1].kolor=0;
 for(int l=0;l<wysokosc;l++)plansza[l*szerokosc].kolor=0;
 for(int d=wysokosc*szerokosc-szerokosc;d<wysokosc*szerokosc;d++)plansza[d].kolor=0;
 for(int k=0;k<wysokosc*szerokosc;k++)kopiaPlanszy[k].kolor=plansza[k].kolor;
 losujKlocka();//wylosowanie pierwszego klocka
 ostatniCzas=GetTickCount();
 predkosc=250;//predkoœc opadania w ms
 zestaw.WczytajBMP("default.bmp",0x000000,false);//wczytanie bitmapy zawieraj¹cej klocki
 pauza=false;
 trwaGra=true;
 gameOver=false;
 punkty=0;
 level=1;
};

void PLANSZA::losujKlocka(void)
{
 if(!gameOver)
 {
  pozycja=5;
  for(int i=0;i<3;i++)
  {
   kol=rand()%5;
   if(kol==0)plansza[i*szerokosc+pozycja].kolor=1;
   if(kol==1)plansza[i*szerokosc+pozycja].kolor=2;
   if(kol==2)plansza[i*szerokosc+pozycja].kolor=3;
   if(kol==3)plansza[i*szerokosc+pozycja].kolor=4;
   if(kol==4)plansza[i*szerokosc+pozycja].kolor=5;
   plansza[i*szerokosc+pozycja].sterowany=true;
  }
 }//gameOver 
};

void PLANSZA::opuscWDol()//dla klocków nie sterowanych
{
 for(int p=0;p<wysokosc;p++)
 {
  for(int i=wysokosc*szerokosc-szerokosc;i>1;i--)
  {
   if(plansza[i-szerokosc].kolor>0 && !plansza[i-szerokosc].sterowany && plansza[i].kolor==-1)
   {
    plansza[i].kolor=plansza[i-szerokosc].kolor;
    plansza[i-szerokosc].kolor=-1;  
   }
  }
 }//for p
};

void PLANSZA::opuscWDolKlocka()//dla sterowanego klocka
{
 for(int i=wysokosc*szerokosc-(2*szerokosc);i>0;i--)
 {
  if(plansza[i].kolor>0 && plansza[i+szerokosc].kolor<0 && plansza[i].sterowany)
  {
   plansza[i+szerokosc].kolor=plansza[i].kolor;
   plansza[i].kolor=-1;
   plansza[i+szerokosc].sterowany=true,plansza[i].sterowany=false;
  }
 }
};

void PLANSZA::przesunKlocka()
{
 if(DINPUT::KEYDOWN(DIK_UP,150))przesunKolory();
 if(DINPUT::KEYDOWN(DIK_DOWN,0))predkosc_tmp=predkosc%2;else predkosc_tmp=predkosc;
 
 if(DINPUT::KEYDOWN(DIK_LEFT,50) && left==3)
 {
  for(int l=1;l<wysokosc*szerokosc-szerokosc;l++)
  {
   if(plansza[l].sterowany)
   {
    plansza[l-1].kolor=plansza[l].kolor;
    plansza[l-1].sterowany=true;
    plansza[l].sterowany=false;
    plansza[l].kolor=-1;
   }
  }
 }
 if(DINPUT::KEYDOWN(DIK_RIGHT,50) && right==3)
 {
  for(int r=wysokosc*szerokosc-szerokosc;r>0;r--)
  {
   if(plansza[r].sterowany)
   {
    plansza[r+1].kolor=plansza[r].kolor;
    plansza[r+1].sterowany=true;
    plansza[r].sterowany=false;
    plansza[r].kolor=-1;
   }
  }
 }
};

void PLANSZA::kasuj()
{
 for(int k=0;k<wysokosc*szerokosc;k++)kopiaPlanszy[k].kolor=plansza[k].kolor;
 for(int i=1;i<wysokosc*szerokosc-szerokosc;i++)//etap 1: znaleŸæ trójke
 {
  if(plansza[i].kolor>0 && !plansza[i].sterowany)
  {
   if(plansza[i].kolor==plansza[i+1].kolor && plansza[i+1].kolor==plansza[i+2].kolor)
   {
    if(plansza[i].kolor==1)for(int r=i;r<i+3;r++)kopiaPlanszy[r].kolor=11,kolor=11;
    if(plansza[i].kolor==2)for(int n=i;n<i+3;n++)kopiaPlanszy[n].kolor=12,kolor=12;
    if(plansza[i].kolor==3)for(int z=i;z<i+3;z++)kopiaPlanszy[z].kolor=13,kolor=13;
    if(plansza[i].kolor==4)for(int z=i;z<i+3;z++)kopiaPlanszy[z].kolor=14,kolor=14;
    if(plansza[i].kolor==5)for(int z=i;z<i+3;z++)kopiaPlanszy[z].kolor=15,kolor=15;
    punkty+=30+level;
	kasowane=true;   
	break;
   }//if 3 poziomo
   if(plansza[i].kolor==plansza[i+szerokosc].kolor && plansza[i+szerokosc].kolor==plansza[i+2*szerokosc].kolor)
   {
    if(plansza[i].kolor==1)for(int r=i;r<i+3*szerokosc;r+=szerokosc)kopiaPlanszy[r].kolor=11,kolor=11;
    if(plansza[i].kolor==2)for(int n=i;n<i+3*szerokosc;n+=szerokosc)kopiaPlanszy[n].kolor=12,kolor=12;
    if(plansza[i].kolor==3)for(int z=i;z<i+3*szerokosc;z+=szerokosc)kopiaPlanszy[z].kolor=13,kolor=13;
    if(plansza[i].kolor==4)for(int z=i;z<i+3*szerokosc;z+=szerokosc)kopiaPlanszy[z].kolor=14,kolor=14;
    if(plansza[i].kolor==5)for(int z=i;z<i+3*szerokosc;z+=szerokosc)kopiaPlanszy[z].kolor=15,kolor=15;
    punkty+=30+level;
    kasowane=true;
    break;
   }//if 3 pionowo
  }//if
 }//for
//etap 2 poszukiwanie ko³o trójek i oznaczanie
 while(kasowane)
 {
  for(int i=1;i<wysokosc*szerokosc-szerokosc;i++)
  {
    if(kopiaPlanszy[i].kolor==kolor)
    {
     if(kopiaPlanszy[i-1].kolor==(kolor-10))kopiaPlanszy[i-1].kolor=kolor,punkty+50+level,kasowane=true;else kasowane=false;
     if(kopiaPlanszy[i+1].kolor==(kolor-10))kopiaPlanszy[i+1].kolor=kolor,punkty+=50+level,kasowane=true;else kasowane=false;
     if(kopiaPlanszy[i-szerokosc].kolor==(kolor-10))kopiaPlanszy[i-szerokosc].kolor=kolor,punkty+50+level,kasowane=true;else kasowane=false;
     if(kopiaPlanszy[i+szerokosc].kolor==(kolor-10))kopiaPlanszy[i+szerokosc].kolor=kolor,punkty+50+level,kasowane=true;else kasowane=false;
 }//while
}
}
 for(int k=0;k<wysokosc*szerokosc;k++)plansza[k].kolor=kopiaPlanszy[k].kolor;
};//end kasuj


void PLANSZA::rysuj(void)
{
 trwaGra=true;
 for(int i=3;i<wysokosc;i++)
  for(int j=0;j<szerokosc;j++)
  {
   if(plansza[i*szerokosc+j].kolor!=-1)
   {
    if(plansza[i*szerokosc+j].kolor==0)zestaw.UstawKadr(0,160,32,192);
    if(plansza[i*szerokosc+j].kolor==1)zestaw.UstawKadr(0,0,32,32);
    if(plansza[i*szerokosc+j].kolor==2)zestaw.UstawKadr(0,32,32,64);
    if(plansza[i*szerokosc+j].kolor==3)zestaw.UstawKadr(0,64,32,96);
    if(plansza[i*szerokosc+j].kolor==4)zestaw.UstawKadr(0,96,32,128);
    if(plansza[i*szerokosc+j].kolor==5)zestaw.UstawKadr(0,128,32,160);
    if(plansza[i*szerokosc+j].kolor==11)zestaw.UstawKadr(32,0,64,32),pauza=true;
    if(plansza[i*szerokosc+j].kolor==12)zestaw.UstawKadr(32,32,64,64),pauza=true;
    if(plansza[i*szerokosc+j].kolor==13)zestaw.UstawKadr(32,64,64,96),pauza=true;
    if(plansza[i*szerokosc+j].kolor==14)zestaw.UstawKadr(32,96,64,128),pauza=true;
    if(plansza[i*szerokosc+j].kolor==15)zestaw.UstawKadr(32,128,64,160),pauza=true;
    zestaw.RysujBMP(j*31+200,i*31,true);
   }
  }
  EKRAN::PutText("PUNKTY:",5,10,0x00Ff00);
  EKRAN::PutText(punkty,100,10,0x00FF00);
  EKRAN::PutText("LEVEL:",5,50,0x00FF00);
  EKRAN::PutText(level,100,50,0x00FF00);
 if(GetTickCount()-czasAnim>300 && pauza)
 {
  pauza=false;
  czasAnim=GetTickCount();
  //kasowania etap ostatni rysowanie a nastepnie usuwanie
  for(int d=1;d<wysokosc*szerokosc;d++)if(plansza[d].kolor>10)plansza[d].kolor=-1;
  opuscWDol();
  kasuj();
 }
};


void PLANSZA::skanuj(void)//g³ówna funkcja programu
{ 
 rysuj();//rysowanie
 for(int g=1;g<4*szerokosc;g++)//sprawdzam czy jakiœ klocek nie wyszed³ poza obszar gry
 {
  if(!plansza[g].sterowany && plansza[g].kolor>0)gameOver=true,trwaGra=false;
 }
 if(!pauza)//pauza jest po to aby odpowiednio zsynchronizowaæ wyœwietlanie z kasowaniem
 {
  left=right=0;//te zmienne musza przyj¹æ wartoœæ 3 aby mo¿na by³o przesun¹æ klocek na boki
  for(int i=wysokosc*szerokosc;i>0;i--)
  {
   if(plansza[i].sterowany)
   {
    if(plansza[i-1].kolor==-1)left++;
    if(plansza[i+1].kolor==-1)right++;
    if(plansza[i+szerokosc].kolor!=-1 && !plansza[i+szerokosc].sterowany)//jeœli klocek opadnie na inne klocki
    {
     plansza[i].sterowany=plansza[i-szerokosc].sterowany=plansza[i-2*szerokosc].sterowany=false;//to ju¿ nim nie sterujemy
     kasuj();//a potem sprawdzamy czy s¹ jakieœ klocki do kasowania
     losujKlocka();//nastêpnie losujemy nowego klocka
     czasAnim=GetTickCount();//pobieramy czas do synchronizacji rysowania
    }
    else //jeœli klocek opada
    {
     obecnyCzas=GetTickCount();
     if(obecnyCzas-ostatniCzas > predkosc_tmp)
     {
      ostatniCzas=GetTickCount();
      opuscWDolKlocka();//po okreslonym czasie opuszczamy klocka o jedno pole w dó³
     }
    }
   } 
  }
  przesunKlocka();//funkcja sprawdza czy chcemy manipulowaæ klockiem
 }//pauza
 if(punkty>(500*level))
 {
  level++;
  if(predkosc>80)predkosc-=int(level/2);//to powoduje ¿e z ka¿dym levelem klocek opada szybciej
 }
};//END skanuj

void PLANSZA::przesunKolory(void)//zmienia kolejnoœæ kolorów na sterowanym klocku
{
 KLOCEK tmp[3];
 KLOCEK tmp2[3];
 int miejsce=0;
 for(int i=1;i<wysokosc*szerokosc-szerokosc;i++)
 {
  if(plansza[i].sterowany)
  {
   tmp[miejsce].kolor=plansza[i].kolor;
   miejsce++;
  }
 }
 tmp2[2]=tmp[0];
 tmp2[1]=tmp[2];
 tmp2[0]=tmp[1];
 miejsce=0;
 for(int j=1;j<wysokosc*szerokosc-szerokosc;j++)
 {
  if(plansza[j].sterowany)
  {
   plansza[j].kolor=tmp2[miejsce].kolor;
   miejsce++;
  }
 }
}