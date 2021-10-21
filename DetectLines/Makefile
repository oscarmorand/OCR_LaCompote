# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -fsanitize=address -g `pkg-config --cflags sdl`
LDFLAGS= -fsanitize=address
LDLIBS= `pkg-config --libs sdl SDL_image` -lm -ldl

o_files:= pixel_operations.o hough.o display.o
d_files:= $(o_files:%.o=%.d)

all: hough

hough: $(o_files)

hough.o: pixel_operations.h


clean:
	${RM} *.o
	${RM} *.d
	${RM} hough

-include $(d_files)

# END