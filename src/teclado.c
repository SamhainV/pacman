
/*
  Este m¢dulo se encarga de controlar los movimientos del pcman
  a traves del teclado.
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "SDL.h"
#include "defines.h"
/*#include "pacman.h"*/
#include "sprites.h"
/*#include "fantasmas.h"*/
#include "gfx.h"
#include "misc.h"
/*int key_der = 0,
  key_izq = 0,
  key_arr = 0,
  key_aba = 0,
  key_salir = 0,
  key_spc = 0;*/


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
	    Calculo del tiempo que los fantasmas est n asustados
	    1§ - nivel  0 15 segundos 15 * 18.2 = 273
	    2§ - nivel  1 11 segundos 11 * 18.2 = 198
	    3§ - nivel  2  9 segundos  9 * 18.2 = 162
	    4§ - nivel  3  7 segundos  7 * 18.2 = 126
	    5§ - nivel  4  5 segundos  5 * 18.2 =  90
	    6§ - nivel  5  3 segundos  3 * 18.2 =  54
	    7§ - nivel  6  1 segundos  1 * 18.2 =  20
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
	  if (c_array[(int)floor((pc.x+pc.inc_x)+pc.yf)] == 0 || c_array[(int)floor((pc.x+pc.inc_x)+pc.yf)] == P)
	    pc.inc_x = 0.0;
	  else if (c_array[(int)floor((pc.x-pc.inc_x)+pc.yf)] == 0 || c_array[(int)floor((pc.x-pc.inc_x)+pc.yf)] == P)
	    pc.inc_x = 0.0;
	  pc.yf = ((pc.y+pc.inc_y) * 32);
	  if (c_array[(int)floor(pc.x+pc.yf)] == 0 || c_array[(int)floor(pc.x+pc.yf)] == P)
	    pc.inc_y = 0.0;
	  else if (c_array[(int)floor(pc.x+(((pc.y-pc.inc_y) * 32)))] == 0 || c_array[(int)floor(pc.x+(((pc.y-pc.inc_y) * 32)))] == P)
	    pc.inc_y = 0.0;

	  

	}
      
      optener_movimientos_fantasmas(&fan, &pc);
      
      
      /* 
       * Aqui controlamos la astucia de los fantasmillas 
       */
      if (fan.estado_fantasma[0] == NORMAL) {  /* Azul  */
	fan.find_x[0] = pc.old_x;
	fan.find_y[0] = pc.old_y;
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
	    fan.find_x[0] = 19;
	    fan.find_y[0] = 12;
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
      
      /*  if (CntStep >= abs(pc.tiempo - 54)) {
	  if (CntStep % 2 == 0) {
	  outp(0x03C8, 251);
	  outp(0x03C9, 63);
	  outp(0x03C9, 63);
	  outp(0x03C9, 63);
	  } else {
	  outp(0x03C8, 251);
	  outp(0x03C9, 0);
	  outp(0x03C9, 0);
	  outp(0x03C9, 0);
	  }
	  } else {
	  outp(0x03C8, 251);
	  outp(0x03C9, 0);
	  outp(0x03C9, 0);
	  outp(0x03C9, 0);
	  }
	  
	  waitretrace2();
	  flip_page(virtual_ems, VGA);
	  flip_page(vaddr, virtual_ems);*/
      
      fill_buffer(vaddr, screen->pixels+((6400)*sizeof(UintDEP))); /* 6400 = 320 * 20 */
      //      WaitFrame();

      memcpy32(vaddr, tablero->pixels, BYTES);
      /* waitretrace2(); */
      if (SDL_MUSTLOCK (screen))
	{
	  SDL_UnlockSurface (screen);
	}
      
      SDL_Flip(screen);
      

    } 
  return 0;
}

      
      
