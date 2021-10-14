#include <stdio.h>
#include <stdlib.h>
#include <err.h> 
#include <math.h>

#include "structsNN.h"


// Return a random weight between 0.0 and 1.0
float rndWeight() {return ((float)rand()) / ((float)RAND_MAX); }

void InitWeights(NN* nNp) 
{
    NN nN = *nNp;

    int i, j, k;
    for (i = 0; i < nN.nbLay-1; i++)
    {
        for (j = 0; j < nN.nbNeus[i]; j++)
        {
            for (k = 0; k < nN.nbNeus[i+1]; k++)
                nN.lays[i].neus[j].outWeights[k] = rndWeight();
        }
    }
}


Neu CreateNeuron(int nbrWeights) 
{
    Neu neuron;

    neuron.v = 0.0f;
    neuron.actv = 0.0f;
    neuron.bias = 0.0f;
    neuron.outWeights = (float*) malloc(nbrWeights * sizeof(float));

    return neuron;
}

Lay CreateLayer(int nbNeus) 
{
    Lay layer;

    layer.nbNeu = nbNeus;
    layer.neus = (Neu*) malloc(nbNeus * sizeof(Neu));

    return layer;
}

NN CreateNN(int nbLay, int nbNeus[]) 
{
    NN nN;

    nN.nbLay = nbLay;
    nN.nbNeus = (int*) malloc(sizeof(nbNeus) * sizeof(int));
    nN.lays = (Lay*) malloc(nbLay * sizeof(Lay));

    int i=0, j=0;
    for (i = 0; i < nbLay; i++)
    {
        nN.nbNeus[i] = nbNeus[i];
        nN.lays[i] = CreateLayer(nbNeus[i]);

        printf("Created layer number %i\n", i+1);
        printf("Number of Neurons in layer %i: %i\n", i+1, nN.lays[i].nbNeu);

        for (j = 0; j < nbNeus[i]; j++)
        {
            if(i < nbLay-1) 
                nN.lays[i].neus[j] = CreateNeuron(nbNeus[i+1]);
            else
                nN.lays[i].neus[j] = CreateNeuron(0);

            printf("Neuron %i in layer %i created\n", j+1, i+1);
        }
        printf("\n"); 
    }
    printf("\n");

    InitWeights(&nN);

    return nN;
}

void DestroyNN(NN* nNp) 
{
    NN nN = *nNp;
    for (int i = 0; i < nN.nbLay; i++)
    {
        for (int j = 0; j < nN.nbNeus[i]; j++)
        {
            free(nN.lays[i].neus[j].outWeights);
        }
        free(nN.lays[i].neus);
    }
    free(nN.lays);
    free(nN.nbNeus);
}


float Sigmoid(float x) {
    return (1 / (1 + exp(-x)));
}

float Relu(float x) {
    if(x < 0) {
        return 0;
    }
    return x;
}


void ForwardProp(NN* nNp)
{
    NN nN = *nNp;
    int* nbNeus = nN.nbNeus;
    int nbLay = nN.nbLay;

    int i,j,k;

    for (i = 1; i < nbLay; i++)                                         // for each layer except the input layer which hasn't a previous layer
    {
        for (j = 0; j < nbNeus[i]; j++)                                 // for each neurons in the layer
        {
            nN.lays[i].neus[j].v = nN.lays[i].neus[j].bias;             // first term of the formula is the biais

            for (k = 0; k < nbNeus[i-1]; k++)                           // for each neuron of the previous layer
            {
                // add to the value the activated value of the previous neuron multiplicated by the weight of the connection
                nN.lays[i].neus[j].v += ((nN.lays[i-1].neus[k].outWeights[j]) * (nN.lays[i-1].neus[k].actv));
            }
            
            // Relu activation function for hidden layers
            if(i < nbLay - 1) {
                nN.lays[i].neus[j].actv = Relu(nN.lays[i].neus[j].v);
            }

            // Sigmoid activation function for output layer
            else {
                nN.lays[i].neus[j].actv = Sigmoid(nN.lays[i].neus[j].v);
            }
        }
    }
}