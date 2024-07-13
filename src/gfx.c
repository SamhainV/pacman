#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "defines.h"
#include "memcpy32.h"
#include "gfx.h"

static struct itimerval oldtimer;
static struct sigaction oldaction;

extern SDL_Surface *screen;
int CntStep, CntStep2, CntStep3;
Uint32 sdl_flags;

void init_gfx(void)
{
    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);

    /* Enter 320x200x256 mode 32 colores*/
    screen = SDL_SetVideoMode(RES_X, RES_Y, DEPTH, sdl_flags);
    if (screen == NULL)
    {
        fprintf(stderr, "Couldn't init video mode: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_WM_SetCaption("PACMAN", NULL);
    /* Oculta el puntero del mouse */
    SDL_ShowCursor(0);
}

/* vuelca el buffer src en dest */
/* El buffer src es lineal */
void flip_screen(SDL_Surface *dest, unsigned char *source)
{
    /* Blit the final image to the screen */
    if (SDL_LockSurface(dest) == 0)
    {
        int row;
        Uint8 *src, *dst;

        src = source;
        dst = (Uint8 *)dest->pixels;
        for (row = dest->h; row > 0; --row)
        {
            memcpy(dst, src, RES_X);
            src += RES_X;
            dst += dest->pitch;
        }
        SDL_UnlockSurface(dest);
    }
    SDL_UpdateRect(dest, 0, 0, 0, 0);
}

/* vuelca el buffer src en dest */
/* El buffer src es lineal */
/* necesita SDL_Flip para actualizar la pantalla */
void fastflip_screen(SDL_Surface *dest, unsigned char *source)
{
    SDL_LockSurface(dest);
    memcpy(dest->pixels, source, 16000);
    SDL_UnlockSurface(dest);
}

void load_screen(void)
{
    SDL_Surface *background;
    SDL_Rect dst;

    background = LoadImage(DATAFILE("ELUGlogo.gif"), 0);

    if (background == NULL)
    {
        /* sale y cierra entorno gráfico atexit(...)  */
        exit(0);
    }

    dst.x = 0;
    dst.y = 0;
    dst.w = background->w;
    dst.h = background->h;

    SDL_BlitSurface(background, NULL, screen, &dst);

    SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void WaitFrame(void)
{
    static Uint32 next_tick = 0;
    Uint32 this_tick;

    /* Wait for the next frame */
    this_tick = SDL_GetTicks();
    if (this_tick < next_tick)
    {
        SDL_Delay(next_tick - this_tick);
    }
    next_tick = this_tick + (1000 / FRAMES_PER_SEC);
}

SDL_Surface *LoadImage(char *datafile, int transparent)
{
    SDL_Surface *image, *surface;

    image = IMG_Load(datafile);
    if (image == NULL)
    {
        fprintf(stderr, "Couldn't load image %s: %s\n", datafile, IMG_GetError());
        return (NULL);
    }
    if (transparent)
    {
        /* Assuming 8-bit BMP image */
        SDL_SetColorKey(image, (SDL_SRCCOLORKEY | SDL_RLEACCEL), *(Uint8 *)image->pixels);
    }
    surface = SDL_DisplayFormat(image);
    SDL_FreeSurface(image);
    return (surface);
}

void putico(int x, int y, UintDEP *source, UintDEP *dest, int tx, int ty)
{
    int sy, sx;

    for (sy = 0; sy < ty; sy++)
        for (sx = 0; sx < tx; sx++)
            dest[(sx + x) + (sy + y) * 320] = source[sx + sy * tx];
}

void TimerStart(void (*handler)(int), int frecuencia)
{
    struct itimerval newtimer;
    struct sigaction action;
    sigset_t blocksignals;

    memset(&blocksignals, 0, sizeof(blocksignals));

    newtimer.it_interval.tv_sec = 0;
    newtimer.it_interval.tv_usec = 1000000.0f / (float)frecuencia; // frecuencia veces por segundo
    newtimer.it_value.tv_sec = 0;
    newtimer.it_value.tv_usec = 1000000.0f / (float)frecuencia;    // frecuencia veces por segundo

    struct itimerval temp_oldtimer = oldtimer;
    setitimer(ITIMER_REAL, &newtimer, &temp_oldtimer);

    action.sa_handler = handler;
    action.sa_mask = blocksignals;
    action.sa_flags = SA_RESTART;
    action.sa_restorer = NULL;

    struct sigaction temp_oldaction = oldaction;
    sigaction(SIGALRM, &action, &temp_oldaction);
}

void TimerStop(void)
{
    struct itimerval temp_oldtimer = oldtimer;
    struct sigaction temp_oldaction = oldaction;
    setitimer(ITIMER_REAL, &temp_oldtimer, &oldtimer);
    sigaction(SIGALRM, &temp_oldaction, &oldaction);
}

void timerfunc(int i)
{
    CntStep++;
    CntStep2++;
    CntStep3++;
}

int keyboard_loop(void)
{
    SDL_Event event;
    Uint8 *keys;
    int done = 1;

    while (done)
    {
        /* Poll input queue, run keyboard loop */
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                return 0;
        }
        keys = SDL_GetKeyState(NULL);

        /* Check for keyboard abort */
        if (keys[SDLK_ESCAPE] == SDL_PRESSED)
        {
            done = 0;
        }
    }
    return done;
}

void fill_buffer(UintDEP *src, UintDEP *dest)
{
    memcpy(dest, src, BYTES);
    /*   memcpy32(dest, src, BYTES); */
}

void getsprite(SDL_Surface *srf, SDL_Rect *rect, UintDEP *dest)
{
    SDL_Rect *rtmp = rect;
    UintDEP *rsrf = srf->pixels;
    UintDEP *ptrdest = dest;
    int j, i;

    if (SDL_LockSurface(srf) == 0)
    {
        for (i = rtmp->y; i < rtmp->y + rtmp->h; i++)
            for (j = rtmp->x; j < rtmp->x + rtmp->w; j++)
                *(ptrdest++) = *(rsrf + j + i * 320);
    }
    SDL_UnlockSurface(srf);
}

void *memcpy32(void *dest, const void *src, size_t n)
{
    return memcpy(dest, src, n);
}
