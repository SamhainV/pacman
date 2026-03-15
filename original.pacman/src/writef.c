/*
 * Bugs conocidos. 
 * Hay que prestar mucha atencion de introducir bien los argumentos en writef
 * ya k de otra manera vsprintf daria un segment fault.
 * writef("%d %s\n", cadena, strlen(cadena)); = segment fault
 *
 */



#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>


void writef(char *format, ...)
{
  va_list arg_ptr;
  char output[1024];
  size_t len;
  int _width;
  va_start(arg_ptr, format);
  vsprintf(output, format, arg_ptr);
  _width = strlen(output);
  *(output + _width) = 0;
  if ((len = strlen(output)) < _width)
    memset(&output[len], ' ', _width - len);

  printf(output);
  
}


int main(void)
{
  char cadena[] = "Esto es una cadena de texto.";

  writef("%s de longitud %d\n", cadena, strlen(cadena));

  return 0;
}
