#include <math.h>
#include "SDL.h"
#include "defines.h"
#include "gfx.h"
#include "sprites.h"
#include "misc.h"
#include "menuopt.h"

static int pf[4];

void mueve_figuras(struct fantasmas *fan, struct pcman *pc)
{
  float xf, yf;
  static float j[4], i[4];
  static float new_xp, new_yp, old_xp, old_yp;
  static float jp, ip;
  static int p = 0;
  static float old_inc_x, old_inc_y;
  static int c=0;
  static int control_puntos_fan_muerto=0;
  
  UintDEP *vaddr = background;
  /*****************************************************************/
  /*****************************************************************/
  /****************** movimientos PCMAN ****************************/
  /*****************************************************************/
  /*****************************************************************/
  new_xp = COOR_X + (pc->x * 8) - 5;
  new_yp = COOR_Y + (pc->y * 8) - 9;
  old_xp = COOR_X + (pc->old_x * 8) - 5;
  old_yp = COOR_Y + (pc->old_y * 8) - 9;
  if (CntStep3 >= 3) CntStep3 = 0;
  
  if (p == 0) {
    jp = 0;
    ip = 0;
  };
  
  p++;
  if (pc->inc_x == 1) {
    jp += inc_velocidad_pc;
    if (CntStep3 == 0) 
	putico(old_xp + jp, old_yp, pc_der, vaddr, 14, 15);
    else if (CntStep3 == 1) 
	putico(old_xp + jp, old_yp, pc_der2, vaddr, 11, 15);
    else if (CntStep3 == 2) {
      putico(old_xp + jp, old_yp, bola, vaddr, 15, 15);
      CntStep3 = 0;
    }
    if (jp == ESCALA) {
      busca_posiciones_pc = TRUE;
      p = 0;
    } else busca_posiciones_pc = FALSE;
  } else if (pc->inc_x == -1) {
    jp -= inc_velocidad_pc;
    if (CntStep3 == 0) putico(old_xp + jp, old_yp, pc_izq, vaddr, 14, 15);
    else if (CntStep3 == 1) putico((old_xp + jp)+3, old_yp, pc_izq2, vaddr, 11, 15);
    else if (CntStep3 == 2) {
      putico(old_xp + jp, old_yp, bola, vaddr, 15, 15);
      CntStep3 = 0;
    }
    if (jp == -ESCALA) {
      busca_posiciones_pc = TRUE;
      p = 0;
    } else
      busca_posiciones_pc = FALSE;
  }
  if (pc->inc_y == 1) {
    ip += inc_velocidad_pc;
    if (CntStep3 == 0)  putico(old_xp, old_yp + ip, pc_aba, vaddr, 15, 14);
    if (CntStep3 == 1)  putico(old_xp, old_yp + ip, pc_aba2, vaddr, 15, 11);
    if (CntStep3 == 2) {
      putico(old_xp, old_yp + ip, bola, vaddr, 15, 15);
      CntStep3 = 0;
    };
    if (ip == ESCALA) {
      busca_posiciones_pc = TRUE;
      p = 0;
    } else busca_posiciones_pc = FALSE;
  } else if (pc->inc_y == -1) {
    ip -= inc_velocidad_pc;
    if (CntStep3 == 0)  putico(old_xp, old_yp + ip, pc_arr, vaddr, 15, 14);
    if (CntStep3 == 1)  putico(old_xp, (old_yp + ip)+3, pc_arr2, vaddr, 15, 11);
    if (CntStep3 == 2) {
      putico(old_xp, old_yp + ip, bola, vaddr, 15, 15);
      CntStep3 = 0;
    };
    if (ip == -ESCALA) {
      busca_posiciones_pc = TRUE;
      p = 0;
    } else busca_posiciones_pc = FALSE;
  }
  
  if (pc->inc_y == 0.0 && pc->inc_x == 0.0) {
    if (c == 0) {
      old_inc_x = pc->old_inc_x;
      old_inc_y = pc->old_inc_y;
    }
    c++;
    if (old_inc_x == 1) {
      jp += inc_velocidad_pc;
      putico(old_xp + jp, old_yp, pc_der, vaddr, 14, 15);
      if (jp == ESCALA) {
	busca_posiciones_pc = TRUE;
	putico(new_xp, new_yp, bola, vaddr, 15, 15);
	p = 0;
	c = 0;
      } else busca_posiciones_pc = FALSE;
    } else if (old_inc_x == -1) {
      jp -= inc_velocidad_pc;
      putico(old_xp + jp, old_yp, pc_izq, vaddr, 14, 15);
      if (jp == -ESCALA) {
	busca_posiciones_pc = TRUE;
	putico(new_xp, new_yp, bola, vaddr, 15, 15);
	p = 0;
	c = 0;
      } else
	busca_posiciones_pc = FALSE;
    }
    if (old_inc_y == 1) {
      ip += inc_velocidad_pc;
      putico(old_xp, old_yp + ip, pc_aba, vaddr, 15, 14);
      if (ip == ESCALA) {
	busca_posiciones_pc = TRUE;
	putico(new_xp, new_yp, bola, vaddr, 15, 15);
	p = 0;
	c = 0;
      } else busca_posiciones_pc = FALSE;
    } else if (old_inc_y == -1) {
      ip -= inc_velocidad_pc;
      putico(old_xp, old_yp + ip, pc_arr, vaddr, 15, 14);
      if (ip == -ESCALA) {
	busca_posiciones_pc = TRUE;
	putico(new_xp, new_yp, bola, vaddr, 15, 15);
	p = 0;
	c = 0;
      } else busca_posiciones_pc = FALSE;
    }
    if (old_inc_x == 0.0 && old_inc_y == 0.0)
      putico(new_xp, new_yp, bola, vaddr, 15, 15);
  } else c = 0;
  
  /*****************************************************************/
  /*****************************************************************/
  /***************** Fin movimientos PCMAN *************************/
  /*****************************************************************/
  /*****************************************************************/
  
  /*****************************************************************/
  /*****************************************************************/
  /****************** movimientos FANTASMAS ************************/
  /*****************************************************************/
  /*****************************************************************/
  
  if (pf[0] == 0) {
    j[0] = 0;
    i[0] = 0;
  }
  if (pf[1] == 0) {
    j[1] = 0;
    i[1] = 0;
  }
  if (pf[2] == 0) {
    j[2] = 0;
    i[2] = 0;
  }
  if (pf[3] == 0) {
    j[3] = 0;
    i[3] = 0;
  }
  pf[0]++;
  pf[1]++;
  pf[2]++;
  pf[3]++;
  
  if (fan->estado_fantasma[0] == NORMAL && fan->estado_fantasma[1] == NORMAL &&
      fan->estado_fantasma[2] == NORMAL && fan->estado_fantasma[3] == NORMAL)
    control_puntos_fan_muerto = 0;

  for (fan->who = 0; fan->who < NUM_GHOTS; fan->who++) {
    xf = COOR_X + (fan->old_x[fan->who] * 8) - 5;
    yf = COOR_Y + (fan->old_y[fan->who] * 8) - 9;
    if (fan->inc_x[fan->who] > 0.0) {
      j[fan->who] += inc_velocidad[fan->who];
      if (fan->estado_fantasma[fan->who] == NORMAL) {
	if (fan->who == 0) {
	  if (CntStep % 2 == 0)
	    putico(xf + j[fan->who], yf, azu1der, vaddr, 14, 14);
	  else putico(xf + j[fan->who], yf, azu2der, vaddr, 14, 14);
	  
	}
	else if (fan->who == 1) {
	  if (CntStep % 2 == 0)
	    putico(xf + j[fan->who], yf, rojo1der, vaddr, 14, 14);
	  else
	    putico(xf + j[fan->who], yf, rojo2der, vaddr, 14, 14);
	}
	else if (fan->who == 2) {
	  if (CntStep % 2 == 0)
	    putico(xf + j[fan->who], yf, ama1der, vaddr, 14, 14);
	  else
	    putico(xf + j[fan->who], yf, ama2der, vaddr, 14, 14);
	}
	else if (fan->who == 3) {
	  if (CntStep % 2 == 0)
	    putico(xf + j[fan->who], yf, gris1der, vaddr, 14, 14);
	  else
	    putico(xf + j[fan->who], yf, gris2der, vaddr, 14, 14);
	}
      } else if (fan->estado_fantasma[fan->who] == ENFADADO) {
	if (fan->who == 0)
	  if (CntStep % 2 == 0)
	    putico(xf + j[fan->who], yf, miedo, vaddr, 14, 14);
	  else putico(xf + j[fan->who], yf, miedo2, vaddr, 14, 14);
	else if (fan->who == 1)
	  if (CntStep % 2 == 0)
	    putico(xf + j[fan->who], yf, miedo, vaddr, 14, 14);
	  else putico(xf + j[fan->who], yf, miedo2, vaddr, 14, 14);
	else if (fan->who == 2)
	  if (CntStep % 2 == 0)
	    putico(xf + j[fan->who], yf, miedo, vaddr, 14, 14);
	  else putico(xf + j[fan->who], yf, miedo2, vaddr, 14, 14);
	else if (fan->who == 3)
	  {
	    if (CntStep % 2 == 0)
	      putico(xf + j[fan->who], yf, miedo, vaddr, 14, 14);
	    else putico(xf + j[fan->who], yf, miedo2, vaddr, 14, 14);
	  }
      } else if (fan->estado_fantasma[fan->who] == MUERTO) {
	if (fan->who == 0)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
	else if (fan->who == 1)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
	else if (fan->who == 2)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
	else if (fan->who == 3)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
      }
      if (j[fan->who] > 8.0) {
	busca_posiciones[fan->who] = TRUE;
	pf[fan->who] = 0;
      } else busca_posiciones[fan->who] = FALSE;
    } else if (fan->inc_x[fan->who] < 0.0) {
      j[fan->who] -= inc_velocidad[fan->who];
      if (fan->estado_fantasma[fan->who] == NORMAL) {
	if (fan->who == 0)
	  if (CntStep % 2 == 0)
	    putico(xf + j[fan->who], yf, azu1izq, vaddr, 14, 14);
	  else
	    putico(xf + j[fan->who], yf, azu2izq, vaddr, 14, 14);
	
	else if (fan->who == 1)
	  if (CntStep % 2 == 0)
	    putico(xf + j[fan->who], yf, rojo1izq, vaddr, 14, 14);
	  else
	    putico(xf + j[fan->who], yf, rojo2izq, vaddr, 14, 14);
	else if (fan->who == 2)
	  if (CntStep % 2 == 0)
	    putico(xf + j[fan->who], yf, ama1izq, vaddr, 14, 14);
	  else
	    putico(xf + j[fan->who], yf, ama2izq, vaddr, 14, 14);
	else if (fan->who == 3)
	  {
	    if (CntStep % 2 == 0)
	      putico(xf + j[fan->who], yf, gris1izq, vaddr, 14, 14);
	    else putico(xf + j[fan->who], yf, gris2izq, vaddr, 14, 14);
	  }
	
      } else if (fan->estado_fantasma[fan->who] == ENFADADO) {
	if (fan->who == 0)
	  if (CntStep % 2 == 0)
	    putico(xf + j[fan->who], yf, miedo, vaddr, 14, 14);
	  else putico(xf + j[fan->who], yf, miedo2, vaddr, 14, 14);
	else if (fan->who == 1)
	  if (CntStep % 2 == 0)
	    putico(xf + j[fan->who], yf, miedo, vaddr, 14, 14);
	  else putico(xf + j[fan->who], yf, miedo2, vaddr, 14, 14);
	else if (fan->who == 2)
	  if (CntStep % 2 == 0)
	    putico(xf + j[fan->who], yf, miedo, vaddr, 14, 14);
	  else putico(xf + j[fan->who], yf, miedo2, vaddr, 14, 14);
	else if (fan->who == 3)
	  {
	    if (CntStep % 2 == 0)
	      putico(xf + j[fan->who], yf, miedo, vaddr, 14, 14);
	    else putico(xf + j[fan->who], yf, miedo2, vaddr, 14, 14);
	  }
      } else if (fan->estado_fantasma[fan->who] == MUERTO) {
	if (fan->who == 0)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
	else if (fan->who == 1)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
	else if (fan->who == 2)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
	else if (fan->who == 3)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
      };
      if (j[fan->who] < -8.0) {
	busca_posiciones[fan->who] = TRUE;
	pf[fan->who] = 0;
      } else busca_posiciones[fan->who] = FALSE;
    }
    if (fan->inc_y[fan->who] > 0.0) {
      i[fan->who] += inc_velocidad[fan->who];
      if (fan->estado_fantasma[fan->who] == NORMAL) {
	if (fan->who == 0)
	  if (CntStep % 2 == 0)
	    putico(xf, yf + i[fan->who], azu1aba, vaddr, 14, 14);
	  else
	    putico(xf, yf + i[fan->who], azu2aba, vaddr, 14, 14);
	else if (fan->who == 1)
	  if (CntStep % 2 == 0)
	    putico(xf, yf + i[fan->who], rojo1aba, vaddr, 14, 14);
	  else
	    putico(xf, yf + i[fan->who], rojo2aba, vaddr, 14, 14);
	else if (fan->who == 2)
	  if (CntStep % 2 == 0)
	    putico(xf, yf + i[fan->who], ama1aba, vaddr, 14, 14);
	  else
	    putico(xf, yf + i[fan->who], ama2aba, vaddr, 14, 14);
	else if (fan->who == 3)
	  {
	    if (CntStep % 2 == 0)
	      putico(xf, yf + i[fan->who], gris1aba, vaddr, 14, 14);
	    else
	      putico(xf, yf + i[fan->who], gris2aba, vaddr, 14, 14);
	  }
      } else if (fan->estado_fantasma[fan->who] == ENFADADO) {
	if (fan->who == 0)
	  if (CntStep % 2 == 0)
	    putico(xf, yf + i[fan->who], miedo, vaddr, 14, 14);
	  else putico(xf, yf + i[fan->who], miedo2, vaddr, 14, 14);
	else if (fan->who == 1)
	  if (CntStep % 2 == 0)
	    putico(xf, yf + i[fan->who], miedo, vaddr, 14, 14);
	  else putico(xf, yf + i[fan->who], miedo2, vaddr, 14, 14);
	else if (fan->who == 2)
	  if (CntStep % 2 == 0)
	    putico(xf, yf + i[fan->who], miedo, vaddr, 14, 14);
	  else putico(xf, yf + i[fan->who], miedo2, vaddr, 14, 14);
	else if (fan->who == 3)
	  {
	    if (CntStep % 2 == 0)
	      putico(xf, yf + i[fan->who], miedo, vaddr, 14, 14);
	    else putico(xf, yf + i[fan->who], miedo2, vaddr, 14, 14);
	  }
      } else if (fan->estado_fantasma[fan->who] == MUERTO) {
	if (fan->who == 0)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
	else if (fan->who == 1)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
	else if (fan->who == 2)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
	else if (fan->who == 3)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
      };
      if (i[fan->who] > 8.0) {
	busca_posiciones[fan->who] = TRUE;
	pf[fan->who] = 0;
      } else busca_posiciones[fan->who] = FALSE;
    } else if (fan->inc_y[fan->who] < 0.0) {
      i[fan->who] -= inc_velocidad[fan->who];
      if (fan->estado_fantasma[fan->who] == NORMAL) {
	if (fan->who == 0)
	  if (CntStep % 2 == 0)
	    putico(xf, yf + i[fan->who], azu1arr, vaddr, 14, 14);
	  else
	    putico(xf, yf + i[fan->who], azu2arr, vaddr, 14, 14);
	else if (fan->who == 1)
	  if (CntStep % 2 == 0)
	    putico(xf, yf + i[fan->who], rojo1arr, vaddr, 14, 14);
	  else
	    putico(xf, yf + i[fan->who], rojo2arr, vaddr, 14, 14);
	else if (fan->who == 2)
	  {
	    if (CntStep % 2 == 0)
	      putico(xf, yf + i[fan->who], ama1arr, vaddr, 14, 14);
	    else
	      putico(xf, yf + i[fan->who], ama2arr, vaddr, 14, 14);
	  }
	else if (fan->who == 3)
	  {
	    if (CntStep % 2 == 0)
	      putico(xf, yf + i[fan->who], gris1arr, vaddr, 14, 14);
	    else
	      putico(xf, yf + i[fan->who], gris2arr, vaddr, 14, 14);
	  }
      } else if (fan->estado_fantasma[fan->who] == ENFADADO) {
	if (fan->who == 0)
	  if (CntStep % 2 == 0)
	    putico(xf, yf + i[fan->who], miedo, vaddr, 14, 14);
	  else putico(xf, yf + i[fan->who], miedo2, vaddr, 14, 14);
	else if (fan->who == 1)
	  if (CntStep % 2 == 0)
	    putico(xf, yf + i[fan->who], miedo, vaddr, 14, 14);
	  else putico(xf, yf + i[fan->who], miedo2, vaddr, 14, 14);
	else if (fan->who == 2)
	  {
	    if (CntStep % 2 == 0)
	      putico(xf, yf + i[fan->who], miedo, vaddr, 14, 14);
	    else putico(xf, yf + i[fan->who], miedo2, vaddr, 14, 14);
	  }
	else if (fan->who == 3) 
	  {
	    if (CntStep % 2 == 0)
	      putico(xf, yf + i[fan->who], miedo, vaddr, 14, 14);
	    else putico(xf, yf + i[fan->who], miedo2, vaddr, 14, 14);
	  }
      } else if (fan->estado_fantasma[fan->who] == MUERTO) {
	if (fan->who == 0)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
	else if (fan->who == 1)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
	else if (fan->who == 2)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
	else if (fan->who == 3)
	  putico(xf + j[fan->who], yf, ojos, vaddr, 10, 5);
      };
      if (i[fan->who] < - 8.0) {
	busca_posiciones[fan->who] = TRUE;
	pf[fan->who] = 0;
      } else busca_posiciones[fan->who] = FALSE;
    };
    /* 10 en x y 10 en y*/
    if (fabs(xf + j[fan->who] - (old_xp + jp + 1)) < 10 &&
	fabs(yf + i[fan->who] - (old_yp + ip)) < 10)
      {
	if (fan->estado_fantasma[fan->who] == NORMAL) {
	  /* PC-MAN muerto */
	  pc->num_vidas--;
	  if (pc->num_vidas < 0) 
	    menu_opciones(FALSE);
	  inicializa_structuras(pc, fan, FALSE);
	  CntStep2 = 0;
	} else if (fan->estado_fantasma[fan->who] == ENFADADO) {
	  /************************************************************/
	  /* Aqui controlaremos que hacer cuando comemos un fantasma  */
	  /************************************************************/
	  switch(control_puntos_fan_muerto) {
	  case 0:
	    writef(xf, yf, vaddr, "%2d", 50);
	    pc->puntuacion+=50;
	    break;
	  case 1:
	    writef(xf, yf, vaddr, "%3d", 100);
	    pc->puntuacion+=100;
	    break;
	  case 2:
	    writef(xf, yf, vaddr, "%3d", 150);
	    pc->puntuacion+=150;
	    break;
	  case 3:
	    writef(xf, yf, vaddr, "%3d", 200);
	    pc->puntuacion+=200;
	    control_puntos_fan_muerto = -1;
	    break;
	  }
	  
	  fan->estado_fantasma[fan->who] = MUERTO;
	  control_puntos_fan_muerto++;
	};
      };
  };
  /*****************************************************************/
  /*****************************************************************/
  /***************** Fin movimientos FANTASMAS *********************/
  /*****************************************************************/
  /*****************************************************************/
}
