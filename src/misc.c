#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "SDL.h"
#include "defines.h"
#include "misc.h"
#include "sprites.h"
#include "gfx.h"

extern void mueve_figuras(struct fantasmas *fan, struct pcman *pc);
extern void optener_movimientos_fantasmas(struct fantasmas *fan, struct pcman *pc);

int c_array[MAXY_A*MAXX_A];
int array[MAXY_A*MAXX_A] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,C,C,C,C,0,0,B,C,C,C,0,0,0,0,0,N,0,0,0,0,0,C,C,C,C,C,B,C,C,0,0,
  0,C,0,0,C,0,0,C,0,0,C,0,0,0,0,0,N,0,0,0,0,0,C,0,0,C,0,0,0,C,0,0,
  0,C,0,0,C,C,C,C,0,0,C,0,0,0,0,0,N,0,0,0,0,0,C,0,0,C,0,0,0,C,0,0,
  0,C,0,0,C,0,0,0,0,0,C,0,0,0,0,0,N,0,0,0,0,0,C,0,0,C,0,0,0,C,0,0,
  0,C,0,0,C,0,0,0,0,0,C,0,0,0,0,0,N,0,0,0,0,0,C,0,0,C,0,0,0,C,0,0,
  0,C,0,0,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,0,0,
  0,C,0,0,0,0,0,C,0,0,C,0,0,0,0,0,N,0,0,0,0,0,0,0,0,C,0,0,0,C,0,0,
  0,C,0,0,0,0,0,C,0,0,C,0,0,0,0,0,N,0,0,0,0,0,0,0,0,C,0,0,0,C,0,0,
  0,C,0,0,C,C,C,C,0,0,C,N,N,N,N,N,N,N,N,N,0,0,C,C,C,C,0,0,0,C,0,0,
  0,C,0,0,C,0,0,C,0,0,C,0,0,N,0,0,0,0,0,N,0,0,C,0,0,C,0,0,0,C,0,0,
  0,C,C,C,C,0,0,C,C,C,C,0,0,N,0,N,N,N,0,N,N,N,C,0,0,C,C,C,C,C,0,0,
  0,C,0,0,0,0,0,N,0,0,0,0,0,N,0,N,0,N,P,N,0,0,0,0,0,C,0,0,0,0,0,0,
  0,C,0,0,0,0,0,N,0,0,0,0,0,N,0,N,0,N,0,N,0,0,0,0,0,C,0,0,0,0,0,0,
  0,C,C,C,C,0,0,C,C,C,C,0,0,N,0,N,N,N,0,N,N,N,C,0,0,C,C,C,C,C,0,0,
  0,C,0,0,C,0,0,C,0,0,C,0,0,N,0,0,0,0,0,N,0,0,C,0,0,C,0,0,0,C,0,0,
  0,C,0,0,C,C,C,C,0,0,C,N,N,N,N,N,N,N,N,N,0,0,C,C,C,C,0,0,0,C,0,0,
  0,C,0,0,0,0,0,C,0,0,C,0,0,0,0,0,N,0,0,0,0,0,0,0,0,C,0,0,0,C,0,0,
  0,C,0,0,0,0,0,C,0,0,C,0,0,0,0,0,N,0,0,0,0,0,0,0,0,C,0,0,0,C,0,0,
  0,C,0,0,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,0,0,
  0,C,0,0,C,0,0,0,0,0,C,0,0,0,0,0,N,0,0,0,0,0,C,0,0,C,0,0,0,C,0,0,
  0,C,0,0,C,0,0,0,0,0,C,0,0,0,0,0,N,0,0,0,0,0,C,0,0,C,0,0,0,C,0,0,
  0,C,0,0,C,C,C,C,0,0,C,0,0,0,0,0,N,0,0,0,0,0,C,0,0,C,0,0,0,C,0,0,
  0,C,0,0,C,0,0,C,0,0,C,0,0,0,0,0,N,0,0,0,0,0,C,0,0,C,0,0,0,C,0,0,
  0,C,C,C,C,0,0,B,C,C,C,0,0,0,0,0,N,0,0,0,0,0,C,C,C,C,C,B,C,C,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};


