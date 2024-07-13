/*
  Este módulo se encarga de controlar los movimientos del pacman
  a través del teclado.
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "SDL.h"
#include "defines.h"
#include "sprites.h"
#include "gfx.h"
#include "misc.h"

int teclado(void) {
    SDL_Event event;
    Uint8 *keys;
    int done = 1;
    UintDEP *vaddr = background;
    int xp, yp;
    int arr_pulsada = 0, aba_pulsada = 0, der_pulsada = 0, izq_pulsada = 0;
    int alea[2];
    int xf, yf;
    unsigned int CntStep4;

    bzero(screen->pixels, RES_X * RES_Y * BPP);

    // Inicializar posiciones iniciales de Pacman y los fantasmas
    inicializar_posiciones(vaddr);

    while (done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return 0;
        }

        keys = SDL_GetKeyState(NULL);

        // Check for keyboard abort
        if (keys[SDLK_ESCAPE]) {
            done = 0;
        }

        if (SDL_MUSTLOCK(screen)) {
            if (SDL_LockSurface(screen) < 0)
                exit(0);
        }

        actualizar_movimiento_pacman(keys, &arr_pulsada, &aba_pulsada, &der_pulsada, &izq_pulsada);

        verificar_bolones_asusta_fantasmas(&xp, &yp);

        actualizar_tiempo_asustados();

        escribir_puntuacion(tablero->pixels);

        // Control de movimiento de fantasmas
        optener_movimientos_fantasmas(&fan, &pc);
        controlar_astucia_fantasmas(alea);

        mueve_figuras(&fan, &pc);
        actualizar_busca_posiciones();

        // Actualización de la pantalla
        actualizar_pantalla(vaddr);

        SDL_Flip(screen);
    }
    return 0;
}

void inicializar_posiciones(UintDEP *vaddr) {
    putico(COOR_X + (pc.x * 8) - 5, COOR_Y + (pc.y * 8) - 9, pc_arr, vaddr, 15, 14);
    int xf = COOR_X + (fan.x[0] * 8) - 5;
    int yf = COOR_Y + (fan.y[0] * 8) - 9;
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
}

void actualizar_movimiento_pacman(Uint8 *keys, int *arr_pulsada, int *aba_pulsada, int *der_pulsada, int *izq_pulsada) {
    pc.old_inc_x = pc.inc_x;
    pc.old_inc_y = pc.inc_y;

    if (busca_posiciones_pc == TRUE) {
        if (keys[SDLK_UP]) {
            reset_pulsaciones(arr_pulsada, aba_pulsada, der_pulsada, izq_pulsada);
            pc.yf = ((pc.y - 1) * 32);
            pc.dir = pc.x + pc.yf;
            if (c_array[(int)pc.dir] != 0.0 && c_array[(int)pc.dir] != P) {
                pc.inc_y = -1;
                pc.inc_x = 0;
            } else {
                *arr_pulsada = 1;
            }
        }
        if (keys[SDLK_DOWN]) {
            reset_pulsaciones(arr_pulsada, aba_pulsada, der_pulsada, izq_pulsada);
            pc.yf = ((pc.y + 1) * 32);
            pc.dir = pc.x + pc.yf;
            if (c_array[(int)pc.dir] != 0 && c_array[(int)pc.dir] != P) {
                pc.inc_y = 1;
                pc.inc_x = 0;
            } else {
                *aba_pulsada = 1;
            }
        }
        if (keys[SDLK_RIGHT]) {
            reset_pulsaciones(arr_pulsada, aba_pulsada, der_pulsada, izq_pulsada);
            pc.yf = (pc.y * 32);
            pc.dir = pc.x + 1 + pc.yf;
            if (c_array[(int)pc.dir] != 0 && c_array[(int)pc.dir] != P) {
                pc.inc_x = 1;
                pc.inc_y = 0;
            } else {
                *der_pulsada = 1;
            }
        }
        if (keys[SDLK_LEFT]) {
            reset_pulsaciones(arr_pulsada, aba_pulsada, der_pulsada, izq_pulsada);
            pc.yf = (pc.y * 32);
            pc.dir = (pc.x - 1) + pc.yf;
            if (c_array[(int)pc.dir] != 0 && c_array[(int)pc.dir] != P) {
                pc.inc_x = -1;
                pc.inc_y = 0;
            } else {
                *izq_pulsada = 1;
            }
        }

        verificar_colisiones_pacman(arr_pulsada, aba_pulsada, der_pulsada, izq_pulsada);
        verificar_tuneles();
    }
}

void reset_pulsaciones(int *arr_pulsada, int *aba_pulsada, int *der_pulsada, int *izq_pulsada) {
    *arr_pulsada = 0;
    *aba_pulsada = 0;
    *der_pulsada = 0;
    *izq_pulsada = 0;
}

void verificar_colisiones_pacman(int *arr_pulsada, int *aba_pulsada, int *der_pulsada, int *izq_pulsada) {
    pc.yf = ((pc.y - 1) * 32);
    if (*arr_pulsada == 1 && c_array[(int)(pc.x + (pc.yf))] != 0 && c_array[(int)(pc.x + (pc.yf))] != P) {
        *arr_pulsada = 0;
        pc.inc_y = -1;
        pc.inc_x = 0;
    }

    pc.yf = ((pc.y + 1) * 32);
    if (*aba_pulsada == 1 && c_array[(int)(pc.x + (pc.yf))] != 0 && c_array[(int)(pc.x + (pc.yf))] != P) {
        *aba_pulsada = 0;
        pc.inc_y = 1;
        pc.inc_x = 0;
    }

    pc.yf = (pc.y * 32);
    if (*der_pulsada == 1 && c_array[(int)(pc.x + 1 + pc.yf)] != 0 && c_array[(int)(pc.x + 1 + pc.yf)] != P) {
        *der_pulsada = 0;
        pc.inc_y = 0;
        pc.inc_x = 1;
    }

    pc.yf = (pc.y * 32);
    if (*izq_pulsada == 1 && c_array[(int)((pc.x - 1) + pc.yf)] != 0 && c_array[(int)((pc.x - 1) + pc.yf)] != P) {
        *izq_pulsada = 0;
        pc.inc_y = 0;
        pc.inc_x = -1;
    }
}

void verificar_tuneles() {
    if (pc.x == 16 && pc.y == 1) {
        pc.x = 16;
        pc.y = 24;
        pc.inc_y = -1;
    } else if (pc.x == 16 && pc.y == 24) {
        pc.x = 16;
        pc.y = 1;
        pc.inc_y = 1;
    }
}

void verificar_bolones_asusta_fantasmas(int *xp, int *yp) {
    if (c_array[(int)(pc.x + (pc.y * 32))] == B) {
        c_array[(int)(pc.x + (pc.y * 32))] = J;
        *xp = COOR_X + (pc.x * 8) - 6;
        *yp = COOR_Y + (pc.y * 8) - 9;
        putico(*xp + 3, *yp + 2, bak_asusta, tablero->pixels, 10, 10);
        pc.estado_pcman = ENFADADO;
        for (int i = 0; i < 4; ++i) {
            if (fan.estado_fantasma[i] == NORMAL)
                fan.estado_fantasma[i] = ENFADADO;
        }
        pc.puntuacion += 50;
        CntStep = 0;
    }
}

void actualizar_tiempo_asustados() {
    CntStep4 = CntStep % 12;
    if (CntStep4 >= 0 && CntStep4 <= 5) {
        mostrar_asusta_fantasmas(bak_asusta);
    } else if (CntStep4 >= 6 && CntStep4 <= 11) {
        mostrar_asusta_fantasmas(asusta);
    }

    if (pc.estado_pcman == ENFADADO && CntStep >= pc.tiempo) {
        pc.estado_pcman = NORMAL;
        for (int i = 0; i < 4; ++i) {
            if (fan.estado_fantasma[i] == ENFADADO)
                fan.estado_fantasma[i] = NORMAL;
        }
    }
}

void mostrar_asusta_fantasmas(UintDEP *sprite) {
    if (c_array[7 + 1 * 32] == B)
        putico(108, 3, sprite, tablero->pixels, 10, 10);
    if (c_array[7 + 24 * 32] == B)
        putico(108, 187, sprite, tablero->pixels, 10, 10);
    if (c_array[27 + 1 * 32] == B)
        putico(268, 3, sprite, tablero->pixels, 10, 10);
    if (c_array[27 + 24 * 32] == B)
        putico(268, 187, sprite, tablero->pixels, 10, 10);
}

void escribir_puntuacion(UintDEP *pixels) {
    writef(40, 25, pixels, "%5d", pc.puntuacion);

    if (c_array[(int)(pc.x + (pc.y * 32))] == C) {
        c_array[(int)(pc.x + (pc.y * 32))] = J;
        int xp = COOR_X + (pc.x * 8) - 6;
        int yp = COOR_Y + (pc.y * 8) - 8;
        putico(xp + 6, yp + 4, punto_negro, pixels, 4, 4);
        pc.puntos--;
        pc.puntuacion += 10;
        if (pc.puntos == 0) {
            adelanta_nivel(&fan, &pc);
        }
    }

    pc.old_x = pc.x;
    pc.old_y = pc.y;

    pc.x += pc.inc_x;
    pc.y += pc.inc_y;

    verificar_colisiones_paredes();
}

void verificar_colisiones_paredes() {
    pc.yf = (pc.y * 32);
    if (c_array[(int)floor((pc.x + pc.inc_x) + pc.yf)] == 0 || c_array[(int)floor((pc.x + pc.inc_x) + pc.yf)] == P)
        pc.inc_x = 0.0;
    else if (c_array[(int)floor((pc.x - pc.inc_x) + pc.yf)] == 0 || c_array[(int)floor((pc.x - pc.inc_x) + pc.yf)] == P)
        pc.inc_x = 0.0;
    pc.yf = ((pc.y + pc.inc_y) * 32);
    if (c_array[(int)floor(pc.x + pc.yf)] == 0 || c_array[(int)floor(pc.x + pc.yf)] == P)
        pc.inc_y = 0.0;
    else if (c_array[(int)floor(pc.x + (((pc.y - pc.inc_y) * 32)))] == 0 || c_array[(int)floor(pc.x + (((pc.y - pc.inc_y) * 32)))] == P)
        pc.inc_y = 0.0;
}

void controlar_astucia_fantasmas(int *alea) {
    for (int i = 0; i < 4; ++i) {
        if (fan.estado_fantasma[i] == NORMAL) {
            if (i == 0) {
                fan.find_x[i] = pc.old_x;
                fan.find_y[i] = pc.old_y;
            } else if (i == 1) {
                fan.find_x[i] = pc.x;
                fan.find_y[i] = pc.y;
            } else if (i == 2 || i == 3) {
                if (fabs(pc.x - fan.x[i]) < 9 && fabs(pc.y - fan.y[i]) < 9) {
                    fan.find_x[i] = pc.x;
                    fan.find_y[i] = pc.y;
                } else {
                    fan.find_x[i] = rand() % MAXX_A;
                    fan.find_y[i] = rand() % MAXY_A;
                }
            }
        } else if (fan.estado_fantasma[i] == ENFADADO) {
            alea[0] = rand() % MAXX_A;
            alea[1] = rand() % MAXY_A;
            fan.find_x[i] = alea[0];
            fan.find_y[i] = alea[1];
        } else {
            fan.find_x[i] = 16;
            fan.find_y[i] = 12;
        }
    }
}

void actualizar_busca_posiciones() {
    for (int i = 0; i < 4; ++i) {
        if (busca_posiciones[i] == TRUE) {
            if (fan.x[i] == 17 && fan.y[i] == 12 && fan.estado_fantasma[i] == NORMAL) {
                if (CntStep2 >= 50 * (i + 1) && CntStep2 <= 50 * (i + 2)) {
                    fan.find_x[i] = 19;
                    fan.find_y[i] = 12;
                    fan.inc_x[i] = 1;
                    fan.inc_y[i] = 0;
                } else {
                    fan.find_x[i] = 15;
                    fan.find_y[i] = 12;
                }
            }
        }
    }
}

void actualizar_pantalla(UintDEP *vaddr) {
    fill_buffer(vaddr, screen->pixels + ((6400) * sizeof(UintDEP))); /* 6400 = 320 * 20 */
    memcpy32(vaddr, tablero->pixels, BYTES);
    if (SDL_MUSTLOCK(screen)) {
        SDL_UnlockSurface(screen);
    }
}
