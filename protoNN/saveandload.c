#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structsNN.h"
#include "neuralnetwork.h"

#define NDECDIGITS 5
#define NDIGITS 2

void PutFloatFP(float x, FILE* fp) 
{
    char* s = (char*) malloc((NDIGITS  +NDECDIGITS + 2) * sizeof(char));

    sprintf(s, "%.5f", x);
    strcat(s, ",");
    fputs(s, fp);

    free(s);
}

void Save(NN* nNp, char* path) 
{
    if(path == NULL)
        path = "savedNN.txt";

    //Open file
    FILE* fp = NULL;
    fp = fopen (path, "w");
    if(fp == NULL) {
        // erreur
    }

    NN nN = *nNp;
    // Save input and hidden layers with biais and all outweights
    for (int i = 0; i < nN.nbLay-1; i++)
    {
        Lay lay = nN.lays[i];
        for (int j = 0; j < lay.nbNeu; j++)
        {
            Neu neu = lay.neus[j];
            PutFloatFP(neu.bias, fp);
            for (int k = 0; k < nN.lays[i+1].nbNeu; k++)
            {
                PutFloatFP(neu.outWeights[k], fp);
            }
            fputs("\n",fp);
        }
        fputs("\n",fp);
    }
    // Save output layer with only biais
    for (int j = 0; j < nN.lays[nN.nbLay-1].nbNeu; j++)
    {
        Neu neu = nN.lays[nN.nbLay-1].neus[j];
        PutFloatFP(neu.bias, fp);
        fputs("\n",fp);
    }
    fputs("\n",fp);

    //Close file
    int closeReturn = fclose(fp);
    if(closeReturn == (int) EOF) {
        // error
    }
}

NN* Load(char* path) 
{
    if(path == NULL)
        path = "savedNN.txt";

    //Open file
    FILE *fp = NULL;
    fp = fopen (path, "r");
    if(fp == NULL) {
        // error
    }

    char c;
    while((c = fgetc(fp)) != EOF) 
    {
        while (c != '\n')
        {
            /* code */
        }
        
    }
}