#include <stdio.h>
#include <math.h>
#include "display.h"
#include "pixel_operations.h"

/* hough transform function */
void houghTransform(int** matrix, int x, int y, int size)
{
    for (int O = 1; O <= 180; O++)
    {
        double thet = (M_PI /180) * O;
        int r = (x*cos(thet) + y*sin(thet));


        int rho = size + r;
        matrix[rho][O] += 1;
        
    }
    
}

/* returns theta and rho coords of the max in the matrix */
void maxMat(int *stop, int *theta, int *rho, int** matrix, int thetaSize, int rhoSize, int threshold)
{
    int max = 0;
    for (int r = 0; r < rhoSize; r++)
    {
        for (int O = 0; O < thetaSize; O++)
        {
            if (max < matrix[r][O] && matrix[r][O] >= threshold)
            {
                max = matrix[r][O];
                *theta = O;
                *rho = r;
            }
        }
    }

    if (max == 0)
    {
        //no max has been found
        *stop = 1;
    }
    
}



int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    init_sdl();

    image_surface = load_image("sudoku.png");
    screen_surface = display_image(image_surface);

    wait_for_keypressed();

    //Init the matrix for hough transform
    int width = image_surface->w;
    int height = image_surface->h;
    int maxLength = 2*sqrt(width*width + height*height);


    //Allocate memory for the matrix
    int** MatTransform = malloc(maxLength * sizeof(int*));
    for(int i = 0; i < maxLength; ++i)
    {
        MatTransform[i] = malloc(180*sizeof(int));
    }

    //Init all matrix value on 0
    for (int i = 0; i < 180; i++)
    {
        for (int j = 0; j < maxLength; j++)
        {
            MatTransform[j][i] = 0;
        }
    }

    //Start of checking if hough transform or not for each black pixel and apply it
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Uint32 pixel = get_pixel(image_surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            if (r <= 100)//r = g = b, check if pixel is black
            {
                //houghTransform(MatTransform, x, y, maxLength/2);

                for (int O = 1; O < 180; O++)
                {
                    double thet = (M_PI /180) * O;
                    int r = (x*cos(thet) + y*sin(thet));
                    int rho = maxLength/2 + r;
                    MatTransform[rho][O] += 1;
                    
                }
            }
        }
    }

    //draw a red line 
    int stop = 0;
    /*while (stop == 0)//*/
    for (size_t i = 0; i < 28; i++)
    {
        //repeat while there are max values
        int theta = 0;
        int rho = 0;
        // draw lines that are 50% the size of the image min
        maxMat(&stop, &theta, &rho, MatTransform, 180, maxLength, 100);
        int max = MatTransform[rho][theta];

        MatTransform[rho][theta] = 0;
        rho -= maxLength/2;

        int changeMode = 0;
        if (theta == 179 || theta == 91 || theta == 1) //case were infinite value
        {
            changeMode = 1;
            theta = 0;
        }
        
        printf("max is = %d in coord rho = %d and theta = %d : cos(O) = %f\n",max, rho, theta, cos(theta * M_PI/180));
        double O = theta * M_PI/180;

        Uint32 pixel = SDL_MapRGB(image_surface->format, 255, 0, 0);
        
        if (changeMode)
        {
            for (int y = 0; y < height; y++)
            {
                double x = ((-y*sin(O))/cos(O)) + rho/cos(O);
                printf("(%d , %lf) : cos(O) = %f\n", y,x, cos(O));
            
                put_pixel(image_surface, abs((int) x), abs(y), pixel);
                update_surface(screen_surface, image_surface);
            
            }
        }
        else

            for (int x = 0; x < width; x++)
            {
                double y = ((-x*cos(O))/sin(O)) + rho/sin(O);
                //printf("(%d , %lf) : cos(O) = %f\n", x,y, cos(O));  
                Uint32 thisPix = get_pixel(image_surface, x, y);
                Uint8 r, g, b;
                SDL_GetRGB(thisPix, image_surface->format, &r, &g, &b);
                if (r <= 100 && b <= 100 && g <= 100)
                {             
                    put_pixel(image_surface, x, y, pixel);
                    update_surface(screen_surface, image_surface);    
                }       
            }
    }

    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    //////////////////////////////
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    
    for(int i = 0; i < maxLength; ++i)
    {
        free(MatTransform[i]);
    } 
    free(MatTransform);

    return 0;
}