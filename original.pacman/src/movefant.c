/*
    He visto en dos PCMAN's hechos en basic que una determinante para atrapar
  al PCMAN por parte de los FANTASMAS es mirar si el siguiente punto del
  array está vacio, ó vale distinto del valor original lo que indica que el
  PCMAN ya ha pasado por alli.
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defines.h"
/*#include "pacman.h"*/
#include "misc.h"
#include "gfx.h"
/*
   La direcci�n debe de ser x + y * 320 pero al ser el array de 32 * 26
 la direcci�n ser� x + y * 32
   Al ser el array de 32 caracteres de ancho para calcular la direcci�n
 de un elemento utilizaremos el operador de desplazamiento (x + (y * 32))
 evitando una multiplizaci�n la cual cosume muchos pulsos de reloj.
 128 64 32 16  8  4  2  1
   0  0  1  0  0  0  0  0
   Este m�dulo contiene la funci�n:
     - void mueve_fantasmas(struct fantasmas *fan, struct pcman *pc);
   La cual utiliza un algoritmo de busqueda de puntos en el array
*/

int truex(int value, struct fantasmas *fan)
{
	if (value == -1 &&
		c_array[(int)((fan->y[fan->who] * 32) + (fan->x[fan->who] + value))] == P)
		return 0;
	else
		return (c_array[(int)((fan->y[fan->who] * 32) + (fan->x[fan->who] + value))]);
}

int truey(int value, struct fantasmas *fan)
{
	return (c_array[(int)(((fan->y[fan->who] + value) * 32) + fan->x[fan->who])]);
}

/*
    Cuando el eje de Y del fantasma es igual a Y del pcman el fantasma
  debe de seguir por donde va a no ser que:

  - No pueda avanzar pues el circuito se acabe.
  - Si el circuito se acaba debemos de optar a continuar por el eje de
  ies que se pueda, esto lo haremos de forma aleatoria.


  - Tenemos de tener cuidado a la hora de comprobar el eje de las X
  este es m�s complicado y tenemos que hacer m�s comprobaciones.

  ***********************************************************************

  - Si el eje de X del fantasma es igual al eje de X del pcman

  1� En esta fase de prueba lo vamos a hacer aleatorio como pasaba
  cuando Y del fantasma era igual a Y del pcman.

  Seguiremos moviendo Y a menos que nos encontremos un obst�culo
  Si encontramos un obst�culo moveremos por el eje de X que se pueda.
*/

int comprueba_distancias_y(struct fantasmas *fan)
{
	int value;

	if (fan->find_x[fan->who] != 15 && fan->find_y[fan->who] != 12)
	{
		if (fabs(fan->y[fan->who] - fan->find_y[fan->who]) <= 10 ||
			fan->who == 0 ||
			fan->who == 1 ||
			fan->who == 2 ||
			fan->who == 3)
		{
			value = 1;
		}
		else
			value = 0;
	}
	else
	{
		if (fabs(fan->y[fan->who] - fan->find_y[fan->who]) <= 10)
			value = 1;
		else
			value = 0;
	}
	return value;
}

int comprueba_distancias_x(struct fantasmas *fan)
{
	int value;
	if (fan->find_x[fan->who] != 15 && fan->find_y[fan->who] != 12)
	{
		if (fabs(fan->x[fan->who] - fan->find_x[fan->who]) <= 10 ||
			fan->who == 0 ||
			fan->who == 1 ||
			fan->who == 2 ||
			fan->who == 3)
		{
			value = 1;
		}
		else
			value = 0;
	}
	else
	{
		if (fabs(fan->x[fan->who] - fan->find_x[fan->who]) <= 10)
			value = 1;
		else
			value = 0;
	}
	return value;
}

