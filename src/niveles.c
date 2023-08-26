#include "pacman.h"
#include "defines.h"

/*
  Esta funci¢n es llamada cuando nos
  comemos todos los puntos de un circuito.
*/

void adelanta_nivel(struct fantasmas *fan, struct pcman *pc)
{
  pc->nivel++;
  stargame(fan, pc, TRUE);
};