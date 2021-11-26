#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "basic_sdl.h"

//Input top left corner of rect / computes the final RECT
// then pass it in BlitSurface
// then find a way to save it as a new image

SDL_Surface* get_RECT(int srcX, int srcY, SDL_Surface* img){
    int boxW = (img->w)/9;
    int boxH = (img->h)/9;

    SDL_Rect box;
    box.x = srcX;
    box.y = srcY;
    box.w = boxW;
    box.h = boxH;

    SDL_Rect oo;
    oo.x = 0;
    oo.y = 0;
    oo.w = boxW;
    oo.h = boxH;

    SDL_Surface* out_box = SDL_CreateRGBSurface(0, boxW, boxH, 32, 0, 0, 0, 0);
    SDL_BlitSurface(img, &box, out_box, &oo);

    return out_box;

    /*char out_path[128]; //buffer to store file name (INCLUDING EXTENSION)
    sprintf(out_path, "out/x%iy%i.bmp", srcX, srcY);
    SDL_SaveBMP(out_box, out_path);

    SDL_FreeSurface(out_box);*/
}

//Checks if the (x.y) pix belongs to surface and if its red
int isRed(int x, int y, SDL_Surface* surf){
    Uint32 pix = get_pixel(surf, x, y);
    Uint8 r, g, b;
    SDL_GetRGB(pix, surf -> format, &r, &g, &b);

    if (x < (surf->w)-1 && y < (surf->h)-1 && r >= 220 && g <= 30 && b <= 30)
        return 1;
    return 0;
}

SDL_Surface** nb_cropout(SDL_Surface* surface){
    int width = surface->w;
    int height = surface->h;

    int i=0; //CNT for x values
    int j=0; //nb of 9's done

    int DEBUG_NB_OF_DOTS = 0;

    SDL_Surface** images = (SDL_Surface**)malloc(99 * sizeof(SDL_Surface*));
    
    for (int y = 0; y < height-1; y++){
        for (int x = 0; x < width-1; x++){
            //increments x and y till (x, y) is the last bright red pixel in the zone
            if (isRed(x, y, surface)){
                for(;;){
                    if (isRed(x+1, y+1, surface) == 1){
                        x++;
                        y++;
                    }
                    else if (isRed(x+1, y, surface) == 1){
                        x++;
                    }
                    else if (isRed(x, y+1, surface) == 1){
                        y++;
                    }
                    else{
                        break;
                    }
                }
                DEBUG_NB_OF_DOTS++;
                if (i<=9){
                    SDL_Surface* image = get_RECT(x, y, surface);
                    images[j*9+i] = image;
                    i+=1;
                }
            } 
        }
        i = 0;
        j+= 1;
    }
    printf("%i dots in this image\n", DEBUG_NB_OF_DOTS);
    //SDL_UnlockSurface(surface);

    return images;
}
