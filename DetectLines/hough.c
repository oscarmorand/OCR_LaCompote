#include <stdio.h>
#include <math.h>
#include "display.h"
#include "pixel_operations.h"

/* hough transform function */
void houghTransform(int** *matrix, int x, int y)
{
    for (int O = 0; O < 180; O++)
    {
        int r = (int) (x*cos(O) + y*sin(O));
        matrix[O][r] += 1;
    }
    
}

/* returns theta and rho coords of the max in the matrix */
void maxMat(int *theta, int *rho, int** matrix, int thetaSize, int rhoSize)
{
    int max = 0;
    for (int r = 0; r < rhoSize; r++)
    {
        for (int O = 0; O < thetaSize; O++)
        {
            if (max < matrix[O][r])
            {
                max = matrix[O][r];
                *theta = O;
                *rho = r;
            }
        }
    }
}



int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    //init_sdl;

    image_surface = load_image("sudoku.png");
    screen_surface = display_image(image_surface);

    wait_for_keypressed();

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
    //MatTransform[180][maxLength];
    for (int i = 0; i < 180; i++)
    {
        for (int j = 0; j < maxLength; j++)
        {
            MatTransform[i][j] = 0;
        }
    }

    //Start of checking if hough transform or not for each black pixel and apply it
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Uint32 pixel = get_pixel(image_surface, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            if (r <= 100)//r = g = b, check if pixel is black
            {
                houghTransform(&MatTransform, j, i);
            }
        }
    }

    //draw a red line 
    int theta = 0;
    int rho = 0;
    maxMat(&theta, &rho, MatTransform, 180, maxLength);
    Uint32 pixel = SDL_MapRGB(image_surface->format, 255, 0, 0);
    for (int x = 0; x < width; x++)
    {
        int y = (-x*cos(theta))/sin(theta) + rho/sin(theta);
        put_pixel(image_surface, x, y, pixel);
    }
    

    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    //////////////////////////////
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    
    return 0;
}