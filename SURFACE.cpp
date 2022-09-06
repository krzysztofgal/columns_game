#include "SURFACE.h"

LPDIRECTDRAW7 SURFACE::lpDD=NULL;
HWND SURFACE::okno=NULL;

void SURFACE::UchwytOkna(HWND Okno)
{
 okno=Okno;
};

void SURFACE::Zwolnij()
{
 surface->Release();
 surface=NULL;
};

SURFACE::SURFACE()
{
 surface=NULL;
 ddsd.ddsCaps.dwCaps=NULL;
 ddsd.dwSize=0;
 ddsd.dwHeight=0;
 ddsd.dwWidth=0;
 ddsd.dwFlags=NULL;
};

void SURFACE::ObiektDD(LPDIRECTDRAW7 DD)
{
 lpDD=DD;
};

void SURFACE::UtworzPowierzchnie(void)
{
 lpDD->CreateSurface(&ddsd,&surface,NULL);
};

void SURFACE::UstawKolorKeying(DWORD kolor)
{
 DDCOLORKEY ddck;
 ddck.dwColorSpaceLowValue = kolor;
 ddck.dwColorSpaceHighValue = kolor; 
 surface->SetColorKey(DDCKEY_SRCBLT,&ddck);
};

void SURFACE::Blur(int ile)
{
 surface->Lock(NULL,&ddsd,DDLOCK_WAIT,NULL);
 int pix=0;
 BYTE* tab=((BYTE*)ddsd.lpSurface);
 for(int i=1;i<abs(ddsd.dwHeight-1);i++)
 for(int j=1;j<abs((ddsd.dwWidth*4)-1);j++)
 {
  pix=i*ddsd.lPitch+j;
  tab[pix]=(tab[pix]+tab[pix+(ddsd.lPitch*ile)])/2;
 }
 surface->Unlock(NULL);
};