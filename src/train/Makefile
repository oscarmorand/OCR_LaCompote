#Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -fsanitize=address -g
LDFLAGS = -fsanitize=address
LDLIBS = -lm

SRC = trainNN.c neuralnetwork.c printNN.c saveandload.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: train

train: ${OBJ}
	${CC} ${LDFLAGS} -o train ${OBJ} ${LDLIBS}

.PHONY: clean

clean:
		${RM} ${OBJ}
		${RM} ${DEP}
		${RM} train

-include ${DEP}

#END
