#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "SDL.h"
#include "defines.h"
#include "gfx.h"
#include "fantasmas.h"
#include "pacman.h"
#include "sprites.h"
#include "memcpy32.h"
#include "misc.h"

int menu_opciones(int value)
{
  Uint32 delay=3; /* milisegundos de espera (framerate) */
  
  SDL_Surface *portada;
  SDL_Event event;
  Uint8 *keys = NULL;
  int done = 1;
  int x[4], y[4];
  float i, inc_i = 0.4;
  UintDEP *buffer = background;
  int portada_x_y[] = 
    {
      85,  5, 150, 32, /* pacman rotulo x y tx ty */
      38, 50, 243, 21,   /* character_nickname */
      69,79,62,14,/* nagosia[62*14]; */
      200,79,62,12,/* Beltzak[62*12]; */
      69,106,45,15,/* azkar[45*15]; */
      200,106,35,10,/* aMoK[35*10]; */
      69,131,53,12,/* w-izar[53*12]; */
      200,131,69,64,/* Gipon[69*64]; */
      69,157,69,12,/* gautxori[69*12]; */
      200,157,62,12,/* chamber[62*12]; */
      74,197,171,16,/* Press_space[171*16]; */

    };
  int iport = 0;
  for (i = 0; i < 4; i++) 
    {
      x[(int)i] = 305;
      y[0] = 79;
      y[1] = 106;
      y[2] = 131;
      y[3] = 157;
    }
  portada = LoadImage("data/portada.bmp", 0);
  SDL_BlitSurface(portada, NULL, screen, NULL);

  if (SDL_MUSTLOCK (screen))
    {
      if (SDL_LockSurface (screen) < 0)
	exit(0);
    }
  bzero(buffer, RES_XB*RES_YB*BPP);
  bzero(screen->pixels, screen->w*screen->h*BPP);
  /*  memcpy(buffer, portada->pixels, portada->w*portada->h*BPP);*/
  i = 300;
  clearkbd(keys);
  putico(portada_x_y[iport], portada_x_y[iport+1], Pacman_rotulo, buffer, portada_x_y[iport+2], portada_x_y[iport+3]);
  iport+=4;
  putico(portada_x_y[iport], portada_x_y[iport+1], character_nickname, buffer, portada_x_y[iport+2], portada_x_y[iport+3]);
  iport+=4;
  if (SDL_MUSTLOCK (screen))
    {
      SDL_UnlockSurface (screen);
    }
  
  do  
    {
      while ( SDL_PollEvent(&event) )
	if ( event.type == SDL_QUIT )
	  return 0;
      keys = SDL_GetKeyState(NULL);
      
      if (keys[SDLK_SPACE]) 
	done = 0;
      else if (keys[SDLK_ESCAPE]) 
	exit(1);
      
      i-=inc_i;
      if (i <= 60) {
	inc_i = 0;
	if (CntStep % 150 >= 140) {
	  i = 305;
	  inc_i = 0.4;
	}
      } else CntStep = 0;

      if (SDL_MUSTLOCK (screen))
	{
	  if (SDL_LockSurface (screen) < 0)
	    exit(0);
	}
      
      if (inc_i) 
	{
	  if (CntStep2%10>5) 
	    {

	      putico(x[0]+i, y[0], rojo1izq, buffer, 14, 14);
	      putico(x[1]+i, y[1],  azu2izq, buffer, 14, 14);
	      putico(x[2]+i, y[2],  gris1izq, buffer, 14, 14);
	      putico(x[3]+i, y[3], ama2izq, buffer, 14, 14);
	    } 
	  else 
	    {
	      putico(portada_x_y[iport+32],portada_x_y[iport+33],Press_space,buffer,portada_x_y[iport+34], portada_x_y[iport+35]);
	      putico(x[0]+i, y[0], rojo2izq, buffer, 14, 14);
	      putico(x[1]+i, y[1],  azu1izq, buffer, 14, 14);
	      putico(x[2]+i, y[2],  gris2izq, buffer, 14, 14);
	      putico(x[3]+i, y[3], ama1izq, buffer, 14, 14);
	    }
	} else {
	  if (CntStep2%10>5) 
	    {
	    
	      putico(x[0]+i, y[0], rojo1der, buffer, 14, 14);
	      putico(x[1]+i, y[1],  azu2der, buffer, 14, 14);
	      putico(x[2]+i, y[2],  gris1der, buffer, 14, 14);
	      putico(x[3]+i, y[3], ama2der, buffer, 14, 14);
	    } 
	  else 
	    {
	      putico(portada_x_y[iport+32],portada_x_y[iport+33],Press_space,buffer,portada_x_y[iport+34], portada_x_y[iport+35]);
	      putico(x[0]+i, y[0], rojo2der, buffer, 14, 14);
	      putico(x[1]+i, y[1],  azu1der, buffer, 14, 14);
	      putico(x[2]+i, y[2],  gris2der, buffer, 14, 14);
	      putico(x[3]+i, y[3], ama1der, buffer, 14, 14);
	    }
	  putico(portada_x_y[iport], portada_x_y[iport+1], nagosia, buffer, portada_x_y[iport+2], portada_x_y[iport+3]);
//	  iport+=4;
	  putico(portada_x_y[iport+4], portada_x_y[iport+5], Beltzak, buffer, portada_x_y[iport+6], portada_x_y[iport+7]);
//	  iport+=4;
	  putico(portada_x_y[iport+8], portada_x_y[iport+9], azkar, buffer, portada_x_y[iport+10], portada_x_y[iport+11]);
//	  iport+=4;
	  putico(portada_x_y[iport+12], portada_x_y[iport+13], aMoK, buffer, portada_x_y[iport+14], portada_x_y[iport+15]);
//	  iport+=4;
	  putico(portada_x_y[iport+16], portada_x_y[iport+17], w_izar, buffer, portada_x_y[iport+18], portada_x_y[iport+19]);
//	  iport+=4;
	  putico(portada_x_y[iport+20], portada_x_y[iport+21], Gipon, buffer, portada_x_y[iport+22], portada_x_y[iport+23]);
//	  iport+=4;
	  putico(portada_x_y[iport+24], portada_x_y[iport+25], gautxori, buffer, portada_x_y[iport+26], portada_x_y[iport+27]);
//	  iport+=4;
	  putico(portada_x_y[iport+28], portada_x_y[iport+29], Chamber, buffer, portada_x_y[iport+30], portada_x_y[iport+31]);
	}


//      fill_buffer(buffer, screen->pixels);
      memcpy(screen->pixels,buffer, BYTES3);
      
      if (SDL_MUSTLOCK (screen))
	{
	  SDL_UnlockSurface (screen);
	}
      
      SDL_Flip(screen);
      /*      memcpy32(buffer, portada->pixels, BYTES);*/
      memset(buffer+25280, 0, 55040*sizeof(UintDEP));
      SDL_Delay(delay);
    } while(done);
  clearkbd(keys);
  return 0;
}

