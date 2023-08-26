#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>

#include "defines.h"
#include "gfx.h"
#include "pacman.h"
#include "sprites.h"
#include "misc.h"
#include "menuopt.h"

SDL_Surface *screen;
SDL_Surface *tablero;
UintDEP background[RES_XB*RES_YB*BPP];

//int eat = 0, leave_home = 0, imagen = 0;
//int CntStep, CntStep2, CntStep3;

/*void termina_programa(void)
{
  exit(0);
}*/

void help(void)
{
  printf("Uso:\n\n");
  printf("intro -f (fullscreen) -w (windomed)\n\n\n");
  exit(0);
}


int main(int argc, char **argv)
{
  int ch;
  sdl_flags = (SDL_SWSURFACE|SDL_HWPALETTE|SDL_DOUBLEBUF);
  /* Opciones -f (fullscreen) -w (en ventana) */
  while ((ch = getopt(argc, argv, "fw")) != -1)
    switch (ch) {
    case 'f': /* fullscreen */
      sdl_flags = (SDL_SWSURFACE|SDL_HWPALETTE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
      break;
    case 'w': /* ventana */
      sdl_flags = (SDL_SWSURFACE|SDL_HWPALETTE|SDL_DOUBLEBUF);
      break;
    case 'h':
      help();
    default:
      help();
    }

  if (optind < argc || !sdl_flags)
    help();

  init_gfx();

  TimerStart(timerfunc,18);
  getsprites();
  menu_opciones(TRUE);

  stargame(&fan, &pc, COMENZAR);
  exit(0);
}