#define MAX_RECT 4*60
int sprites_rects[MAX_RECT] = 
  {
    /* 
     * Todos estos esprites estan capturados de data/sprites.bmp 
     */
    /* Pc-Man */
    55, 145, 15, 15,  // Bola
    22, 184, 14, 15,  // pc_der
    38, 162, 11, 15,  // pc_der2
    56, 185, 14, 15,  // pc_izq
    4, 162, 11, 15,   // pc_izq2
    1, 185, 15, 14,   // pc_arr
    17, 164, 15, 11,  // pc_arr2
    40, 186, 15, 14,  // pc_aba
    54, 164, 15, 11,  // pc_aba2
    /**********/
    1, 1, 14, 14,     // rojo1arr
    16, 1, 14, 14,    // rojo2arr
    31, 1, 14, 14,    // rojo1izq
    47, 1, 14, 14,    // rojo2izq
    1, 17, 14, 14,    // rojo1aba
    16, 17, 14, 14,   // rojo2aba
    32, 17, 14, 14,   // rojo1der
    48, 17, 14, 14,   // rojo2der
    /**********/
    1, 33, 14, 14,    // ama1arr
    17, 33, 14, 14,   // ama2arr
    34, 33, 14, 14,   // ama1izq
    50, 33, 14, 14,   // ama2izq
    1, 49, 14, 14,    // ama1aba
    17, 49, 14, 14,   // ama2aba
    34, 49, 14, 14,   // ama1der
    50, 49, 14, 14,   // ama2der
    /**********/
    1, 65, 14, 14,    // azu1arr
    17, 65, 14, 14,   // azu2arr
    34, 65, 14, 14,   // azu1izq
    50, 65, 14, 14,   // azu2izq
    1, 81, 14, 14,    // azu1aba
    17, 81, 14, 14,   // azu2aba
    34, 81, 14, 14,   // azu1der
    50, 81, 14, 14,   // azu2der
    /**********/
    1, 97, 14, 14,    // gris1arr
    17, 97, 14, 14,   // gris2arr
    34, 97, 14, 14,   // gris1izq
    50, 97, 14, 14,   // gris2izq
    1, 113, 14, 14,   // gris1aba
    17, 114, 14, 14,  // gris2aba
    34, 113, 14, 14,  // gris1der
    50, 113, 14, 14,  // gris2der
    /**********/
    112, 170, 10, 10, // asusta
    81, 123, 10, 5,   // ojos
    80, 139, 14, 14, // miedo
    80, 160, 14, 14, // miedo2
    /**********/
    72, 4, 150, 32,   // Pacman Rotulo
    74, 38, 243, 21,  // character/nickname
    123, 59, 62, 14,  // nagosia
    121, 81, 45, 15,  // azkar
    119, 100, 69, 12, // gautxori
    122, 122, 53, 12, // w - izar
    119, 138, 31, 13, // 1 up
    156, 138, 84, 13, // hight score
    137, 159, 30, 8,  // 10 pts
    180, 159, 30, 8,  // 50 pts
    132, 173, 171, 16,// press space
    223, 59, 62, 12,  // Beltzak
    213, 83, 35, 10,  // aMoK
    238, 100, 62, 12, // Chamber
    215, 122, 69, 14, // [G]ip_oN
    
  };

UintDEP *ptrs[MAX_RECT/4] = { 
  bola, pc_der, pc_der2, pc_izq, pc_izq2, pc_arr, pc_arr2, pc_aba, pc_aba2, // pacman
  rojo1arr, rojo2arr, rojo1izq, rojo2izq, rojo1aba, rojo2aba, rojo1der, rojo2der,   // Fantasma rojo
  ama1arr,  ama2arr,  ama1izq,  ama2izq,  ama1aba,  ama2aba,  ama1der,  ama2der,     // Fantasma amarillo
  azu1arr,  azu2arr,  azu1izq,  azu2izq,  azu1aba,  azu2aba,  azu1der,  azu2der,    // Fantasma azul
  gris1arr, gris2arr, gris1izq, gris2izq, gris1aba, gris2aba, gris1der, gris2der,    // Fantasma gris
  asusta, ojos, miedo, miedo2,
  Pacman_rotulo, character_nickname, nagosia, azkar, gautxori, w_izar, _1_up,
  hight_score, _10pts, _50pts, Press_space, Beltzak, aMoK, Chamber, Gipon,
  
};

struct fantasmas fan;
struct pcman pc;

float inc_velocidad[4];
float velocidades[14] = {
  0.4,      // Nivel  0
  0.5,      // Nivel  1
  0.6,      // Nivel  2
  0.7,      // Nivel  3
  0.8,      // Nivel  4
  0.9,      // Nivel  5
  1.0,      // Nivel  6
  1.1,      // Nivel  7
  1.2,      // Nivel  8
  1.3,      // Nivel  9
  1.4,      // Nivel 10
  1.5,      // Nivel 11
  1.6,      // Nivel 12
  1.7       // Nivel 13
};
float inc_velocidad_pc = 0.5;
int busca_posiciones[4];
int busca_posiciones_pc = TRUE;


void clearkbd(Uint8 *keys)
{
  keys = SDL_GetKeyState(NULL);
  keys[SDLK_UP] =   keys[SDLK_DOWN] =   keys[SDLK_RIGHT] =   keys[SDLK_LEFT] =   keys[SDLK_ESCAPE] =   keys[SDLK_SPACE] = 0;
}

