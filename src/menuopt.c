#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "SDL.h"
#include "defines.h"
#include "gfx.h"
#include "fantasmas.h"
#include "pacman.h"
#include "sprites.h"
#include "memcpy32.h"
#include "misc.h"

#define DELAY 3         // Milisegundos de espera (framerate)
#define INC_I 0.4       // Incremento de movimiento inicial

// Prototipos
void inicializar_posiciones(int x[], int y[]);
void procesar_eventos(SDL_Event *event, int *done, Uint8 **keys);
void dibujar_portada(SDL_Surface *portada, UintDEP *buffer, int portada_x_y[], int *iport);
void actualizar_pantalla(UintDEP *buffer);
void dibujar_fantasmas(UintDEP *buffer, int x[], int y[], float i, int portada_x_y[], int iport);
void procesar_teclas(Uint8 *keys, int *done, float *i, float *inc_i);
void gestionar_dibujo(UintDEP *buffer, float i, float inc_i, int x[], int y[], int portada_x_y[], int iport);

// Menú principal
int menu_opciones(int value) {
    SDL_Surface *portada;
    SDL_Event event;
    Uint8 *keys = NULL;
    int done = 1;
    int x[4], y[4];
    float i = 300, inc_i = INC_I;
    UintDEP *buffer = background;

    int portada_x_y[] = {
        85, 5, 150, 32,      // Pacman rotulo
        38, 50, 243, 21,     // character_nickname
        69, 79, 62, 14,      // nagosia
        200, 79, 62, 12,     // Beltzak
        69, 106, 45, 15,     // azkar
        200, 106, 35, 10,    // aMoK
        69, 131, 53, 12,     // w-izar
        200, 131, 69, 14,    // Gipon
        69, 157, 69, 12,     // gautxori
        200, 157, 62, 12,    // chamber
        74, 180, 171, 16     // Press_space
    };
    int iport = 0;

    inicializar_posiciones(x, y);

    portada = LoadImage("data/portada.bmp", 0);
    SDL_BlitSurface(portada, NULL, screen, NULL);

    if (SDL_MUSTLOCK(screen) && SDL_LockSurface(screen) < 0) exit(0);

    bzero(buffer, RES_XB * RES_YB * BPP);
    bzero(screen->pixels, screen->w * screen->h * BPP);
    clearkbd(keys);

    dibujar_portada(portada, buffer, portada_x_y, &iport);

    if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

    do {
        procesar_eventos(&event, &done, &keys);
        procesar_teclas(keys, &done, &i, &inc_i);

        if (SDL_MUSTLOCK(screen) && SDL_LockSurface(screen) < 0) exit(0);

        gestionar_dibujo(buffer, i, inc_i, x, y, portada_x_y, iport);
        actualizar_pantalla(buffer);

        SDL_Delay(DELAY);
    } while (done);

    clearkbd(keys);
    return 0;
}

void inicializar_posiciones(int x[], int y[]) {
    for (int i = 0; i < 4; i++) {
        x[i] = 305;
    }
    y[0] = 79;
    y[1] = 106;
    y[2] = 131;
    y[3] = 157;
}

void procesar_eventos(SDL_Event *event, int *done, Uint8 **keys) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            *done = 0;
            return;
        }
    }
    *keys = SDL_GetKeyState(NULL);
}

void dibujar_portada(SDL_Surface *portada, UintDEP *buffer, int portada_x_y[], int *iport) {
    putico(portada_x_y[*iport], portada_x_y[*iport + 1], Pacman_rotulo, buffer,
           portada_x_y[*iport + 2], portada_x_y[*iport + 3]);
    *iport += 4;
    putico(portada_x_y[*iport], portada_x_y[*iport + 1], character_nickname, buffer,
           portada_x_y[*iport + 2], portada_x_y[*iport + 3]);
    *iport += 4;
}

void actualizar_pantalla(UintDEP *buffer) {
    memcpy(screen->pixels, buffer, BYTES3);
    if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
    SDL_Flip(screen);
    memset(buffer + 25280, 0, 55040 * sizeof(UintDEP));
}

