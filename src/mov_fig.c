#include <math.h>
#include "SDL.h"
#include "defines.h"
#include "gfx.h"
#include "sprites.h"
#include "misc.h"
#include "menuopt.h"

// Conservamos pf[] como estado estático (contador por fantasma)
static int pf[4];

// Helpers para reducir duplicación en fantasmas
// Asumimos que los punteros a sprite tienen tipo UintDEP* (igual que background/putico)
typedef UintDEP* Sprite;

typedef struct {
    Sprite der[2];
    Sprite izq[2];
    Sprite aba[2];
    Sprite arr[2];
} DirSprites;

// Tabla de sprites para cada fantasma en estado NORMAL (0..3)
static const DirSprites GHOST_SPRITES[4] = {
    // who == 0 (azul)
    { { azu1der, azu2der }, { azu1izq, azu2izq }, { azu1aba, azu2aba }, { azu1arr, azu2arr } },
    // who == 1 (rojo)
    { { rojo1der, rojo2der }, { rojo1izq, rojo2izq }, { rojo1aba, rojo2aba }, { rojo1arr, rojo2arr } },
    // who == 2 (amarillo)
    { { ama1der,  ama2der  }, { ama1izq,  ama2izq  }, { ama1aba,  ama2aba  }, { ama1arr,  ama2arr  } },
    // who == 3 (gris)
    { { gris1der, gris2der }, { gris1izq, gris2izq }, { gris1aba, gris2aba }, { gris1arr, gris2arr } }
};

static inline void draw_ghost_normal(int who, float x, float y, int dirX, int dirY, int frame, UintDEP *vaddr) {
    const DirSprites *ds = &GHOST_SPRITES[who];
    if (dirX > 0)      putico(x, y, ds->der [frame], vaddr, 14, 14);
    else if (dirX < 0) putico(x, y, ds->izq [frame], vaddr, 14, 14);
    else if (dirY > 0) putico(x, y, ds->aba [frame], vaddr, 14, 14);
    else if (dirY < 0) putico(x, y, ds->arr [frame], vaddr, 14, 14);
}

static inline void draw_ghost_enfadado(float x, float y, int frame, UintDEP *vaddr) {
    putico(x, y, (frame == 0 ? miedo : miedo2), vaddr, 14, 14);
}

static inline void draw_ghost_muerto(float x, float y, UintDEP *vaddr) {
    putico(x, y, ojos, vaddr, 10, 5);
}

// Helper: actualiza desplazamiento incremental y decide si hay que recalcular posiciones
static inline void advance_axis(float *accum, float delta, float limite, int *need_seek, int *pf_counter) {
    *accum += delta;
    if ((delta > 0 && *accum >  limite) || (delta < 0 && *accum < -limite)) {
        *need_seek = TRUE;
        *accum = *accum; // (sin cambio: mantenemos el acumulado como en el original, solo señalizamos)
        *pf_counter = 0;
    } else {
        *need_seek = FALSE;
    }
}

