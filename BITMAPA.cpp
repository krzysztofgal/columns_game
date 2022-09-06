#include "BITMAPA.h"

BITMAPA BITMAPA::sortowaneBMP[500];
int BITMAPA::ile_bitmap=0;
LPDIRECTDRAWSURFACE7 BITMAPA::bufor=NULL;

//================================ANIMACJA==================================

ANIMACJA::ANIMACJA()
{
 flaga=0;
 klatka=ileklatek=Czas=0;
 X=Y=0;
 predkosc=pozycja=poziom=0;
 raz=true;
 staryCzas=GetTickCount();
};

void ANIMACJA::WyzerujPozycje()
{
if(raz)pozycja=0;
};

void ANIMACJA::ZmienKlatke(void)
{
 if(flaga==LOOP)
 {
  ostatniCzas=GetTickCount();
  if(ostatniCzas > staryCzas+Czas)klatka++,staryCzas=ostatniCzas;
  if(klatka==ileklatek)klatka=0;
 }
 if(flaga==CONDITION)
 {
  if(!raz)
  {
   ostatniCzas=GetTickCount();
   if(ostatniCzas > staryCzas+Czas)klatka++,staryCzas=ostatniCzas;
   if(klatka==ileklatek)klatka=0,raz=true;
  } 
 }
 if(flaga==SCROOL)
 {
  int rozm=ileklatek*X;
  ostatniCzas=GetTickCount();
  if(ostatniCzas > staryCzas+Czas)pozycja+=predkosc,staryCzas=ostatniCzas;
  if(pozycja+X>rozm)pozycja=0;
 }
 if(flaga==CONDITION_SCROOL)
 {
  if(!raz)
  {
   int rozm=ileklatek*X;
   ostatniCzas=GetTickCount();
   if(ostatniCzas > staryCzas+Czas)pozycja+=predkosc,staryCzas=ostatniCzas;
   if(pozycja+X>=rozm)raz=true;
  } 
 }
};
// SCHEMAT
SCHEMAT::SCHEMAT(int ile,int czas,int kadrX,int kadrY,int pozY,DWORD flag)
{
 klatki=new int[ile];
 ileklatek=ile;
 Czas=czas;
 poziom=pozY;
 X=kadrX;
 Y=kadrY;
 flaga=flag;
 predkosc=pozycja=0;
};

void SCHEMAT::Wartosci(int liczba,...)
{
 va_list arg;
 va_start(arg,liczba);
 klatki[0]=liczba;
 for(int i=1;i<=ileklatek;i++)
 {
  klatki[i]=va_arg(arg,int);
 }
 va_end(arg);
};

//=========================BITMAPA=========================================

BITMAPA::BITMAPA()
{
 X=Y=0;
 wysokosc=szerokosc=0;
 ID=0;
 kx=ky=kx2=ky2=0;
 animowana=false;
 rysowana=true;
};

void BITMAPA::UchwytDoBuforaEkranu(LPDIRECTDRAWSURFACE7 buf)
{
 bufor=buf;
};

