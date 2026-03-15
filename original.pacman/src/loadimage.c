#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

#include "include/loadimage.h"

SDL_Surface *LoadImage(char *datafile, int transparent)
{
  SDL_Surface *image, *surface;
  
  image = IMG_Load(datafile);
  if ( image == NULL ) {
    fprintf(stderr, "Couldn't load image %s: %s\n",
	    datafile, IMG_GetError());
    return(NULL);
  }
  if ( transparent ) {
    /* Assuming 8-bit BMP image */
    SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),
		    *(Uint8 *)image->pixels);
  }
  surface = SDL_DisplayFormat(image);
  SDL_FreeSurface(image);
  return(surface);
}
