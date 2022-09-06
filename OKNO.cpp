#include "OKNO.h"

bool OKNO::koniecProgramu=false;

OKNO::OKNO()
{
 hOkno=NULL;
 hInstance=NULL;
};

void OKNO::UtworzKlaseOkna(HINSTANCE instancja,WNDPROC petlaKomunikatow)
{
 wd.hInstance=instancja;
 wd.lpfnWndProc=petlaKomunikatow;
 wd.lpszClassName="klasa";
 wd.style=CS_HREDRAW | CS_VREDRAW;
 wd.cbClsExtra=0;
 wd.cbWndExtra=0;
 wd.lpszMenuName=NULL;
 wd.hIcon=LoadIcon(NULL,IDI_WINLOGO);
 wd.hCursor=LoadCursor(instancja,IDC_ARROW);
 RegisterClass(&wd);
 hInstance=instancja;
};

void OKNO::UtworzOkno(LPCSTR nazwaOkna,unsigned int rozmiarX,unsigned int rozmiarY)
{
 hOkno = CreateWindow("klasa",nazwaOkna,WS_EX_TOPMOST | WS_POPUP,0,0,rozmiarX,rozmiarY,NULL,NULL,hInstance,NULL);
 ShowWindow(hOkno,1);
 ShowCursor(false);
};

HWND OKNO::ZwrocUchwytOkna(void)
{
 return hOkno;
}

void OKNO::Wiadomosc(HWND okno,LPSTR text)
{
 MessageBox(okno,text,"Informacja",MB_OK);
};

void OKNO::Petla(void(*funkcja)(void))
{
 MSG komunikat;
 for(;;)
 { 	
  funkcja();
  if (PeekMessage(&komunikat,NULL,0,0,PM_REMOVE))
  {
   if(koniecProgramu)break;
   TranslateMessage(&komunikat);
   DispatchMessage(&komunikat);
  }
 }
};