void dibujar_fantasmas(UintDEP *buffer, int x[], int y[], float i, int portada_x_y[], int iport) {
    if (CntStep2 % 10 > 5) {
        putico(x[0] + i, y[0], rojo1izq, buffer, 14, 14);
        putico(x[1] + i, y[1], azu2izq, buffer, 14, 14);
        putico(x[2] + i, y[2], gris1izq, buffer, 14, 14);
        putico(x[3] + i, y[3], ama2izq, buffer, 14, 14);
    } else {
        putico(portada_x_y[iport + 32], portada_x_y[iport + 33], Press_space, buffer,
               portada_x_y[iport + 34], portada_x_y[iport + 35]);

        putico(x[0] + i, y[0], rojo2izq, buffer, 14, 14);
        putico(x[1] + i, y[1], azu1izq, buffer, 14, 14);
        putico(x[2] + i, y[2], gris2izq, buffer, 14, 14);
        putico(x[3] + i, y[3], ama1izq, buffer, 14, 14);
    }
}

void procesar_teclas(Uint8 *keys, int *done, float *i, float *inc_i) {
    if (keys[SDLK_SPACE]) {
        *done = 0;
    } else if (keys[SDLK_ESCAPE]) {
        exit(1);
    }

    *i -= *inc_i;
    if (*i <= 60) {
        *inc_i = 0;
        if (CntStep % 150 >= 140) {
            *i = 305;
            *inc_i = INC_I;
        }
    } else {
        CntStep = 0;
    }
}

void gestionar_dibujo(UintDEP *buffer, float i, float inc_i, int x[], int y[], int portada_x_y[], int iport) {
    if (inc_i) {
        dibujar_fantasmas(buffer, x, y, i, portada_x_y, iport);
    } else {
        if (CntStep2 % 10 > 5) {
            putico(x[0] + i, y[0], rojo1der, buffer, 14, 14);
            putico(x[1] + i, y[1], azu2der, buffer, 14, 14);
            putico(x[2] + i, y[2], gris1der, buffer, 14, 14);
            putico(x[3] + i, y[3], ama2der, buffer, 14, 14);
        } else {
            putico(portada_x_y[iport + 32], portada_x_y[iport + 33], Press_space, buffer,
                   portada_x_y[iport + 34], portada_x_y[iport + 35]);

            putico(x[0] + i, y[0], rojo2der, buffer, 14, 14);
            putico(x[1] + i, y[1], azu1der, buffer, 14, 14);
            putico(x[2] + i, y[2], gris2der, buffer, 14, 14);
            putico(x[3] + i, y[3], ama1der, buffer, 14, 14);
        }

        // Nombres
        putico(portada_x_y[iport], portada_x_y[iport + 1], nagosia, buffer,
               portada_x_y[iport + 2], portada_x_y[iport + 3]);
        putico(portada_x_y[iport + 4], portada_x_y[iport + 5], Beltzak, buffer,
               portada_x_y[iport + 6], portada_x_y[iport + 7]);
        putico(portada_x_y[iport + 8], portada_x_y[iport + 9], azkar, buffer,
               portada_x_y[iport + 10], portada_x_y[iport + 11]);
        putico(portada_x_y[iport + 12], portada_x_y[iport + 13], aMoK, buffer,
               portada_x_y[iport + 14], portada_x_y[iport + 15]);
        putico(portada_x_y[iport + 16], portada_x_y[iport + 17], w_izar, buffer,
               portada_x_y[iport + 18], portada_x_y[iport + 19]);
        putico(portada_x_y[iport + 20], portada_x_y[iport + 21], Gipon, buffer,
               portada_x_y[iport + 22], portada_x_y[iport + 23]);
        putico(portada_x_y[iport + 24], portada_x_y[iport + 25], gautxori, buffer,
               portada_x_y[iport + 26], portada_x_y[iport + 27]);
        putico(portada_x_y[iport + 28], portada_x_y[iport + 29], Chamber, buffer,
               portada_x_y[iport + 30], portada_x_y[iport + 31]);
    }
}
