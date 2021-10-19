#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <err.h>

#include "structsNN.h"
#include "neuralnetwork.h"

#define NDECDIGITS 5
#define NDIGITS 3

void PutFloatFP(float x, FILE* fp) 
{
    char* s = (char*) malloc((NDIGITS  + NDECDIGITS + 3) * sizeof(char));

    sprintf(s, "%.5f", x);
    strcat(s, ",");
    fputs(s, fp);

    free(s);
}

void PutIntFP(int x, FILE* fp) 
{
    char* s = (char*) malloc(((int)(log10((double)x)) + 3) * sizeof(char));

    sprintf(s, "%i", x);
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
    int nbLay = nN.nbLay;

    // Save number of layer and number of neurons in each layer
    PutIntFP(nbLay,fp);
    fputc((char)'\n',fp);
    for (int i = 0; i < nbLay; i++)
    {
        PutIntFP(nN.nbNeus[i], fp);
    }
    fputc((char)'\n',fp);
    fputc((char)'\n',fp);
    
    // Save input and hidden layers with biais and all outweights
    for (int i = 0; i < nbLay-1; i++)
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
            fputc((char)'\n',fp);
        }
        fputc((char)'\n',fp);
    }
    // Save output layer with only biais
    for (int j = 0; j < nN.lays[nbLay-1].nbNeu; j++)
    {
        Neu neu = nN.lays[nbLay-1].neus[j];
        PutFloatFP(neu.bias, fp);
        fputc((char)'\n',fp);
    }
    fputc((char)'\n',fp);

    //Close file
    int closeReturn = fclose(fp);
    if(closeReturn == (int) EOF) {
        // error
    }
}



float LoadNextFloat(FILE* fp) 
{
    int c;
    float f = 0;
    int decimal = 0;
    int nbDecimal = 0;
    int sign = 1;
    while((c = fgetc(fp)) != ',') {
        if(c == '-')
            sign = -1;
        else if(c == '.') 
            decimal = 1;
        else {
            if(decimal)
                nbDecimal += 1;
            f *= 10;
            f += c-'0';
        }
    }
    f = sign * (f/(pow(10,nbDecimal)));
    return f;
}

int LoadNextInt(FILE* fp) 
{
    int c;
    int x = 0;
    while((c = fgetc(fp)) != ',') {
        x *= 10;
        x += c-'0';
    }
    return x;
}

NN Load(char* path) 
{
    if(path == NULL)
        path = "savedNN.txt";

    //Open file
    FILE *fp = NULL;
    fp = fopen (path, "r");
    if(fp == NULL) {
        // error
    }

    NN nN;

    nN.nbLay = LoadNextInt(fp);
    fgetc(fp);

    // get the array with the number of neurons in each layer
    nN.nbNeus = (int*) malloc(nN.nbLay * sizeof(int));
    for (int i = 0; i < nN.nbLay; i++)
        nN.nbNeus[i] = LoadNextInt(fp);
    fgetc(fp);
    fgetc(fp);

    // get all the biais and weights
    nN.lays = (Lay*) malloc(nN.nbLay * sizeof(Lay));
    for (int i = 0; i < nN.nbLay; i++)
    {
        nN.lays[i] = CreateLayer(nN.nbNeus[i]);

        for (int j = 0; j < nN.nbNeus[i]; j++)
        {
            // input and hidden layers
            if(i < nN.nbLay-1) 
                nN.lays[i].neus[j] = CreateNeuron(nN.nbNeus[i+1]);
            // output layer
            else 
                nN.lays[i].neus[j] = CreateNeuron(0);

            // get bias
            nN.lays[i].neus[j].bias = LoadNextFloat(fp);

            // get weights
            if(i < nN.nbLay-1) 
            {
                for (int k = 0; k < nN.nbNeus[i+1]; k++) 
                    nN.lays[i].neus[j].outWeights[k] = LoadNextFloat(fp);
            }
            fgetc(fp);
        }
        fgetc(fp);
    }

    //Close file
    int closeReturn = fclose(fp);
    if(closeReturn == (int) EOF) {
        // error
    }

    return nN;
}