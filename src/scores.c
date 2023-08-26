#include <dos.h>
#include <alloc.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
/*#include "newlib.h"
#include "pacman.h"
#include "extended.h"
#include "defines.h"*/

#define MAX_NAMES 20


extern struct pcman {
  float x;
  float y;
  float inc_x;
  float inc_y;
  float old_inc_x;
  float old_inc_y;
  float old_x;
  float old_y;
  float yf;
  float dir;
  int puntos;
  int puntuacion;
  int nivel;
  int tiempo;
  int estado_pcman;
  int num_vidas;
};

char *nombres[MAX_NAMES];
unsigned long puntos[MAX_NAMES];

typedef struct {
  char nombre[80];
  unsigned long puntuacion;
} SCORES;

void score(struct pcman *pc)
{
FILE *fhandle;
SCORES *score;
int indice = 0;
int i;
char nombre[80];
  *nombre = 0;
/*  cls_page(0, VGA);
  unset_vectores();*/
  editar_texto(nombre,  1, 1, 20, 0,	0);
/*  set_vectores(mapa_teclado);
  memset((char *)mapa_teclado, 0, 255);*/

  if ((score = (SCORES *)farmalloc(sizeof(SCORES))) == NULL) {
      asm {
	mov ax, 0x3;
	int 0x10;
      };
      printf("Error de asignaci¢n de memoria\n");
//      termina_programa();
  };

  if ((fhandle = fopen("scores.dat", "rt")) == NULL) {
    if ((fhandle = fopen("scores.dat", "wt")) == NULL) {
      asm {
	mov ax, 0x3;
	int 0x10;
      };
      printf("No puedo crear archivo SCORES.DAT\n");
 //     termina_programa();
    } else {
      strcpy(score->nombre, nombre);
      score->puntuacion = pc->puntuacion;
      fwrite(score, sizeof(SCORES), 1, fhandle);
      fclose(fhandle);
    }
  } else {
    indice = 0;
    while(fread(score, sizeof(SCORES), 1, fhandle)) {
       nombres[indice] = score->nombre;
       puntos[indice] = score->puntuacion;
       printf("%s %6lu %5d\n", nombres[indice], puntos[indice], indice);
       indice++;
    }
    printf("%s %6lu\n",  nombres[0], puntos[0]);

    printf("%4d\n", indice);
    nombres[indice] = nombre;
    puntos[indice] =  pc->puntuacion;
    printf("%s %6lu %5d\n",  nombres[indice], puntos[indice], indice);
    indice++;
    nombres[indice] = 0;
    puntos[indice] =  0;
//    indice=0;
    for (i = 0; i < indice; i++)
      printf("%s %6lu %4d\n",  nombres[i], puntos[i], i);
    fclose(fhandle);

    if ((fhandle = fopen("scores.dat", "wt")) == NULL) {
      asm {
	mov ax, 0x3;
	int 0x10;
      };
      printf("No puedo crear archivo SCORES.DAT\n");
   // termina_programa();
    } else {
      indice = 0;
      while(nombres[indice] != 0) {
	strcpy(score->nombre, nombres[indice]);
	score->puntuacion = puntos[indice];
	fwrite(score, sizeof(SCORES), 1, fhandle);
	indice++;
      };
      fclose(fhandle);
    }
  }


  farfree(score);

  //memset((char *)mapa_teclado, 0, 255);

/*  do {
   // DVT_CallMusic();
  }  while(*(mapa_teclado + key_spc) != 1);
  memset((char *)mapa_teclado, 0, 255);*/

};


#define DEBUG

#ifdef DEBUG


#include <stdarg.h>
#include <dos.h>
#include <string.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <bios.h>
#include <conio.h>
#include <string.h>

#include "newlib.h"
#include "defines.h"


void putico2(int XMov, int YMov, char *icon, unsigned SegDes, int max_x, int max_y)
{
asm   push ds;
asm   mov  ax,SegDes;
asm   mov  es,ax;
asm   mov  ax,YMov;
asm   xchg ah,al;
asm   mov  di,ax;
asm   shr  di,2;
asm   add  di,ax;
asm   add  di,XMov;
asm   lds  si,icon;
asm   mov  dx,320;
asm   sub  dx,max_x;
asm   mov  bx,max_y;
AnotherLine:
asm   mov  cx,max_x;
asm   sar  cx,1;
asm   jnc  Par;
asm   movsb;
Par:
asm   rep movsw;
asm   add  di,dx;
asm   dec  bx;
asm   jnz  AnotherLine;
asm   pop  ds;
};



static char cursor[8*8] = {
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
};
static char black_cursor[8*8] = {
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
};
/*static char buffer[165];*/

