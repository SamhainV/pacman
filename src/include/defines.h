#include "SDL.h"
#define MAXCHAR 80
#define NORMAL 0
#define ENFADADO 1
#define MUERTO 2
#define COMENZAR 2
#define TRUE 1
#define FALSE 0
#define COOR_X  55 /* Define coordenadas del array � circuito en pantalla */
#define COOR_Y   2 /* Define coordenadas del array � circuito en pantalla */
/* En realidad es 31 usamos 32 para que el desplazamiento sea << 5 */
#define MAXX_A 32 /* M�ximo tama�o X del array + 2 bordes */
#define MAXY_A 26 /* M�ximo tama�o Y del array + 2 bordes */
#define ESCALA 8  /* Separaci�n entre puntos en medidas de array */
#define ARRIBA 200
#define ABAJO  208
#define DERECHA 205
#define IZQUIERDA 203
#define DER 0
#define IZQ 1
#define ARR 2
#define ABA 3

#define MOV_X 0
#define MOV_Y 1
#define NUM_GHOTS 4
#define NUM_PUNTOS 226

//#define ARCHBIN "\\PCMAN\\PCMAN.BIN"

#define COME 0
#define SIRENAS 1
#define SILENCIO 2

enum CODIGOS  {  /* C�digos para el array */
  C = 1, /* Circuito   */
  N = 2, /* Nada */
  J = 3, /* Camino pasado */
  P = 4, /* Puerta abierta */
  B = 5  /* Bolon asusta fantasmas */
};

/* Offset de las figuras en pantalla */
/*enum FIGURAS {
  pc_der0 = 58902u,
  pc_izq0 = 59255u,
  pc_aba0 = 59560u,
  pc_arr0 = 59201u,
  pc_der1 = 51878u,
  pc_izq1 = 51840u,
  pc_aba1 = 52534u,
  pc_arr1 = 51217u,
  pc_bol  = 46455u,

  fanarr0 =   321u,
  fanaba0 =  5441u,
  fander0 =  5472u,
  fanizq0 =   351u,
  fanarr0p =  336u,
  fanaba0p = 5456u,
  fander0p = 5488u,
  fanizq0p =  367u,

  fanarr1 =  10561u,
  fanaba1 =  15681u,
  fander1 =  15714u,
  fanizq1 =  10594u,
  fanarr1p = 10577u,
  fanaba1p = 15697u,
  fander1p = 15730u,
  fanizq1p = 10610u,

  fanarr2 =  20801u,
  fanaba2 =  25921u,
  fander2 =  25954u,
  fanizq2 =  20834u,
  fanarr2p = 20817u,
  fanaba2p = 25937u,
  fander2p = 25970u,
  fanizq2p = 20850u,

  fanarr3 =  31041u,
  fanaba3 =  36161u,
  fander3 =  36194u,
  fanizq3 =  31074u,
  fanarr3p = 31057u,
  fanaba3p = 36177u,
  fander3p = 36210u,
  fanizq3p = 31090u,
};*/

/* 320 200 = 64000; 320 * 200 * BPP*/
#define RES_X 320
#define RES_Y 200
#define RES_XB 320
#define RES_YB 200
#define DEPTH 32
typedef Uint32 UintDEP;
#define BPP sizeof(UintDEP)
#define BYTES  ((RES_XB*RES_YB*BPP)/BPP) /* 128000/4 */
#define BYTES2 ((RES_X*RES_Y*BPP)/BPP) /* 128000/4 */
#define BYTES3 (RES_XB*RES_YB) * 4

#define DIR_SEP	"/"
#define DIR_CUR	""

#define DATAFILE(X)	DIR_CUR "data" DIR_SEP X

#define MAX_INSTRUMENTS 12
#define NOTHING 0
#define DOWNLOAD 1
#define UPLOAD 2
#define REUPLOAD 3
#define MAX_XA 13
#define MAX_YA 8

extern int CntStep3, CntStep3, CntStep3;
extern SDL_Surface *screen;
extern SDL_Surface *tablero;
extern UintDEP background[RES_XB*RES_YB*sizeof(UintDEP)];