void BITMAPA::WczytajBMP(NAPIS nazwa,DWORD kolor,bool czySortowana)
{
 nazwa_pliku=nazwa;
 kolor_kluczowany=kolor;
 HBITMAP hbmp;
 BITMAP bmp;
 HDC bmpDC;          
 HDC powDC;
 hbmp = (HBITMAP) LoadImage(NULL,nazwa.Text(),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 bmpDC = CreateCompatibleDC(NULL);
 SelectObject(bmpDC,hbmp);
 GetObject(hbmp,sizeof(bmp),&bmp);
 //nie sortowana
 if(!czySortowana)
 { 
  sortowana=false;
  BMP.ddsd.dwSize         = sizeof(BMP.ddsd);
  BMP.ddsd.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
  BMP.ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
  kx2=szerokosc=BMP.ddsd.dwWidth=bmp.bmWidth;
  ky2=wysokosc=BMP.ddsd.dwHeight=bmp.bmHeight;
  BMP.UtworzPowierzchnie();
  if(BMP.surface->GetDC(&powDC) == DD_OK)
  {
   BitBlt(powDC, 0, 0, bmp.bmWidth, bmp.bmHeight, bmpDC, 0, 0, SRCCOPY);
   BMP.surface->ReleaseDC(powDC);
   BMP.UstawKolorKeying(kolor);
  }
 }
 //sortowana
 if(czySortowana)
 {
  sortowana=true;
  sortowaneBMP[ile_bitmap].BMP.ddsd.dwSize         = sizeof(sortowaneBMP[ile_bitmap].BMP.ddsd);
  sortowaneBMP[ile_bitmap].BMP.ddsd.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
  sortowaneBMP[ile_bitmap].BMP.ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
  sortowaneBMP[ile_bitmap].kx2=sortowaneBMP[ile_bitmap].szerokosc=sortowaneBMP[ile_bitmap].BMP.ddsd.dwWidth=bmp.bmWidth;
  sortowaneBMP[ile_bitmap].ky2=sortowaneBMP[ile_bitmap].wysokosc=sortowaneBMP[ile_bitmap].BMP.ddsd.dwHeight=bmp.bmHeight;
  sortowaneBMP[ile_bitmap].BMP.UtworzPowierzchnie();
  if(sortowaneBMP[ile_bitmap].BMP.surface->GetDC(&powDC) == DD_OK)
  {
   BitBlt(powDC, 0, 0, bmp.bmWidth, bmp.bmHeight, bmpDC, 0, 0, SRCCOPY);
   sortowaneBMP[ile_bitmap].BMP.surface->ReleaseDC(powDC);
   sortowaneBMP[ile_bitmap].BMP.UstawKolorKeying(kolor);
  }
  ID=ile_bitmap;
  sortowaneBMP[ile_bitmap].ID=ile_bitmap;
  ile_bitmap++;
 }
 DeleteDC(bmpDC);
 DeleteObject(hbmp);
};

void BITMAPA::ZwolnijBMP()
{
 BMP.Zwolnij();
 wysokosc=szerokosc=0;
 X=Y=0;
 ID=0;
};

void BITMAPA::Koordynaty(int kx,int ky)
{
 if(sortowana)
 {
  for(int i=0;i<ile_bitmap;i++)
  {
   if(sortowaneBMP[i].ID==ID)sortowaneBMP[i].X=kx,sortowaneBMP[i].Y=ky;
  }
 }
 else 
 {
  X=kx;
  Y=ky;
 }
};

void BITMAPA::RysujBMP(int x,int y,bool kluczowanie)
{
 X=x;
 Y=y;
 if(animowana)
 {
  RECT kadr;
  anim.ZmienKlatke();
  RECT ob={x,y,x+anim.X-1,y+anim.Y-1};
  if(anim.flaga!=SCROOL && anim.flaga!=CONDITION_SCROOL)
  {
   kadr.left=anim.X*anim.klatki[anim.klatka];
   kadr.right=anim.X*anim.klatki[anim.klatka]+anim.X;
   kadr.top=anim.poziom*anim.Y;
   kadr.bottom=anim.poziom*anim.Y+anim.Y;
  }
  else
  {
   kadr.left=anim.pozycja;
   kadr.right=anim.pozycja+anim.X;
   kadr.top=anim.poziom*anim.Y;
   kadr.bottom=anim.poziom*anim.Y+anim.Y;
  }
  if(rysowana)bufor->Blt(&ob,BMP.surface,&kadr,DDBLT_WAIT | (kluczowanie*DDBLT_KEYSRC),NULL);
 }
 else
 {
  RECT kadr={kx,ky,kx2,ky2};
  RECT ob={x,y,x+kx2-kx-1,y+ky2-ky-1};
  if(rysowana)bufor->Blt(&ob,BMP.surface,&kadr,DDBLT_WAIT | (kluczowanie*DDBLT_KEYSRC),NULL);
 }
};

void BITMAPA::UstawKadr(int x,int y,int x2,int y2)
{
 if(x2<1 || x2>szerokosc)kx2=szerokosc;else kx2=x2;
 if(y2<1 || y2>wysokosc)ky2=wysokosc;else ky2=y2;
 if(x<0 || x>szerokosc)kx=0;else kx=x;
 if(y<0 || y>wysokosc)ky=0;else ky=y;
};

void BITMAPA::Schemat(SCHEMAT sch)
{
 if(sortowana)
 {
  for(int i=0;i<ile_bitmap;i++)
  {
   if(sortowaneBMP[i].ID==ID)
   {
    sortowaneBMP[i].animowana=true;
	sortowaneBMP[i].anim.Czas=sch.Czas;
	sortowaneBMP[i].anim.flaga=sch.flaga;
	sortowaneBMP[i].anim.ileklatek=sch.ileklatek;
	sortowaneBMP[i].anim.klatki=new int[sortowaneBMP[i].anim.ileklatek];
	sortowaneBMP[i].anim.klatki=sch.klatki;
	sortowaneBMP[i].anim.poziom=sch.poziom;
	sortowaneBMP[i].anim.pozycja=sch.pozycja;
	sortowaneBMP[i].anim.predkosc=sch.predkosc;
	sortowaneBMP[i].anim.X=sch.X;
	sortowaneBMP[i].anim.Y=sch.Y;
   }
  }
 }
 else
 {
  animowana=true;
  anim.Czas=sch.Czas;
  anim.flaga=sch.flaga;
  anim.ileklatek=sch.ileklatek;
  anim.klatki=new int[anim.ileklatek];
  anim.klatki=sch.klatki;
  anim.poziom=sch.poziom;
  anim.pozycja=sch.pozycja;
  anim.predkosc=sch.predkosc;
  anim.X=sch.X;
  anim.Y=sch.Y;
 }
};

//sortowanie bmp;
int porownajX(const void *arg1, const void *arg2)
{
 BITMAPA *Arg1 = (BITMAPA *)arg1;
 BITMAPA *Arg2 = (BITMAPA *)arg2;
 return (Arg2->X <= Arg1->X);
};

int porownajY(const void *arg1, const void *arg2)
{
 BITMAPA *Arg1 = (BITMAPA *)arg1;
 BITMAPA *Arg2 = (BITMAPA *)arg2;
 return (Arg2->Y <= Arg1->Y);
};

void BITMAPA::SortujBMP(void)
{
 qsort(sortowaneBMP,ile_bitmap,sizeof(BITMAPA),porownajX);
 qsort(sortowaneBMP,ile_bitmap,sizeof(BITMAPA),porownajY);
};

void BITMAPA::RysujSortowaneBMP(void)
{
 for(int j=0;j<ile_bitmap;j++)
 {
  sortowaneBMP[j].RysujBMP(sortowaneBMP[j].X,sortowaneBMP[j].Y,true);
 }
};