int insertsi = 1;
void insertar_c(char codigoc, char *unacadena, int posc)
{
	int p;

	p = strlen(unacadena);
	posc = (posc < 0) ? 0 : posc;
	posc = (posc >= p) ? p : posc;
	for (; p >= posc; p--) unacadena[p+1] = unacadena[p];
	unacadena[posc] = codigoc;
}

void borrarc(char *unacadena, int posc)
{
	int p;

	p = strlen(unacadena);
	if (p > 0 && posc >= 0 && posc <= p) {
		while (posc < p) {
			unacadena[posc] = unacadena[posc+1];
			posc++;
		}
	}
}

void borfinlin(void)
{
static lugarx, lugary;
static char vacio[81];

  lugarx = wherex();
  lugary = wherey();
  sprintf(vacio, "%*c", 81-lugarx, ' ');
  printf("%s", vacio);
  gotoxy(lugarx, lugary);
}

int editar_texto(char *unacadena,  int numcol,	int numlin,
						int longmax,
						int desplaz,
						int mayus)
{
int X, x, y;
char codigoext, codigosal, carac = 0;
static char temp[MAXCHAR];
static char temp2[MAXCHAR];
int long;
int i;
int cont_der = 0;

  strcpy(temp, unacadena);

  codigoext = 0; codigosal = 0;
  X = 0;
  y = numlin; x = X + numcol;
  for (i = 0; temp[i] != '\0' && i < MAX_X; i++) {
    gotoxy(x+i, y);
    printf("%c", temp[i]);
  }
  X = (desplaz > 0) ? desplaz : 0;
  x = X + numcol;
  gotoxy(x, y);
  putico2((x * 8)-8, y, cursor, VGA, 8,8);
  strcpy(unacadena, temp);

  do {  /* BUCLE PRINCIPAL DE EDICION */
    /* debemos de suprimir una linea del texto. de la lista */
    codigoext = 0;
    carac = getch();
    putico2((x * 8)-8, y, black_cursor, VGA, 8,8);
	  switch (carac) {
	    case '\0':
	      carac = getch();
	      putico2((x * 8)-8, y, cursor, VGA, 8,8);
	      break;
	    case '\x1b': /* Escape */
	      strcpy(unacadena, temp);
	      return '\x1b';
	    case 13:
	      strcpy(unacadena, temp);
	      return 13;
	    case 8:			/* CONTROL-H o RETROCESO */
	      if (X > 0) {
		X--;
		x--;
		gotoxy(x, y);
	      }
	      if (X < strlen(temp) && X >= 0) {
		int z = 1;
		borrarc(temp, X);
		borfinlin();
		for (i = cont_der; temp[i] != '\0' && i < MAX_X+cont_der; i++) {
		  gotoxy(z, y);
		  printf("%c", temp[i]);
		  z++;
		}
		gotoxy(x, y);
		putico2((x * 8)-8, y, cursor, VGA, 8,8);
	      }
	      break;
	    default:
	      if (strlen(temp) < longmax-1) {
		if (mayus && islower(carac))
		  carac = toupper(carac);
		if (insertsi) {
		  insertar_c(carac, temp, X);
		}
		else {
		  if (X >= strlen(temp))
		    insertar_c(carac, temp, X);
		  else
		    temp[X] = carac;
		}
		X++; x++;
		gotoxy(x, y);
		putico2((x * 8)-8, y, cursor, VGA, 8,8);
		strcpy(temp2, temp);
		if (X > MAX_X) {
		  if (x < MAX_X) {
		    int i, p, old_x;
		    i = X-1;
		    old_x = x;
		    for (p = x-1; p <= MAX_X && temp2[i] != '\0' ; p++) {
		      gotoxy(p, y);
		      printf("%c", temp2[i]);
		      i++;
		    };
		    x = old_x;
		    gotoxy(x, y);
		    putico2((x * 8)-8, y, cursor, VGA, 8,8);
		  } else {
		    gotoxy(x, y);
		    printf("%c", carac);
		    gotoxy(--x, y);
		    putico2((x * 8)-8, y, cursor, VGA, 8,8);
		  };
		} else {
		  for (i = 0; temp2[i] != '\0' && i < MAX_X; i++) {
		    gotoxy(i+1, y);
		    printf("%c", temp2[i]);
		  }
		}
		gotoxy(x, y);
		putico2((x * 8)-8, y, cursor, VGA, 8,8);
	      }
	    break;
	  }
	putico2((x * 8)-8, y, cursor, VGA, 8,8);
   }  while (!codigosal);
  return 0;
}



int main(void)
{
struct pcman pc;
  clrscr();
  asm {
    mov ax, 0x13;
    int 0x10;
  }
  pc.puntuacion=100;
  score(&pc);
   getch();
  asm {
    mov ax, 0x3;
    int 0x10;
  }
  return 0;
};

#endif