void mueve_figuras(struct fantasmas *fan, struct pcman *pc)
{
  float xf, yf;
  static float j[4], i[4];      // desplazamientos por fantasma
  static float new_xp, new_yp, old_xp, old_yp; // pcman
  static float jp, ip;          // desplazamientos de pcman
  static int p = 0;
  static float old_inc_x, old_inc_y;
  static int c=0;
  static int control_puntos_fan_muerto=0;
  
  UintDEP *vaddr = background;
  /*****************************************************************/
  /****************** movimientos PCMAN ****************************/
  /*****************************************************************/
  new_xp = COOR_X + (pc->x * 8) - 5;
  new_yp = COOR_Y + (pc->y * 8) - 9;
  old_xp = COOR_X + (pc->old_x * 8) - 5;
  old_yp = COOR_Y + (pc->old_y * 8) - 9;
  if (CntStep3 >= 3) CntStep3 = 0;
  
  if (p == 0) { jp = 0; ip = 0; }
  p++;

  // --- Movimiento en X de PC ---
  if (pc->inc_x == 1) {
    jp += inc_velocidad_pc;
    if      (CntStep3 == 0) putico(old_xp + jp, old_yp, pc_der,  vaddr, 14, 15);
    else if (CntStep3 == 1) putico(old_xp + jp, old_yp, pc_der2, vaddr, 11, 15);
    else { putico(old_xp + jp, old_yp, bola, vaddr, 15, 15); CntStep3 = 0; }
    if (jp == ESCALA) { busca_posiciones_pc = TRUE; p = 0; } else busca_posiciones_pc = FALSE;
  } else if (pc->inc_x == -1) {
    jp -= inc_velocidad_pc;
    if      (CntStep3 == 0) putico(old_xp + jp, old_yp, pc_izq,  vaddr, 14, 15);
    else if (CntStep3 == 1) putico((old_xp + jp)+3, old_yp, pc_izq2, vaddr, 11, 15);
    else { putico(old_xp + jp, old_yp, bola, vaddr, 15, 15); CntStep3 = 0; }
    if (jp == -ESCALA) { busca_posiciones_pc = TRUE; p = 0; } else busca_posiciones_pc = FALSE;
  }

  // --- Movimiento en Y de PC ---
  if (pc->inc_y == 1) {
    ip += inc_velocidad_pc;
    if      (CntStep3 == 0) putico(old_xp, old_yp + ip, pc_aba,  vaddr, 15, 14);
    else if (CntStep3 == 1) putico(old_xp, old_yp + ip, pc_aba2, vaddr, 15, 11);
    else { putico(old_xp, old_yp + ip, bola, vaddr, 15, 15); CntStep3 = 0; }
    if (ip == ESCALA) { busca_posiciones_pc = TRUE; p = 0; } else busca_posiciones_pc = FALSE;
  } else if (pc->inc_y == -1) {
    ip -= inc_velocidad_pc;
    if      (CntStep3 == 0) putico(old_xp, old_yp + ip, pc_arr,  vaddr, 15, 14);
    else if (CntStep3 == 1) putico(old_xp, (old_yp + ip)+3, pc_arr2, vaddr, 15, 11);
    else { putico(old_xp, old_yp + ip, bola, vaddr, 15, 15); CntStep3 = 0; }
    if (ip == -ESCALA) { busca_posiciones_pc = TRUE; p = 0; } else busca_posiciones_pc = FALSE;
  }
  
  // Arrastre cuando inc==0 (mantiene animación hasta encajar en celda)
  if (pc->inc_y == 0.0 && pc->inc_x == 0.0) {
    if (c == 0) { old_inc_x = pc->old_inc_x; old_inc_y = pc->old_inc_y; }
    c++;
    if (old_inc_x == 1) {
      jp += inc_velocidad_pc; putico(old_xp + jp, old_yp, pc_der, vaddr, 14, 15);
      if (jp == ESCALA) { busca_posiciones_pc = TRUE; putico(new_xp, new_yp, bola, vaddr, 15, 15); p = 0; c = 0; } else busca_posiciones_pc = FALSE;
    } else if (old_inc_x == -1) {
      jp -= inc_velocidad_pc; putico(old_xp + jp, old_yp, pc_izq, vaddr, 14, 15);
      if (jp == -ESCALA) { busca_posiciones_pc = TRUE; putico(new_xp, new_yp, bola, vaddr, 15, 15); p = 0; c = 0; } else busca_posiciones_pc = FALSE;
    }
    if (old_inc_y == 1) {
      ip += inc_velocidad_pc; putico(old_xp, old_yp + ip, pc_aba, vaddr, 15, 14);
      if (ip == ESCALA) { busca_posiciones_pc = TRUE; putico(new_xp, new_yp, bola, vaddr, 15, 15); p = 0; c = 0; } else busca_posiciones_pc = FALSE;
    } else if (old_inc_y == -1) {
      ip -= inc_velocidad_pc; putico(old_xp, old_yp + ip, pc_arr, vaddr, 15, 14);
      if (ip == -ESCALA) { busca_posiciones_pc = TRUE; putico(new_xp, new_yp, bola, vaddr, 15, 15); p = 0; c = 0; } else busca_posiciones_pc = FALSE;
    }
    if (old_inc_x == 0.0 && old_inc_y == 0.0) putico(new_xp, new_yp, bola, vaddr, 15, 15);
  } else c = 0;
  
  /*****************************************************************/
  /****************** movimientos FANTASMAS ************************/
  /*****************************************************************/
  // Reinicio de acumuladores cuando toca (pf==0)
  for (int k = 0; k < 4; ++k) { if (pf[k] == 0) { j[k] = 0; i[k] = 0; } }
  for (int k = 0; k < 4; ++k) pf[k]++;

  if (fan->estado_fantasma[0] == NORMAL && fan->estado_fantasma[1] == NORMAL &&
      fan->estado_fantasma[2] == NORMAL && fan->estado_fantasma[3] == NORMAL)
    control_puntos_fan_muerto = 0;

  for (fan->who = 0; fan->who < NUM_GHOTS; fan->who++) {
    int who = fan->who;
    xf = COOR_X + (fan->old_x[who] * 8) - 5;
    yf = COOR_Y + (fan->old_y[who] * 8) - 9;

    // --- Avance en X ---
    if (fan->inc_x[who] > 0.0f) {
      j[who] += inc_velocidad[who];
    } else if (fan->inc_x[who] < 0.0f) {
      j[who] -= inc_velocidad[who];
    }

    // --- Avance en Y ---
    if (fan->inc_y[who] > 0.0f) {
      i[who] += inc_velocidad[who];
    } else if (fan->inc_y[who] < 0.0f) {
      i[who] -= inc_velocidad[who];
    }

    // --- Dibujo del fantasma según estado y dirección ---
    const int frame = (CntStep % 2 == 0) ? 0 : 1;
    if (fan->estado_fantasma[who] == NORMAL) {
      draw_ghost_normal(who, xf + j[who], yf + i[who], (fan->inc_x[who] > 0) - (fan->inc_x[who] < 0), (fan->inc_y[who] > 0) - (fan->inc_y[who] < 0), frame, vaddr);
    } else if (fan->estado_fantasma[who] == ENFADADO) {
      draw_ghost_enfadado(xf + j[who], yf + i[who], frame, vaddr);
    } else if (fan->estado_fantasma[who] == MUERTO) {
      draw_ghost_muerto(xf + j[who], yf + i[who], vaddr);
    }

    // Señalizar cuando superar media celda (8.0) en cualquiera de los ejes para recalcular ruta
    if (fan->inc_x[who] > 0.0f) {
      if (j[who] > 8.0f) { busca_posiciones[who] = TRUE; pf[who] = 0; } else busca_posiciones[who] = FALSE;
    } else if (fan->inc_x[who] < 0.0f) {
      if (j[who] < -8.0f) { busca_posiciones[who] = TRUE; pf[who] = 0; } else busca_posiciones[who] = FALSE;
    }
    if (fan->inc_y[who] > 0.0f) {
      if (i[who] > 8.0f) { busca_posiciones[who] = TRUE; pf[who] = 0; } else busca_posiciones[who] = FALSE;
    } else if (fan->inc_y[who] < 0.0f) {
      if (i[who] < -8.0f){ busca_posiciones[who] = TRUE; pf[who] = 0; } else busca_posiciones[who] = FALSE;
    }

    // --- Colisión PCMAN vs Fantasma (radio ~10 px en X y Y, como el original) ---
    if (fabs((xf + j[who]) - (old_xp + jp + 1)) < 10 && fabs((yf + i[who]) - (old_yp + ip)) < 10) {
      if (fan->estado_fantasma[who] == NORMAL) {
        // PC-MAN muere
        pc->num_vidas--;
        if (pc->num_vidas < 0)
          menu_opciones(FALSE);
        inicializa_structuras(pc, fan, FALSE);
        CntStep2 = 0;
      } else if (fan->estado_fantasma[who] == ENFADADO) {
        // Comer fantasma
        switch (control_puntos_fan_muerto) {
          case 0: writef(xf, yf, vaddr, "%2d", 50 ); pc->puntuacion += 50;  break;
          case 1: writef(xf, yf, vaddr, "%3d", 100); pc->puntuacion += 100; break;
          case 2: writef(xf, yf, vaddr, "%3d", 150); pc->puntuacion += 150; break;
          case 3: writef(xf, yf, vaddr, "%3d", 200); pc->puntuacion += 200; control_puntos_fan_muerto = -1; break;
        }
        fan->estado_fantasma[who] = MUERTO;
        control_puntos_fan_muerto++;
      }
    }
  }
  /***************** Fin movimientos FANTASMAS *********************/
}
