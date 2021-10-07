#include <stdio.h>
# include <err.h>

#include "solveralgo.h"


/*
 * main
 */

int main(int argc, char *argv[])
{
    if(argc != 2){
        errx(1,"solver/solver.c : incorrect number of parameters, please enter only the name of the source file");
    }
    char *path = argv[1];
    printf("%s\n",path);
}