/* Valores aleatorios sabiendo que el �ltimo movimiento realizado fue de X */
/* y que Y es mayor � menor que Y a encontrar */
void devuelve_valores_aleatorios_x(struct fantasmas *fan)
{
	int alea_t;
	fan->inc_x[fan->who] = 0;
	fan->inc_y[fan->who] = 0;
	if (truey(-1, fan) &&
		truey(1, fan) &&
		truex(fan->old_mov_x[fan->who], fan))
	{
		alea_t = rand() % 30;

		if (alea_t >= 0 && alea_t <= 9)
			fan->inc_y[fan->who] = 1;
		else if (alea_t >= 10 && alea_t <= 19)
			fan->inc_y[fan->who] = -1;
		else if (alea_t >= 20 && alea_t <= 29)
			fan->inc_x[fan->who] = fan->old_mov_x[fan->who];
	}
	else
	{
		if (!truex(fan->old_mov_x[fan->who], fan) && truey(-1, fan) && truey(1, fan))
		{
			alea_t = rand() % 30;

			if (alea_t >= 0 && alea_t <= 14)
				fan->inc_y[fan->who] = -1;
			else
				fan->inc_y[fan->who] = 1;
		}
		else
		{
			if (!truex(fan->old_mov_x[fan->who], fan) && truey(-1, fan) && !truey(1, fan))
			{
				fan->inc_y[fan->who] = -1;
			}
			else
			{
				if (!truex(fan->old_mov_x[fan->who], fan) && !truey(-1, fan) && truey(1, fan))
				{
					fan->inc_y[fan->who] = 1;
				}
				else
				{
					if (truex(fan->old_mov_x[fan->who], fan) && !truey(-1, fan) && !truey(1, fan))
					{
						fan->inc_x[fan->who] = fan->old_mov_x[fan->who];
					}
					else
					{
						if (truex(fan->old_mov_x[fan->who], fan) && truey(-1, fan) && !truey(1, fan))
						{

							alea_t = rand() % 30;
							if (alea_t >= 0 && alea_t <= 14)
								fan->inc_y[fan->who] = -1;
							else
								fan->inc_x[fan->who] = fan->old_mov_x[fan->who];
						}
						else
						{
							if (truex(fan->old_mov_x[fan->who], fan) && !truey(-1, fan) && truey(1, fan))
							{
								alea_t = rand() % 30;

								if (alea_t >= 0 && alea_t <= 14)
									fan->inc_y[fan->who] = 1;
								else
									fan->inc_x[fan->who] = fan->old_mov_x[fan->who];
							}
						}
					}
				}
			}
		}
	}
}

/* Valores aleatorios sabiendo que el �ltimo movimiento realizado fue de Y */
/* y que X es mayor � menor que X a encontrar */
void devuelve_valores_aleatorios_y(struct fantasmas *fan)
{
	int alea_t;

	fan->inc_y[fan->who] = 0;
	fan->inc_x[fan->who] = 0;

	if (truex(-1, fan) &&
		truex(1, fan) &&
		truey(fan->old_mov_y[fan->who], fan))
	{
		alea_t = rand() % 30;

		if (alea_t >= 0 && alea_t <= 9)
			fan->inc_x[fan->who] = 1;
		else if (alea_t >= 10 && alea_t <= 19)
			fan->inc_x[fan->who] = -1;
		else if (alea_t >= 20 && alea_t <= 29)
			fan->inc_y[fan->who] = fan->old_mov_y[fan->who];
	}
	else
	{
		if (!truey(fan->old_mov_y[fan->who], fan) && truex(-1, fan) && truex(1, fan))
		{
			alea_t = rand() % 30;

			if (alea_t >= 0 && alea_t <= 14)
				fan->inc_x[fan->who] = -1;
			else
				fan->inc_x[fan->who] = 1;
		}
		else
		{
			if (!truey(fan->old_mov_y[fan->who], fan) && truex(-1, fan) && !truex(1, fan))
			{
				fan->inc_x[fan->who] = -1;
			}
			else
			{
				if (!truey(fan->old_mov_y[fan->who], fan) && !truex(-1, fan) && truex(1, fan))
				{
					fan->inc_x[fan->who] = 1;
				}
				else
				{
					if (truey(fan->old_mov_y[fan->who], fan) && !truex(-1, fan) && !truex(1, fan))
					{
						fan->inc_y[fan->who] = fan->old_mov_y[fan->who];
					}
					else
					{
						if (truey(fan->old_mov_y[fan->who], fan) && truex(-1, fan) && !truex(1, fan))
						{
							alea_t = rand() % 30;

							if (alea_t >= 0 && alea_t <= 14)
								fan->inc_x[fan->who] = -1;
							else
								fan->inc_y[fan->who] = fan->old_mov_y[fan->who];
						}
						else
						{
							if (truey(fan->old_mov_y[fan->who], fan) && !truex(-1, fan) && truex(1, fan))
							{
								alea_t = rand() % 30;

								if (alea_t >= 0 && alea_t <= 14)
									fan->inc_x[fan->who] = 1;
								else
									fan->inc_y[fan->who] = fan->old_mov_y[fan->who];
							}
						}
					}
				}
			}
		}
	}
}