void writef(int col, int row, UintDEP *where, char *format, ...)
{
  va_list arg_ptr;
  char output[81];
  size_t len;
  int _width;
  int itemp, i;
  va_start(arg_ptr, format);
  vsprintf(output, format, arg_ptr);
  _width = strlen(output);
  *(output + _width) = 0;
  if ((len = strlen(output)) < _width)
    memset(&output[len], ' ', _width - len);
  /* paso de poner el siguiente codigo en una funci�n */
  /* esta funci�n tarda demasiado tiempo y no quiero gastar m�s */
  /* llamando a una funci�n */
  
  /* Analizaremos la cadena empezando por el final e iremos escribiendo */
  /* los n�meros que vayan apareciendo */
  itemp = strlen(output);
  for (i = itemp; i >= 0; i--) {
    switch(output[i]) {
    case '0':
      putico(col, row, n_0, where, 4, 7);
      break;
    case '1':
      putico(col, row, n_1, where, 4, 7);
      break;
    case '2':
      putico(col, row, n_2, where, 4, 7);
      break;
    case '3':
      putico(col, row, n_3, where, 4, 7);
      break;
    case '4':
      putico(col, row, n_4, where, 4, 7);
      break;
    case '5':
      putico(col, row, n_5, where, 4, 7);
      break;
    case '6':
      putico(col, row, n_6, where, 4, 7);
      break;
    case '7':
      putico(col, row, n_7, where, 4, 7);
      break;
    case '8':
      putico(col, row, n_8, where, 4, 7);
      break;
    case '9':
      putico(col, row, n_9, where, 4, 7);
      break;
    }
    col -= 5;
  }
  
}


void getsprites(void)
{
  SDL_Surface *sprites;
  SDL_Rect rect;
  int i, irect;
  sprites = LoadImage("data/sprites.bmp", 0);
  for (i = 0, irect = 0; i < MAX_RECT; i += 4)
    {
      rect.x = sprites_rects[i];  
      rect.y = sprites_rects[i+1];  
      rect.w = sprites_rects[i+2];
      rect.h = sprites_rects[i+3];      
      getsprite(sprites, &rect, *(ptrs+irect++));
    }

}

void copyarray(void)
{
int j;
  for (j = 0; j < MAXX_A * MAXY_A; j++)
    c_array[j] = array[j];
}

void pon_puntos_en_pantalla(void)
{
  int j, i;
  for (i = 0; i < MAXY_A; i++)
    for (j = 0; j < MAXX_A; j++) {
      if (c_array[j + i * MAXX_A] == C) {
	putico(COOR_X + (j * 8), COOR_Y + (i * 8)-3, punto, tablero->pixels, 4, 4);
      }
    }
}

