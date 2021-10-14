#Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -fsanitize=address -g
LDFLAGS = -fsanitize=address
LDLIBS = -lm

SRC = testNN.c arrayaux.c neuralnetwork.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: testNN

testNN: ${OBJ}

.PHONY: clean

clean:
		${RM} ${OBJ}
		${RM} ${DEP}
		${RM} testNN

-include ${DEP}

#END