void optener_movimientos_fantasmas(struct fantasmas *fan, struct pcman *pc)
{
	int alea_t;
	for (fan->who = 0; fan->who < NUM_GHOTS; fan->who++)
	{
		if (busca_posiciones[fan->who] == TRUE)
		{

			if (fan->old_mov_y[fan->who] != 0)
			{
				if (fan->x[fan->who] > fan->find_x[fan->who])
				{
					if (comprueba_distancias_x(fan))
					{
						if (truex(-1, fan))
						{
							fan->inc_x[fan->who] = -1;
							fan->inc_y[fan->who] = 0;
						}
					}
					else
						devuelve_valores_aleatorios_y(fan);
				}
				else if (fan->x[fan->who] < fan->find_x[fan->who])
				{
					if (comprueba_distancias_x(fan))
					{
						if (truex(1, fan))
						{
							fan->inc_x[fan->who] = 1;
							fan->inc_y[fan->who] = 0;
						}
					}
					else
						devuelve_valores_aleatorios_y(fan);
				}
				else if (fan->x[fan->who] == fan->find_x[fan->who])
				{
					if ((fan->inc_y[fan->who] == -1 && !truey(-1, fan)) ||
						(fan->inc_y[fan->who] == 1 && !truey(1, fan)))
					{
					L2: /* Etiqueta correspondiente a comprobaciones adicionales */
						/* Debemos mover X. En este caso si podemos mover +X � -X */
						/* Lo haremos de forma aleatoria */
						/* 1� comprobamos si puede pasar por los dos sitios */
						if (truex(1, fan) && truex(-1, fan))
						{
							alea_t = rand() % 2;

							if (alea_t == 0)
							{
								fan->inc_x[fan->who] = 1;
								fan->inc_y[fan->who] = 0;
							}
							else if (alea_t == 1)
							{
								fan->inc_x[fan->who] = -1;
								fan->inc_y[fan->who] = 0;
							}
						}
						else
						{
							/* Si solo puede mover por un solo sitio */
							/* miramos por cual es y movemos */
							if (truex(1, fan))
							{
								fan->inc_x[fan->who] = 1;
								fan->inc_y[fan->who] = 0;
							}
							if (truex(-1, fan))
							{
								fan->inc_x[fan->who] = -1;
								fan->inc_y[fan->who] = 0;
							}
						}
					}
				}
			}
			else if (fan->old_mov_x[fan->who] != 0)
			{
				if (fan->y[fan->who] > fan->find_y[fan->who])
				{
					if (comprueba_distancias_y(fan))
					{
						if (truey(-1, fan))
						{
							fan->inc_y[fan->who] = -1;
							fan->inc_x[fan->who] = 0;
						}
					}
					else
						devuelve_valores_aleatorios_x(fan);
				}
				else if (fan->y[fan->who] < fan->find_y[fan->who])
				{
					if (comprueba_distancias_y(fan))
					{
						if (truey(1, fan))
						{
							fan->inc_y[fan->who] = 1;
							fan->inc_x[fan->who] = 0;
						}
					}
					else
						devuelve_valores_aleatorios_x(fan);
				}
				else if (fan->y[fan->who] == fan->find_y[fan->who])
				{
					if ((fan->inc_x[fan->who] == -1 && !truex(-1, fan)) || (fan->inc_x[fan->who] == 1 && !truex(1, fan)))
					{
						/* En este punto debemos de optar por mover Y por donde se pueda */
						/* Si puede pasar por los sitios */
					L1: /* Etiqueta de comprobaciones adicionales */
						if (truey(-1, fan) && truey(1, fan))
						{
							alea_t = rand() % 2;

							if (alea_t == 0)
							{
								fan->inc_y[fan->who] = 1;
								fan->inc_x[fan->who] = 0;
							}
							else if (alea_t == 1)
							{
								fan->inc_y[fan->who] = -1;
								fan->inc_x[fan->who] = 0;
							}
						}
						else
						{
							/* Solo puede mover por +Y � -Y */
							if (truey(-1, fan))
							{
								fan->inc_y[fan->who] = -1;
								fan->inc_x[fan->who] = 0;
							}
							else if (truey(1, fan))
							{
								fan->inc_y[fan->who] = 1;
								fan->inc_x[fan->who] = 0;
							}
						}
					}
				}
			}

			/* Comprobaciones adicionales */

			if ((fan->inc_x[fan->who] == 1 && !truex(1, fan)) ||
				(fan->inc_x[fan->who] == -1 && !truex(-1, fan)))
			{
				/* Tendremos que mover Y */
				/*   Para no crear m�s c�digo damos un salto a una linea */
				/* anterior donde pasaba algo parecido */
				goto L1;
			}

			if ((fan->inc_y[fan->who] == 1 && !truey(1, fan)) ||
				(fan->inc_y[fan->who] == -1 && !truey(-1, fan)))
			{
				/* Tendremos que mover X */
				/*   Para no crear m�s c�digo damos un salto a una linea */
				/* anterior donde pasaba algo parecido */
				if ((fan->x[fan->who] == 16 && fan->y[fan->who] == 1) ||
					(fan->x[fan->who] == 16 && fan->y[fan->who] == 24))
				{
					fan->inc_y[fan->who] = fan->inc_y[fan->who];
				}
				else
					goto L2;
			}

			if (fan->x[fan->who] == 16 && fan->y[fan->who] == 1)
			{
				fan->x[fan->who] = 16;
				fan->y[fan->who] = 24;
				fan->inc_y[fan->who] = -1;
				fan->inc_x[fan->who] = 0;
			}
			else if (fan->x[fan->who] == 16 && fan->y[fan->who] == 24)
			{
				fan->x[fan->who] = 16;
				fan->y[fan->who] = 1;
				fan->inc_y[fan->who] = 1;
				fan->inc_x[fan->who] = 0;
			}

			if (fan->x[fan->who] == 16 && (fan->y[fan->who] == 2 || fan->y[fan->who] == 3 || fan->y[fan->who] == 4 || fan->y[fan->who] == 5))
			{
				inc_velocidad[fan->who] = velocidades[pc->nivel] - 0.2;
			}
			else if (fan->x[fan->who] == 16 && (fan->y[fan->who] == 23 || fan->y[fan->who] == 22 || fan->y[fan->who] == 21 ||
												fan->y[fan->who] == 20))
			{
				inc_velocidad[fan->who] = velocidades[pc->nivel] - 0.2;
			}
			else
			{
				if (pc->nivel < 13)
				{
					if (fan->estado_fantasma[fan->who] == NORMAL)
						inc_velocidad[fan->who] = velocidades[pc->nivel];
					else if (fan->estado_fantasma[fan->who] == ENFADADO)
						inc_velocidad[fan->who] = velocidades[pc->nivel] - 0.2;
					else
						inc_velocidad[fan->who] = 1.0;
				}
				else
				{
					if (fan->estado_fantasma[fan->who] == NORMAL)
						inc_velocidad[fan->who] = velocidades[pc->nivel];
					else if (fan->estado_fantasma[fan->who] == ENFADADO)
						inc_velocidad[fan->who] = velocidades[pc->nivel] - 0.2;
					else
						inc_velocidad[fan->who] = 1.0;
				}
			}

			/* El Fantasma est� en la puerta de su casa en estado muerto */
			/* Salta por un espacio del array que est� en blanco para entrar en */
			/* la casa */
			if (fan->x[fan->who] == 19 &&
				fan->y[fan->who] == 12 &&
				fan->estado_fantasma[fan->who] == MUERTO)
			{
				fan->inc_y[fan->who] = 0;
				fan->inc_x[fan->who] = -1;
			}

			if (CntStep2 >= 240)
				CntStep2 = 0;
			fan->old_mov_x[fan->who] = fan->inc_x[fan->who];
			fan->old_mov_y[fan->who] = fan->inc_y[fan->who];
			fan->old_x[fan->who] = fan->x[fan->who];
			fan->old_y[fan->who] = fan->y[fan->who];
			fan->x[fan->who] += fan->inc_x[fan->who];
			fan->y[fan->who] += fan->inc_y[fan->who];

			/* Evita que todos los fantasmas salgan a la vez */
			if ((fan->x[fan->who] == 15 && fan->y[fan->who] == 12) &&
				fan->estado_fantasma[fan->who] == MUERTO)
			{
				fan->estado_fantasma[fan->who] = NORMAL;
				inc_velocidad[fan->who] = velocidades[pc->nivel];
			}
		}
	}
}
