VERSION = first
OS = linux
ARCH = i386

CC = gcc
INCLUDEDIR = /usr/include/SDL
INCLUDESRCDIR = src/include

CFLAGS = -DLINUX -O3 -ggdb -ffast-math -funroll-loops -fomit-frame-pointer -Wall -pipe \
         -I$(INCLUDEDIR) -I$(INCLUDESRCDIR)

LDFLAGS = -L/usr/lib -lSDL -lSDL_image -lm -lmikmod -lglfw

SRC = src/main.c \
      src/gfx.c \
      src/menuopt.c \
      src/mov_fig.c \
      src/sprites.c \
      src/movefant.c \
      src/misc.c

OBJS = $(SRC:.c=.o)

all: pacman

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

pacman: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o pacman $(LDFLAGS)

clean:
	rm -f $(OBJS) pacman