void inicializa_structuras(struct pcman *pc, struct fantasmas *fan, int value)
{
  pc->x = 7;
  pc->y = 11;
  pc->old_x = 7;
  pc->old_y = 11;
  pc->inc_x = 0;
  pc->inc_y = -1;
  pc->old_inc_x = 0;
  pc->old_inc_y = 0;
  pc->estado_pcman = NORMAL;
  if (value == TRUE || value == COMENZAR) {
    pc->puntos = NUM_PUNTOS;
  }
  if (value == COMENZAR) {
    pc->nivel = 0;
    pc->num_vidas = 2;
    pc->puntuacion = 0;
  }

  fan->who = 0;              /* Azul */
  fan->x[fan->who] = 17;
  fan->y[fan->who] = 11;
  fan->inc_x[fan->who] =   1; /* der */
  fan->inc_y[fan->who] =   0;
  fan->old_mov_x[fan->who] =  1;
  fan->old_mov_y[fan->who] =  0;
  fan->find_x[fan->who] = pc->x;
  fan->find_y[fan->who] = pc->y;

  fan->who = 1;             /* Rojo */
  fan->x[fan->who] = 19;
  fan->y[fan->who] = 12;
  fan->inc_x[fan->who] =   0;
  fan->inc_y[fan->who] =   1; /* aba */
  fan->old_mov_x[fan->who] =  1;
  fan->old_mov_y[fan->who] =  0;
  fan->find_x[fan->who] = pc->x;
  fan->find_y[fan->who] = pc->y;

  fan->who = 2;           /* Amarillo */
  fan->x[fan->who] = 15;
  fan->y[fan->who] = 11;
  fan->inc_x[fan->who] =   0;
  fan->inc_y[fan->who] =   1; /* aba */
  fan->old_mov_x[fan->who] =  1;
  fan->old_mov_y[fan->who] =  0;
  fan->find_x[fan->who] = pc->x;
  fan->find_y[fan->who] = pc->y;

  fan->who = 3;        /* Gris */
  fan->x[fan->who] = 16;
  fan->y[fan->who] = 14;
  fan->inc_x[fan->who] =   0;
  fan->inc_y[fan->who] =   1; /* aba */
  fan->old_mov_x[fan->who] =  1;
  fan->old_mov_y[fan->who] =  0;
  fan->find_x[fan->who] = pc->x;
  fan->find_y[fan->who] = pc->y;

  fan->estado_fantasma[0] = NORMAL;
  fan->estado_fantasma[1] = NORMAL;
  fan->estado_fantasma[2] = NORMAL;
  fan->estado_fantasma[3] = NORMAL;
  
  switch(pc->nivel) {
  case 0:
    pc->tiempo = 273;
    inc_velocidad[0] = velocidades[pc->nivel];
    inc_velocidad[1] = velocidades[pc->nivel];
    inc_velocidad[2] = velocidades[pc->nivel];
    inc_velocidad[3] = velocidades[pc->nivel];
    break;
  case 1:
    pc->tiempo = 198;
    inc_velocidad[0] = velocidades[pc->nivel];
    inc_velocidad[1] = velocidades[pc->nivel];
    inc_velocidad[2] = velocidades[pc->nivel];
    inc_velocidad[3] = velocidades[pc->nivel];
    break;
  case 2:
    pc->tiempo = 162;
    inc_velocidad[0] = velocidades[pc->nivel];
    inc_velocidad[1] = velocidades[pc->nivel];
    inc_velocidad[2] = velocidades[pc->nivel];
    inc_velocidad[3] = velocidades[pc->nivel];
    break;
  case 3:
    pc->tiempo = 126;
    inc_velocidad[0] = velocidades[pc->nivel];
    inc_velocidad[1] = velocidades[pc->nivel];
    inc_velocidad[2] = velocidades[pc->nivel];
    inc_velocidad[3] = velocidades[pc->nivel];
    break;
  case 4:
    pc->tiempo = 90;
    inc_velocidad[0] = velocidades[pc->nivel];
    inc_velocidad[1] = velocidades[pc->nivel];
    inc_velocidad[2] = velocidades[pc->nivel];
    inc_velocidad[3] = velocidades[pc->nivel];
    break;
  case 5:
    pc->tiempo = 90;
    inc_velocidad[0] = velocidades[pc->nivel];
    inc_velocidad[1] = velocidades[pc->nivel];
    inc_velocidad[2] = velocidades[pc->nivel];
    inc_velocidad[3] = velocidades[pc->nivel];
    break;
  case 6:
    pc->tiempo = 90;
    inc_velocidad[0] = velocidades[pc->nivel];
    inc_velocidad[1] = velocidades[pc->nivel];
    inc_velocidad[2] = velocidades[pc->nivel];
    inc_velocidad[3] = velocidades[pc->nivel];
    break;
  case 7:
    pc->tiempo = 90;
    inc_velocidad[0] = velocidades[pc->nivel];
    inc_velocidad[1] = velocidades[pc->nivel];
    inc_velocidad[2] = velocidades[pc->nivel];
    inc_velocidad[3] = velocidades[pc->nivel];
    break;
  case 8:
    pc->tiempo = 90;
    inc_velocidad[0] = velocidades[pc->nivel];
    inc_velocidad[1] = velocidades[pc->nivel];
    inc_velocidad[2] = velocidades[pc->nivel];
    inc_velocidad[3] = velocidades[pc->nivel];
    break;
  case 9:
    pc->tiempo = 90;
    inc_velocidad[0] = velocidades[pc->nivel];
    inc_velocidad[1] = velocidades[pc->nivel];
    inc_velocidad[2] = velocidades[pc->nivel];
    inc_velocidad[3] = velocidades[pc->nivel];
    break;
  case 10:
    pc->tiempo = 90;
    inc_velocidad[0] = velocidades[pc->nivel];
    inc_velocidad[1] = velocidades[pc->nivel];
    inc_velocidad[2] = velocidades[pc->nivel];
    inc_velocidad[3] = velocidades[pc->nivel];
    break;
  case 11:
    pc->tiempo = 90;
    inc_velocidad[0] = velocidades[pc->nivel];
    inc_velocidad[1] = velocidades[pc->nivel];
    inc_velocidad[2] = velocidades[pc->nivel];
    inc_velocidad[3] = velocidades[pc->nivel];
    break;
  case 12:
    pc->tiempo = 90;
    inc_velocidad[0] = velocidades[pc->nivel];
    inc_velocidad[1] = velocidades[pc->nivel];
    inc_velocidad[2] = velocidades[pc->nivel];
    inc_velocidad[3] = velocidades[pc->nivel];
    break;
  case 13:
    pc->tiempo = 20;
    inc_velocidad[0] = velocidades[pc->nivel];
    inc_velocidad[1] = velocidades[pc->nivel];
    inc_velocidad[2] = velocidades[pc->nivel];
    inc_velocidad[3] = velocidades[pc->nivel];
    break;
  default:
    pc->nivel = 13;
    inc_velocidad[0] = velocidades[pc->nivel];
    inc_velocidad[1] = velocidades[pc->nivel];
    inc_velocidad[2] = velocidades[pc->nivel];
    inc_velocidad[3] = velocidades[pc->nivel];
    break;
  };
  
  busca_posiciones[0] = TRUE;
  busca_posiciones[1] = TRUE;
  busca_posiciones[2] = TRUE;
  busca_posiciones[3] = TRUE;
/*  cls_page(0, vaddr);
  cls_page(0, virtual_ems);

  putico2(0, 0, tablero, vaddr, 299, 200);
  putico2(0, 0, tablero, virtual_ems, 299, 200);

  if (pc->num_vidas == 2) {
    putico2(303, 1, pc_der, vaddr, 14, 15);
    putico2(303, 15, pc_der, vaddr, 14, 15);
  } else if (pc->num_vidas == 1) {
    putico2(303, 1, pc_der, vaddr, 14, 15);
    screentrans (303, 15, 14, 15,  vaddr, virtual_ems);
    putico2(0, 0, tablero, virtual_ems, 299, 200);
  } else if (pc->num_vidas == 0) {
    putico2(0, 0, tablero, virtual_ems, 299, 200);
    screentrans (303, 1, 14, 15,   vaddr, virtual_ems);
    screentrans (303, 15, 14, 15,  vaddr, virtual_ems);
  };*/
  CntStep = CntStep2 = CntStep3 = 0;
//  pon_puntos_en_pantalla();
};


