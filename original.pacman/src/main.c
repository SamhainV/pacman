#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>

#include "defines.h"
#include "gfx.h"
#include "pacman.h"
#include "sprites.h"
#include "misc.h"
#include "menuopt.h"
#include <GLFW/glfw3.h>

static int resolucion_ancho = 0;
static int resolucion_alto = 0;
static int refresco_hz = 0;
static const char *script_restauracion = "/tmp/restaurar_xrandr.sh";

SDL_Surface *screen;
SDL_Surface *tablero;
UintDEP background[RES_XB * RES_YB * BPP];

void guardarResolucionOriginal()
{
  if (!glfwInit())
  {
    fprintf(stderr, "No se pudo inicializar GLFW\n");
    return;
  }

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  if (!monitor)
  {
    fprintf(stderr, "No se pudo obtener el monitor principal\n");
    glfwTerminate();
    return;
  }

  const GLFWvidmode *mode = glfwGetVideoMode(monitor);
  if (!mode)
  {
    fprintf(stderr, "No se pudo obtener el modo de video\n");
    glfwTerminate();
    return;
  }

  resolucion_ancho = mode->width;
  resolucion_alto = mode->height;
  refresco_hz = mode->refreshRate;

  printf("Resolución guardada: %dx%d @%dHz\n", resolucion_ancho, resolucion_alto, refresco_hz);

  glfwTerminate();

  // Crear script de restauración completo
  FILE *fp = fopen(script_restauracion, "w");
  if (!fp)
  {
    perror("No se pudo crear el script de restauración");
    return;
  }

  fprintf(fp, "#!/bin/bash\n");

  // Obtener salida primaria
  FILE *primary_pipe = popen("xrandr --query | awk '/ connected primary/ {print $1}'", "r");
  char primary_output[32] = {0};
  if (primary_pipe)
  {
    if (fgets(primary_output, sizeof(primary_output), primary_pipe))
    {
      primary_output[strcspn(primary_output, "\n")] = 0; // quitar salto
    }
    pclose(primary_pipe);
  }

  // Generar comandos xrandr por cada salida activa con modo y posición
  FILE *pipe = popen(
    "xrandr --query | grep ' connected' | awk '{"
    " salida=$1;"
    " for(i=1;i<=NF;i++) if ($i ~ /[0-9]+x[0-9]+\\+[0-9]+\\+[0-9]+/) modo=$i;"
    " if (modo != \"\") {"
    " split(modo, parts, /[x+]/);"
    " ancho=parts[1]; alto=parts[2]; posx=parts[3]; posy=parts[4];"
    " cmd=\"xrandr --output \" salida \" --mode \" ancho \"x\" alto \" --pos \" posx \"x\" posy;"
    " for(j=1;j<=NF;j++) if ($j == \"primary\") cmd=cmd \" --primary\";"
    " print cmd;"
    " }"
    "}'",
    "r");


  if (!pipe)
  {
    perror("No se pudo obtener la configuración de pantalla");
    fclose(fp);
    return;
  }

  char linea[256];
  while (fgets(linea, sizeof(linea), pipe))
  {
    fputs(linea, fp);
  }

  pclose(pipe);
  fclose(fp);
  system("chmod +x /tmp/restaurar_xrandr.sh");
  printf("📝 Script de restauración generado con disposición y salida primaria en %s\n", script_restauracion);
}


void restaurarResolucionOriginal()
{
  if (resolucion_ancho > 0 && resolucion_alto > 0)
  {
    printf("Restaurando configuración de monitores desde script...\n");
    char comando[128];
    snprintf(comando, sizeof(comando), "%s", script_restauracion);
    system(comando);
  }
  else
  {
    fprintf(stderr, "Resolución original no válida, no se puede restaurar.\n");
  }
}

int xrandr_disponible()
{
  // Comprobamos si xrandr está en /usr/bin
  if (access("/usr/bin/xrandr", X_OK) == 0)
  {
    return 1;
  }
  // Alternativamente, usamos `which xrandr`
  return (system("which xrandr > /dev/null 2>&1") == 0);
}

void setup()
{
  if (!xrandr_disponible())
  {
    fprintf(stderr, "⚠️  ADVERTENCIA: 'xrandr' no está disponible en el sistema.\n");
    fprintf(stderr, "No se podrá guardar ni restaurar la resolución automáticamente.\n\n");
  }
  else
  {
    printf("✅ xrandr disponible. Se podrá guardar/restaurar la configuración de pantalla.\n");
  }
}

void help(void)
{
  printf("Uso:\n\n");
  printf("intro -f (fullscreen) -w (windomed)\n\n\n");
  exit(0);
}

int main(int argc, char **argv)
{
  setup();
  int ch;
  sdl_flags = (SDL_SWSURFACE | SDL_HWPALETTE | SDL_DOUBLEBUF);
  /* Opciones -f (fullscreen) -w (en ventana) */
  while ((ch = getopt(argc, argv, "fw")) != -1)
    switch (ch)
    {
    case 'f': /* fullscreen */
      sdl_flags = (SDL_SWSURFACE | SDL_HWPALETTE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
      break;
    case 'w': /* ventana */
      sdl_flags = (SDL_SWSURFACE | SDL_HWPALETTE | SDL_DOUBLEBUF);
      break;
    case 'h':
      help();
    default:
      help();
    }

  if (optind < argc || !sdl_flags)
    help();

  guardarResolucionOriginal();

  init_gfx();

  TimerStart(timerfunc, 18);
  getsprites();
  menu_opciones(TRUE);

  stargame(&fan, &pc, COMENZAR);
  restaurarResolucionOriginal();

  exit(0);
}
