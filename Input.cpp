#include "Input.h"

LPDIRECTINPUT8 DINPUT::lpDI8=NULL;
LPDIRECTINPUTDEVICE8 DINPUT::klawiatura;
LPDIRECTINPUTDEVICE8 DINPUT::mysz;
HINSTANCE DINPUT::hInstance=NULL;
DIMOUSESTATE DINPUT::mouse_state;
MOUSESTATE DINPUT::stan_myszy;
HWND DINPUT::Okno=NULL;
unsigned char DINPUT::keystate[256];
clock_t DINPUT::ostatniCzasK=0;
clock_t DINPUT::ostatniCzasM=0;

MOUSESTATE::MOUSESTATE()
{
 y=x=0;
 b[0]=b[1]=b[2]=0;
};

void DINPUT::Inicjuj(HINSTANCE instancja,HWND okno)
{
 hInstance=instancja;
 Okno=okno;
 DirectInput8Create(instancja, DIRECTINPUT_VERSION,IID_IDirectInput8, (void**)&lpDI8, NULL);
 lpDI8->CreateDevice(GUID_SysKeyboard,&klawiatura, NULL);
 klawiatura->SetDataFormat(&c_dfDIKeyboard);
 klawiatura->SetCooperativeLevel(okno,DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
 klawiatura->Acquire();
 lpDI8->CreateDevice(GUID_SysMouse, &mysz, NULL);
 mysz->SetDataFormat(&c_dfDIMouse);
 mysz->SetCooperativeLevel(okno,DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
 mysz->Acquire();
 ostatniCzasK=ostatniCzasM=GetTickCount();
};

void DINPUT::Zwolnij(void)
{
 klawiatura->Unacquire();
 klawiatura->Release();
 klawiatura=NULL;
 mysz->Unacquire();
 mysz->Release();
 mysz=NULL;
 lpDI8->Release();
 lpDI8=NULL;
};

void DINPUT::SprawdzStan(void)
{
 klawiatura->GetDeviceState(sizeof(unsigned char[256]),keystate);
 mysz->GetDeviceState(sizeof(DIMOUSESTATE),&mouse_state);
 stan_myszy.x+=mouse_state.lX;
 stan_myszy.y+=mouse_state.lY;
 for(int m=0;m<5;m++)
 {
  stan_myszy.b[m]=mouse_state.rgbButtons[m];
 }
};

bool DINPUT::KEYDOWN(int klawisz,int op)
{
 if(abs(GetTickCount()-ostatniCzasK)>op)
 {
  if(keystate[klawisz])
  {
   ostatniCzasK=GetTickCount();
   return true && 0x80;
  }else return false && 0x01;
 }return false && 0x01;
};

bool DINPUT::ButtonDown(int button,int op)
{
 if(abs(GetTickCount()-ostatniCzasM)>op)
 {
  if(stan_myszy.b[button])
  {
   ostatniCzasM=GetTickCount();
   return true;
  }else return false; 
 }return false;
};

bool DINPUT::MouseOnPos(int x1,int y1,int x2,int y2)
{
 if(MyszX()>x1 && MyszY()>y1 && MyszX()<x2 && MyszY()<y2)return true;else return false;
};

BYTE DINPUT::MyszB(void)
{
 for(int i=0;i<4;i++)
 {
 if(stan_myszy.b[i])break;
 }
 return BYTE(i);
};