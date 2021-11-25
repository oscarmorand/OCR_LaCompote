#Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS =  -Wall -Wextra -std=c99 -O3 -g `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl` -fsanitize=address
LDFLAGS = -fsanitize=address
LDLIBS = -lm `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl SDL_image` -ldl

SRC = main.c solver.c parser.c useNN.c neuralnetwork.c saveandload.c printNN.c basic_sdl.c cut.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main 

main: ${OBJ}

.PHONY: clean

clean:
		${RM} ${OBJ}
		${RM} ${DEP}
		${RM} main
		${RM} test.result

-include ${DEP}

#END