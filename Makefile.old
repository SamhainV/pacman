VERSION=first first
OS=linux
ARCH=i386

CC= gcc
INCLUDEDIR = /usr/include/SDL
INCLUDESRCDIR = src/include

CFLAGS = -DLINUX -O3  -ggdb -ffast-math -funroll-loops -fomit-frame-pointer -Wall -pipe -I$(INCLUDEDIR) -I$(INCLUDESRCDIR)

all: pacman

OBJS = 	src/main.o		\
	src/gfx.o		\
	src/menuopt.o		\
	src/mov_fig.o		\
	src/sprites.o		\
	src/movefant.o		\
	src/misc.o		\

$(OBJS): %.o : %.c

	#nasm -f elf -o src/memcpy32.o src/memcpy32.asm
	$(CC) $(CFLAGS) $(GAME_FLAGS) -o $@ -c $<

pacman: $(OBJS)
	 $(CC) $(CFLAGS) $(OBJS) $(GAME_LIBS) -I../../include -L/usr/X11R6/lib -o pacman -L/usr/lib -lSDL -lSDL_image -lm -lmikmod

clean:
	rm -f $(OBJS) pacman
