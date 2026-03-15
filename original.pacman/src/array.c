/*
    Este m¢dulo realiza las operaciones pertinentes con los arrays.
    Este m¢dulo contiene el array propiamente dicho y las siguientes
  funciones de apoyo:
    - void rellena_array(void);
    Esta funci¢n se encarga de leer el array y dibujar en una pantalla
  virtual al contenido de este.
*/

#include "defines.h"
#include "sprites.h"


float c_array[MAXY_A*MAXX_A];
float array[MAXY_A*MAXX_A] = {
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

void copyarray(void)
{
int j;
  for (j = 0; j < MAXX_A * MAXY_A; j++)
    c_array[j] = array[j];
}

void pon_puntos_en_pantalla(void)
{
/*int j, i;
  for (i = 0; i < MAXY_A; i++)
    for (j = 0; j < MAXX_A; j++) {
      if (c_array[j + i * MAXX_A] == C) {
	putico3(COOR_X + (j * 8), COOR_Y + (i * 8)-3, punto, background, 4, 4, 1);
      }
    }*/
}
