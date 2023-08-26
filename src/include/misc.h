struct pcman {
  float x;
  float y;
  float inc_x;
  float inc_y;
  float old_inc_x;
  float old_inc_y;
  float old_x;
  float old_y;
  float yf;
  float dir;
  int puntos;
  int puntuacion;
  int nivel;
  int tiempo;
  int estado_pcman;
  int num_vidas;
};

struct fantasmas {
  float x[4];
  float y[4];
  float old_x[4];
  float old_y[4];
  float inc_x[4];
  float inc_y[4];
  float find_x[4];
  float find_y[4];
  float find_xp[4];
  float find_yp[4];
  float old_mov_x[4];
  float old_mov_y[4];
  int estado_fantasma[4];
  int who;
};

extern int c_array[MAXY_A*MAXX_A];
extern int array[MAXY_A*MAXX_A];

extern struct fantasmas fan;
extern struct pcman pc;
extern float inc_velocidad[4];
extern float velocidades[14];
extern float inc_velocidad_pc;
extern int busca_posiciones[4];
extern int busca_posiciones_pc;


void clearkbd(Uint8 *keys);
void writef(int col, int row, UintDEP *where, char *format, ...);
void getsprites(void);
void copyarray(void);
void pon_puntos_en_pantalla(void);
void inicializa_structuras(struct pcman *pc, struct fantasmas *fan, int value);
void adelanta_nivel(struct fantasmas *fan, struct pcman *pc);
void stargame(struct fantasmas *fan, struct pcman *pc, int value);
int teclado(void);
