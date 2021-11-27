#include <stdio.h>

#include "structsNN.h"

void PrintWeights(Neu neu, int nbNeusNext) 
{
    printf("[");
    for (int i = 0; i < nbNeusNext-1; i++)
    {
        printf("%.2f,", neu.outWeights[i]);
    }
    printf("%.2f]", neu.outWeights[nbNeusNext-1]);
}

void PrintNN(NN* nNp) 
{
    NN nN = *nNp;
    int* nbNeus = nN.nbNeus;
    int nbLay = nN.nbLay;
    Lay* lays = nN.lays;

    printf("Input layer\n");
    for (int j = 0; j < nbNeus[0]; j++)
    {
        printf("   i%i: %.2f, %.2f, ", j, lays[0].neus[j].actv, lays[0].neus[j].bias);
        PrintWeights(lays[0].neus[j], lays[1].nbNeu);
        printf("   ");
    }
    printf("\nHidden layers\n");
    for (int i = 1; i < nbLay-1; i++)
    {
        for (int j = 0; j < nbNeus[i]; j++) {
            printf("  h%i%i: %.2f, %.2f, ", i, j, lays[i].neus[j].actv, lays[i].neus[j].bias);
            PrintWeights(lays[i].neus[j], lays[i+1].nbNeu);
            printf("   ");
        }
        printf("\n");
    }
    printf("\nOutput layer\n");
    for (int j = 0; j < nbNeus[nbLay-1]; j++)
    {
        printf("  o%i: %.2f, %.2f  ", j, lays[nbLay-1].neus[j].actv, lays[nbLay-1].neus[j].bias);
    }
    printf("\n\n");
}