#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "sprites.h"
#include "pacman.h"
#include "gfx.h"

void writef(int col, int row, UintDEP *where, char *format, ...)
{
va_list arg_ptr;
char output[81];
size_t len;
int _width;
int itemp, i;
  va_start(arg_ptr, format);
  vsprintf(output, format, arg_ptr);
  _width = strlen(output);
  *(output + _width) = 0;
  if ((len = strlen(output)) < _width)
    memset(&output[len], ' ', _width - len);
  /* paso de poner el siguiente codigo en una funci¢n */
  /* esta funci¢n tarda demasiado tiempo y no quiero gastar m s */
  /* llamando a una funci¢n */
/*  hprintf(col, row, where, output);*/

  /* Analizaremos la cadena empezando por el final e iremos escribiendo */
  /* los n£meros que vayan apareciendo */
  itemp = strlen(output);
  for (i = itemp; i >= 0; i--) {
    switch(output[i]) {
      case '0':
	putico(col, row, n_0, where, 4, 7);
	break;
      case '1':
	putico(col, row, n_1, where, 4, 7);
	break;
      case '2':
	putico(col, row, n_2, where, 4, 7);
	break;
      case '3':
	putico(col, row, n_3, where, 4, 7);
	break;
      case '4':
	putico(col, row, n_4, where, 4, 7);
	break;
      case '5':
	putico(col, row, n_5, where, 4, 7);
	break;
      case '6':
	putico(col, row, n_6, where, 4, 7);
	break;
      case '7':
	putico(col, row, n_7, where, 4, 7);
	break;
      case '8':
	putico(col, row, n_8, where, 4, 7);
	break;
      case '9':
	putico(col, row, n_9, where, 4, 7);
	break;
    }
    col -= 5;
  }

}