/*
  Esta funci�n es llamada cuando nos
  comemos todos los puntos de un circuito.
*/

void adelanta_nivel(struct fantasmas *fan, struct pcman *pc)
{
  pc->nivel++;
  stargame(fan, pc, TRUE);
}

void stargame(struct fantasmas *fan, struct pcman *pc, int value)
{
  if (value == TRUE || value == COMENZAR)
    copyarray();

  /* Pone primer premio en pantalla : */
  /* El bast�n */
  inicializa_structuras(pc, fan, value);

  tablero = LoadImage("data/tablero.bmp", 0);
  CntStep2 = 0;
  teclado();
};


int teclado(void)
{
  SDL_Event event;
  Uint8 *keys;
  int done = 1;
  UintDEP *vaddr = background;
  int xp, yp;
  int arr_pulsada = 0, aba_pulsada = 0, der_pulsada = 0, izq_pulsada = 0;
  int alea[2];
  int xf,yf;
  unsigned int CntStep4;
  bzero(screen->pixels, RES_X*RES_Y*BPP);
  /*  flip_page(vaddr, VGA);*/

  putico(COOR_X + (pc.x * 8) - 5, COOR_Y + (pc.y * 8) - 9, pc_arr, vaddr, 15, 14);
  xf = COOR_X + (fan.x[0] * 8) - 5;
  yf = COOR_Y + (fan.y[0] * 8) - 9;
  putico(xf, yf, azu1izq, vaddr, 14, 14);
  xf = COOR_X + (fan.x[1] * 8) - 5;
  yf = COOR_Y + (fan.y[1] * 8) - 9;
  putico(xf, yf, rojo1izq, vaddr, 14, 14);
  xf = COOR_X + (fan.x[2] * 8) - 5;
  yf = COOR_Y + (fan.y[2] * 8) - 9;
  putico(xf, yf, ama1izq, vaddr, 14, 14);
  xf = COOR_X + (fan.x[3] * 8) - 5;
  yf = COOR_Y + (fan.y[3] * 8) - 9;
  putico(xf, yf, gris1izq, vaddr, 14, 14);
  /*  playon = SILENCIO; */
  /*  dsleep(&fan);*/
  /*  memset((char *)mapa_teclado, 0, 255);*/


  while(done)
    {
      while ( SDL_PollEvent(&event) ) {
	if ( event.type == SDL_QUIT )
	  return 0;
      }
      keys = SDL_GetKeyState(NULL);
      
      /* Check for keyboard abort */
      if ( keys[SDLK_ESCAPE]) {// == SDL_PRESSED ) {
	done = 0;
      }

      if (SDL_MUSTLOCK (screen))
	{
	  if (SDL_LockSurface (screen) < 0)
	    exit(0);
	}
      

     
      pc.old_inc_x = pc.inc_x;
      pc.old_inc_y = pc.inc_y;
      
      if (busca_posiciones_pc == TRUE) 
	{
	  if (keys[SDLK_UP]) 
	    {
	      izq_pulsada = arr_pulsada = aba_pulsada = der_pulsada = 0;
	      pc.yf =  ((pc.y-1) * 32);
	      pc.dir = pc.x + pc.yf;
	      if (c_array[(int)pc.dir] != 0.0 && c_array[(int)pc.dir] != P) {
		pc.inc_y = -1;
		pc.inc_x = 0;
		arr_pulsada = 0;
	      } else {
		arr_pulsada = 1;
		aba_pulsada = der_pulsada = izq_pulsada = 0;
	      }
	    }
	  if (keys[SDLK_DOWN]) 
	    {
	      izq_pulsada = arr_pulsada = aba_pulsada = der_pulsada = 0;
	      pc.yf =  ((pc.y+1) * 32);
	      pc.dir = pc.x + pc.yf;
	      if (c_array[(int)pc.dir] != 0 && c_array[(int)pc.dir] != P) {
		pc.inc_y = 1;
		pc.inc_x = 0;
		aba_pulsada = 0;
	      } else {
		aba_pulsada = 1;
		arr_pulsada = der_pulsada = izq_pulsada = 0;
	      }
	    }
	  if (keys[SDLK_RIGHT]) 
	    {
	      izq_pulsada = arr_pulsada = aba_pulsada = der_pulsada = 0;
	      pc.yf =  (pc.y * 32);
	      pc.dir = pc.x+1 + pc.yf;
	      if (c_array[(int)pc.dir] != 0 && c_array[(int)pc.dir] != P) {
		pc.inc_x = 1;
		pc.inc_y = 0;
		der_pulsada = 0;
	      } else {
		der_pulsada = 1;
		arr_pulsada = aba_pulsada = izq_pulsada = 0;
	      }
	    }
	  if (keys[SDLK_LEFT]) 
	    {
	      izq_pulsada = arr_pulsada = aba_pulsada = der_pulsada = 0;
	      pc.yf =  (pc.y * 32);
	      pc.dir = (pc.x-1) + pc.yf;
	      if (c_array[(int)pc.dir] != 0 && c_array[(int)pc.dir] != P) {
		pc.inc_x = -1;
		pc.inc_y = 0;
		izq_pulsada = 0;
	      } else {
		izq_pulsada = 1;
		arr_pulsada = aba_pulsada = der_pulsada = 0;
	      }
	    }

	  /*    memset((char *)mapa_teclado, 0, 255);*/
	  
	  pc.yf = ((pc.y-1) * 32);
	  if (arr_pulsada == 1 && c_array[(int)(pc.x+(pc.yf))] != 0 && c_array[(int)(pc.x+(pc.yf))] != P) {
	    arr_pulsada = 0;
	    pc.inc_y = -1;
	    pc.inc_x = 0;
	  }
	  
	  pc.yf = ((pc.y+1) * 32);
	  if (aba_pulsada == 1 && c_array[(int)(pc.x+(pc.yf))] != 0 && c_array[(int)(pc.x+(pc.yf))] != P) {
	    aba_pulsada = 0;
	    pc.inc_y = 1;
	    pc.inc_x = 0;
	  }
	  
	  pc.yf = (pc.y * 32);
	  if (der_pulsada == 1 && c_array[(int)(pc.x+1+pc.yf)] != 0 && c_array[(int)(pc.x+1+pc.yf)] != P) {
	    der_pulsada = 0;
	    pc.inc_y = 0;
	    pc.inc_x = 1;
	  }
	  
	  pc.yf = (pc.y * 32);
	  if (izq_pulsada == 1 && c_array[(int)((pc.x-1)+pc.yf)] != 0 && c_array[(int)((pc.x-1)+pc.yf)] != P) {
	    izq_pulsada = 0;
	    pc.inc_y = 0;
	    pc.inc_x = -1;
	  }
	  
	  if (pc.x == 16 && pc.y == 1) {
	    pc.x = 16;
	    pc.y = 24;
	    pc.inc_y = -1;
	  } else
	    if (pc.x == 16 && pc.y == 24) {
	      pc.x = 16;
	      pc.y =  1;
	      pc.inc_y = 1;
	    }

	  /*    Control de bolones asusta fantasmas */
	  if (c_array [(int)(pc.x + (pc.y * 32))] == B) {
	    c_array[(int)(pc.x + (pc.y * 32))] = J;
	    xp = COOR_X + (pc.x * 8) - 6;
	    yp = COOR_Y + (pc.y * 8) - 9;
	    putico(xp + 3, yp + 2, bak_asusta, tablero->pixels, 10, 10);
	    pc.estado_pcman = ENFADADO;
	    if (fan.estado_fantasma[0] == NORMAL) fan.estado_fantasma[0] = ENFADADO;
	    if (fan.estado_fantasma[1] == NORMAL) fan.estado_fantasma[1] = ENFADADO;
	    if (fan.estado_fantasma[2] == NORMAL) fan.estado_fantasma[2] = ENFADADO;
	    if (fan.estado_fantasma[3] == NORMAL) fan.estado_fantasma[3] = ENFADADO;
	    pc.puntuacion+=50;
	    CntStep = 0;
	  }
	  
	  /* Semaforo para los asusta fantasmas */
	  CntStep4 = CntStep%12;
	  if (CntStep4 >= 0 && CntStep4 <= 5) {
	    if (c_array [ 7 +  1 * 32] == B)putico(108, 3, bak_asusta, tablero->pixels, 10, 10);
	    if (c_array [ 7 + 24 * 32] == B)putico(108, 187, bak_asusta, tablero->pixels, 10, 10);
	    if (c_array [27 +  1 * 32] == B)putico(268, 3, bak_asusta, tablero->pixels, 10, 10);
	    if (c_array [27 + 24 * 32] == B)putico(268, 187, bak_asusta, tablero->pixels, 10, 10);
	  } else if (CntStep4 >= 6 && CntStep4 <= 11) {
	    if (c_array [ 7 +  1 * 32] == B)putico(108, 3, asusta, tablero->pixels, 10, 10);
	    if (c_array [ 7 + 24 * 32] == B)putico(108, 187, asusta, tablero->pixels, 10, 10);
	    if (c_array [27 +  1 * 32] == B)putico(268, 3, asusta, tablero->pixels, 10, 10);
	    if (c_array [27 + 24 * 32] == B)putico(268, 187, asusta, tablero->pixels, 10, 10);
	  }
	  
	  /*
	    Calculo del tiempo que los fantasmas est�n asustados
	    1� - nivel  0 15 segundos 15 * 18.2 = 273
	    2� - nivel  1 11 segundos 11 * 18.2 = 198
	    3� - nivel  2  9 segundos  9 * 18.2 = 162
	    4� - nivel  3  7 segundos  7 * 18.2 = 126
	    5� - nivel  4  5 segundos  5 * 18.2 =  90
	    6� - nivel  5  3 segundos  3 * 18.2 =  54
	    7� - nivel  6  1 segundos  1 * 18.2 =  20
	  */
	  
	  if (pc.estado_pcman == ENFADADO && CntStep >= pc.tiempo) {
	    pc.estado_pcman = NORMAL;
	    if (fan.estado_fantasma[0] == ENFADADO) fan.estado_fantasma[0] = NORMAL;
	    if (fan.estado_fantasma[1] == ENFADADO) fan.estado_fantasma[1] = NORMAL;
	    if (fan.estado_fantasma[2] == ENFADADO) fan.estado_fantasma[2] = NORMAL;
	    if (fan.estado_fantasma[3] == ENFADADO) fan.estado_fantasma[3] = NORMAL;
	  }
	  /***************************************/
	  
	  writef(40, 25, tablero->pixels, "%5d", pc.puntuacion);
	  
	  
	  /* Marca el array por donde pase en pcman */
	  if (c_array [(int)(pc.x + (pc.y * 32))] == C) {
	    /* Camino no pasado */
	    c_array[(int)(pc.x + (pc.y * 32))] = J;
	    /* 46 151 */
	    xp = COOR_X + (pc.x * 8) - 6;
	    yp = COOR_Y + (pc.y * 8) - 8;
	    putico(xp + 6, yp + 4, punto_negro, tablero->pixels, 4, 4);
	    pc.puntos--;
	    pc.puntuacion+=10;
	    if (pc.puntos == 0) {
	      adelanta_nivel(&fan, &pc);
	    }
	    /*   playon = COME;*/
	  } else {
	    /*   playon = SILENCIO;*/
	  }
	  
	  
	  pc.old_x = pc.x;
	  pc.old_y = pc.y;

	  pc.x += pc.inc_x;
	  pc.y += pc.inc_y;

	  pc.yf = (pc.y * 32);
	  if (c_array[(int)((pc.x+pc.inc_x)+pc.yf)] == 0 || c_array[(int)((pc.x+pc.inc_x)+pc.yf)] == P)
	    pc.inc_x = 0.0;
	  else if (c_array[(int)((pc.x-pc.inc_x)+pc.yf)] == 0 || c_array[(int)((pc.x-pc.inc_x)+pc.yf)] == P)
	    pc.inc_x = 0.0;
	  pc.yf = ((pc.y+pc.inc_y) * 32);
	  if (c_array[(int)(pc.x+pc.yf)] == 0 || c_array[(int)(pc.x+pc.yf)] == P)
	    pc.inc_y = 0.0;
	  else if (c_array[(int)(pc.x+(((pc.y-pc.inc_y) * 32)))] == 0 || c_array[(int)(pc.x+(((pc.y-pc.inc_y) * 32)))] == P)
	    pc.inc_y = 0.0;

	  

	}
      
      optener_movimientos_fantasmas(&fan, &pc);
      
      
      /* 
       * Aqui controlamos la astucia de los fantasmillas 
       */
      if (fan.estado_fantasma[0] == NORMAL) {  /* Azul  */
	if (fan.x[0] == fan.find_xp[0] && fan.y[0] == fan.find_yp[0])
	  {
	    fan.find_xp[0] = pc.x;
	    fan.find_yp[0] = pc.y;
	    
	    fan.find_x[0] = fan.find_xp[0];
	    fan.find_y[0] = fan.find_yp[0];
/*	    printf("%f %f %f %f\n", fan.find_xp[0],fan.find_yp[0],fan.find_x[0],fan.find_y[0]);
	    fflush(stdin);*/

	  }
      } else if (fan.estado_fantasma[0] == ENFADADO) {
	alea[0] = rand() % MAXX_A;
	alea[1] = rand() % MAXY_A;
	fan.find_x[0] = alea[0];
	fan.find_y[0] = alea[1];
      } else {
	fan.find_x[0] = 16;
	fan.find_y[0] = 12;
      }
      
      if (fan.estado_fantasma[1] == NORMAL) { /* Rojo */
	fan.find_x[1] = pc.x;
	fan.find_y[1] = pc.y;
      } else  if (fan.estado_fantasma[1] == ENFADADO) {
	alea[0] = rand() % MAXX_A;
	alea[1] = rand() % MAXY_A;
	fan.find_x[1] = alea[0];
	fan.find_y[1] = alea[1];
      } else {
	fan.find_x[1] = 16;
	fan.find_y[1] = 12;
      }
      
      if (fan.estado_fantasma[2] == NORMAL) { /* amarillo */
	if (fabs(pc.x - fan.x[2]) < 9 && fabs(pc.y - fan.y[2]) < 9)
	  {
	    fan.find_x[2] = pc.x;
	    fan.find_y[2] = pc.y;
	  } else {
	    fan.find_x[2] = rand()%MAXX_A;
	    fan.find_y[2] = rand()%MAXY_A;
	  }
/*	printf("%f %f\n", fabs(pc.x - fan.x[2]),fabs(pc.y - fan.y[2]));
	fflush(stdin);*/
      } else if (fan.estado_fantasma[2] == ENFADADO) {
	alea[0] = rand() % MAXX_A;
	alea[1] = rand() % MAXY_A;
	fan.find_x[2] = alea[0];
	fan.find_y[2] = alea[1];
      } else {
	fan.find_x[2] = 16;
	fan.find_y[2] = 12;
      }
      
      if (fan.estado_fantasma[3] == NORMAL) { /* verde */
	if (fabs(pc.x - fan.x[3]) < 12 && fabs(pc.y - fan.y[3]) < 12)
	  {
	    fan.find_x[3] = pc.x;
	    fan.find_y[3] = pc.y;
	  } else {
	    fan.find_x[3] = rand()%MAXX_A;
	    fan.find_y[3] = rand()%MAXY_A;
	  }

/*	fan.find_x[3] = rand()%MAXX_A;
	fan.find_y[3] = rand()%MAXY_A;*/
      } else if (fan.estado_fantasma[3] == ENFADADO) {
	alea[0] = rand() % MAXX_A;
	alea[1] = rand() % MAXY_A;
	fan.find_x[3] = alea[0];
	fan.find_y[3] = alea[1];
      } else {
	fan.find_x[3] = 16;
	fan.find_y[3] = 12;
      }

      mueve_figuras(&fan, &pc);

      if (busca_posiciones[0] == TRUE) {
	if (fan.x[0] == 17 && fan.y[0] == 12 && fan.estado_fantasma[0] == NORMAL)  {
	  if (CntStep2 >= 50 && CntStep2 <= 100) {
/*	    fan.find_x[0] = 19;
	    fan.find_y[0] = 12;*/
	    fan.find_x[0] = fan.find_xp[0] = pc.x;
	    fan.find_y[0] = fan.find_yp[0] = pc.y;
	    fan.inc_x[0] = 1;
	    fan.inc_y[0] = 0;
	  } else {
	    fan.find_x[0] = 15;
	    fan.find_y[0] = 12;
	  }
	}
      }
      if (busca_posiciones[1] == TRUE) {
	if (fan.x[1] == 17 && fan.y[1] == 12 && fan.estado_fantasma[1] == NORMAL)  {
	  if (CntStep2 >= 100 && CntStep2 <= 150) {
	    fan.find_x[1] = 19;
	    fan.find_y[1] = 12;
	    fan.inc_x[1] = 1;
	    fan.inc_y[1] = 0;
	  } else {
	    fan.find_x[1] = 15;
	    fan.find_y[1] = 12;
	  }
	}
      }
      if (busca_posiciones[2] == TRUE) {
	if (fan.x[2] == 17 && fan.y[2] == 12 && fan.estado_fantasma[2] == NORMAL)  {
	  if (CntStep2 >= 150 && CntStep2 <= 200) {
	    fan.find_x[2] = 19;
	    fan.find_y[2] = 12;
	    fan.inc_x[2] = 1;
	    fan.inc_y[2] = 0;
	  } else {
	    fan.find_x[2] = 15;
	    fan.find_y[2] = 12;
	  }
	}
      }
      if (busca_posiciones[3] == TRUE) {
	if (fan.x[3] == 17 && fan.y[3] == 12 && fan.estado_fantasma[3] == NORMAL)  {
	  if (CntStep2 >= 200 && CntStep2 <= 240) {
	    fan.find_x[3] = 19;
	    fan.find_y[3] = 12;
	    fan.inc_x[3] = 1;
	    fan.inc_y[3] = 0;
	  } else {
	    fan.find_x[3] = 15;
	    fan.find_y[3] = 12;
	  }
	}
      }

     

      memcpy(screen->pixels,vaddr, BYTES3);

      WaitFrame(); /* clave para la correcta ejecucion del timer */
      
      memcpy(vaddr, tablero->pixels, RES_X*RES_Y*BPP);
      
      
      if (SDL_MUSTLOCK (screen))
	{
	  SDL_UnlockSurface (screen);
	}
      
      SDL_Flip(screen);
      
      
    } 
  return 0;
}

