#ifndef SDLNN_H
#define SDLNN_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

void init_sdl();

SDL_Surface* load_image(char *path);

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);

#endif