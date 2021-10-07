#Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -fsanitize=address -g
LDFLAGS = -fsanitize=address
LDLIBS = 

SRC = solver.c solveralgo.c parser.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: solver

solver: ${OBJ}

.PHONY: clean

clean:
		${RM} ${OBJ}
		${RM} ${DEP}
		${RM} solver

-include ${DEP}

#END