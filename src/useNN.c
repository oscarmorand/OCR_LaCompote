#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// NEURAL NETWORK INCLUDES
#include "neuralnetwork.h"
#include "saveandload.h"
#include "structsNN.h"
#include "printNN.h"
#include "sdlNN.h"

#define BASE_FILENAME "x0y0.png"
#define SIZE_IMAGE 28

int nbrLayers = 5;
int nbrNeurones[] = {784, 512, 256, 128, 10};


char determine_digit(SDL_Surface* image, NN* nNp) 
{
    // for each pixel of the image
    for (size_t y = 0; y < SIZE_IMAGE; y++)
    {
        for (size_t x = 0; x < SIZE_IMAGE; x++)
        {
            // get grayscale value of the pixel
            Uint32 pixel = get_pixel(image, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            // initialize the inputs of the neural network
            nNp->lays[0].neus[y*SIZE_IMAGE+x].actv = r;
        }
    }

    // calculate the output of the neural network
    ForwardProp(nNp);
    
    int outputLayer = nNp->nbLay - 1;
    char nbNeuOutput = (char)nNp->nbNeus[outputLayer];

    // determine the output that has the max probability
    char maxDigit = 0;
    float maxProbDigit = nNp->lays[outputLayer].neus[0].actv;
    for (char i = 1; i < nbNeuOutput; i++)
    {
        if(nNp->lays[outputLayer].neus[(int)i].actv > maxProbDigit) {
            maxProbDigit = nNp->lays[outputLayer].neus[(int)i].actv;
            maxDigit = i;
        }
    }

    return maxDigit;
}

void fill_grid(size_t n, char** grid)
{
    NN nN = CreateNN(nbrLayers, nbrNeurones);

    for (size_t y = 0; y < n; y++)
    {
        for (size_t x = 0; x < n; x++)
        {
            char fileName[] = BASE_FILENAME;
            fileName[1] = (char)(x+'0');
            fileName[3] = (char)(y+'0');

            printf("%s\n", fileName);

            /*
            SDL_Surface* image_surface;
            image_surface = load_image(fileName);

            char digit = determine_digit(image_surface, &nN);
            grid[y][x] = digit;

            SDL_FreeSurface(image_surface);
            */
        }
    }
    printf("\n");

    DestroyNN(&nN);
}
