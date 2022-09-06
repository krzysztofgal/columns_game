#include "EKRAN.h"
#include <DDraw.h>
#include "OKNO.h"

LPDIRECTDRAW EKRAN::DDraw=NULL;
LPDIRECTDRAW7 EKRAN::DDraw7=NULL;
SURFACE EKRAN::ekran;
SURFACE EKRAN::bufor;
HWND EKRAN::Okno=NULL;
HDC EKRAN::hdc;
double EKRAN::Katc[360];
double EKRAN::Kats[360];

EKRAN::EKRAN()
{
 lpDDC=NULL;
 int j=0;
 for(double i=0;i<360;i++)
 {
  Kats[j]=sin(i);
  Katc[j]=cos(i);
  j++;
 }
};

void EKRAN::Inicjuj(HWND okno,int x,int y,int bpp)
{
 Okno=okno;
 DirectDrawCreate(NULL,&DDraw,NULL);
 DDraw->QueryInterface(IID_IDirectDraw7,(LPVOID *)&DDraw7);
 DDraw7->SetCooperativeLevel(okno, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
 DDraw7->SetDisplayMode(x,y,bpp,0,0);
 DDraw7->CreateClipper(0,&lpDDC,NULL);
 SURFACE::ObiektDD(DDraw7);
 ekran.ddsd.dwWidth=x;
 ekran.ddsd.dwHeight=y;
 ekran.ddsd.dwFlags=DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
 ekran.ddsd.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP; 
 ekran.ddsd.dwBackBufferCount=1;
 ekran.ddsd.dwSize=sizeof(ekran.ddsd);
 ekran.UtworzPowierzchnie();
 bufor.ddsd.dwSize=sizeof( bufor.ddsd );
 bufor.ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH ;
 bufor.ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN;
 bufor.UtworzPowierzchnie();
 bufor.ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
 ekran.surface->GetAttachedSurface(&bufor.ddsd.ddsCaps,&bufor.surface);
 lpDDC->SetHWnd(0,okno);
 bufor.surface->SetClipper(lpDDC);
 BITMAPA::UchwytDoBuforaEkranu(bufor.surface);
 memset(&ddbltfx,0,sizeof(ddbltfx));
 ddbltfx.dwSize=sizeof(ddbltfx);
};

void EKRAN::Zwolnij(void)
{
 bufor.surface->SetClipper(NULL);
 bufor.Zwolnij();
 ekran.Zwolnij();
 DDraw7->RestoreDisplayMode();
 DDraw7->SetCooperativeLevel(Okno,DDSCL_NORMAL);
 DDraw7->Release();
 DDraw->Release();
};

void EKRAN::CzyscEkran(DWORD kolor)
{
 ddbltfx.dwFillColor=kolor;
 bufor.surface->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_DDFX|DDBLT_COLORFILL,&ddbltfx);
};

void EKRAN::OdwrocBufory(void)
{
 ekran.surface->Flip(NULL,DDFLIP_WAIT);
 if(ekran.surface->IsLost())DDraw7->RestoreAllSurfaces();
};

void EKRAN::PutPix(int x,int y,DWORD kolor)
{
 hdc=GetDC(Okno);
 SetPixel(hdc,x,y,kolor);
 ReleaseDC(Okno,hdc);
};

void EKRAN::PutCircle(int x,int y,int r,DWORD kolor)
{
 hdc=GetDC(Okno);
 for(int i=1;i<360;i++)SetPixel(hdc,int(x+Katc[i]*r),int(y+Kats[i]*r),kolor);
 ReleaseDC(Okno,hdc);
};

void EKRAN::PutText(NAPIS tekst,int x,int y,DWORD kolor)
{
 hdc=GetDC(Okno);
 SetBkMode(hdc, TRANSPARENT);
 SetTextColor(hdc, kolor);
 TextOut(hdc,x,y,tekst.Text(),tekst.Lenght());
 ReleaseDC(Okno,hdc);
};