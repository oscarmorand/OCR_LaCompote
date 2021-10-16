#include <stdio.h>
#include <math.h>
#include "display.h"


int** houghTransform(int** *matrix, int theta, int rho)
{
    //todo
}

int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    //Init the matrix for hough transform
    int width = image_surface->w;
    int height = image_surface->h;
    int maxLength = sqrt(width*width + height*height);

    //Allocate memory for the matrix
    int **MatTransform = malloc(maxLength * sizeof(int));
    for(int i = 0; i < maxLength; ++i)
    {
        MatTransform[i] = malloc(180*sizeof(int));
    } 

    //Init all matrix value on 0
    MatTransform[180][maxLength];
    for (int i = 0; i < 180; i++)
    {
        for (int j = 0; j < maxLength; j++)
        {
            MatTransform[i][j] = 0;
        }
    }

    //Start of checking if hough transform or not for each black pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Uint32 pixel = get_pixel(image_surface, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            if (r <= 100)//r = g = b, check if pixel is black
            {
                houghTransform(&MatTransform, 180, maxLength);
            }
            
        }
        
    }
    

    init_sdl;
}