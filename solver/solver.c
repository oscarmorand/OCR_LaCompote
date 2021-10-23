#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "solveralgo.h"
#include "parser.h"


void PrintGrid(int size, char grid[][9])
{
    int i,j;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            if(j%3 == 0)
                printf("  ");
            printf("%hhu ", grid[i][j]);
        }
        printf("\n");
        if((i+1)%3 == 0)
                printf("\n");
    }
}


/*
 * main
 */

int main(int argc, char *argv[])
{
    //Variables
    char *fileName = NULL;
    int size = 9;

    //Test arguments and initialize file name
    if(argc != 2){
        errx(1,"solver/solver.c : incorrect number of parameters, please enter only the name of the source file\n");
    }
    fileName = argv[1];

    char grid[9][9] = 
    {
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    };

    printf("Avant remplissage:\n");
    PrintGrid(size, grid);

    //Loading (Parsing)
    Load(fileName,grid);

    printf("Apres remplissage:\n");
    PrintGrid(size, grid);

    //Solving
    Solve(grid);

    printf("Apres resolution\n");
    PrintGrid(size, grid);

    //Saving
    Save(fileName, grid);

    return 0;
}