#include <dos.h>
#include "newlib.h"

#define  PelAddrRgR   0x3C7
#define  PelAddrRgW   0x3C8
#define  PelDataReg   0x3C9

typedef struct {
  int r;
  int g;
  int b;
} paleta ;

paleta pal[255];

void GetCol(int c, int *r, int *g, int *b)
{
  outportb(PelAddrRgR, c);
  *r = inportb(PelDataReg);
  *g = inportb(PelDataReg);
  *b = inportb(PelDataReg);
};

void SetCol(int c, int r, int g, int b)
{
  outportb(PelAddrRgW, c);
  outportb(PelDataReg, r);
  outportb(PelDataReg, g);
  outportb(PelDataReg, b);
};


void SetInten(int b)
{
int i, fr, fg, fb;

  for(i = 0; i < 255; i++) {
    fr = pal[i].r * b / 63;
    fg = pal[i].g * b / 63;
    fb = pal[i].b * b / 63;
    SetCol(i, fr, fg, fb);
    DVT_CallMusic();
  }
}

void fadedown(void)
{
int i, vol=255;
  for (i = 0; i < 255; i++) {
    GetCol(i, &pal[i].r, &pal[i].g, &pal[i].b);
  }
  for (i = 63; i > 0; i--) {
    DVT_SetSoundVolume(vol);
    waitretrace2();
    SetInten(i);
    vol-=4;
  }
};


#ifdef MAIN
void main(void)
{
int i;
  asm {
    mov ax, 0x13;
    int 0x10;
  }
  system("dir");
  for (i = 0; i < 63; i++) {
    GetCol(i, &pal[i].r, &pal[i].g, &pal[i].b);
  }
  for (i = 63; i > 0; i--) {
    waitretrace();
    SetInten(i);
  }
  getch();
  asm {
    mov ax, 0x3;
    int 0x10;
  }
};
#endif