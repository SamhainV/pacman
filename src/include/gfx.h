/*extern SDL_Surface *screen;*/
#define	FRAMES_PER_SEC	50
void init_gfx(void);
void close_gfx(void);
void flip_screen(SDL_Surface *dest, unsigned char *src);
void fastflip_screen(SDL_Surface *dest, unsigned char *source);
void load_screen(void);
void WaitFrame(void);
SDL_Surface *LoadImage(char *datafile, int transparent);
void putico(int x, int y, UintDEP *source, UintDEP *dest, int max_x, int max_y);
void TimerStart(void (*handler)(int),int frecuencia);
void TimerStop(void);
void timerfunc(int i);
int keyboard_loop(void);
void getsprite(SDL_Surface *srf, SDL_Rect *rect, UintDEP *dest);
void fill_buffer(UintDEP *src, UintDEP *dest);
void *memcpy32(void *dest, const void *src, size_t n);

extern int CntStep, CntStep2, CntStep3;
extern Uint32 sdl_flags;
