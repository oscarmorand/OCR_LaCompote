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

void InitInputs(NN* nNp, float* inputs) 
{
    NN nN = *nNp;
    for (int i = 0; i < nN.lays[0].nbNeu; i++)
    {
        nN.lays[0].neus[i].actv = inputs[i];
    }
}


Neu CreateNeuron(int nbrWeights) 
{
    Neu neuron;

    neuron.v = 0.0f;
    neuron.actv = 0.0f;
    neuron.bias = 0.0f;
    neuron.outWeights = (float*) malloc(nbrWeights * sizeof(float));
    neuron.dw = (float*) malloc(nbrWeights * sizeof(float));

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
    nN.nbNeus = (int*) malloc(nbLay * sizeof(int));
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
            free(nN.lays[i].neus[j].dw);
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
    if(x < 0)
        return 0;
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
                // add to the value the activated value of the previous neuron multiplicated by the weight of the connection
                nN.lays[i].neus[j].v += ((nN.lays[i-1].neus[k].outWeights[j]) * (nN.lays[i-1].neus[k].actv));
            
            // Relu activation function for hidden layers
            if(i < nbLay - 1)
                nN.lays[i].neus[j].actv = Relu(nN.lays[i].neus[j].v);

            // Sigmoid activation function for output layer
            else
                nN.lays[i].neus[j].actv = Sigmoid(nN.lays[i].neus[j].v);
        }
    }
}

int TestResults(NN* nNp, float* expOut) 
{
    NN nN = *nNp;
    for (int i = 0; i < nN.nbNeus[nN.nbLay-1]; i++)
    {
        //printf("output: %.0f, expected output: %.0f\n", round(nN.lays[nN.nbLay-1].neus[i].actv), expOut[i]);
        if(round(nN.lays[nN.nbLay-1].neus[i].actv) != expOut[i]) {
            //printf("faux!\n");
            return 0;
        }
    }
    //printf("c'est bon!\n");
    return 1;
}

void BackwardProp(NN* nNp, float* expOut)
{
    NN nN = *nNp;
    int* nbNeus = nN.nbNeus;
    int nbLay = nN.nbLay;
    int i,j,k;

    // Output Layer
    for (j = 0; j < nbNeus[nbLay-1]; j++)
    {
        double dv = nN.lays[nbLay-1].neus[j].actv - expOut[j];
        dv *= nN.lays[nbLay-1].neus[j].actv;
        dv *= (1 - nN.lays[nbLay-1].neus[j].actv);
        nN.lays[nbLay-1].neus[j].dv = dv;

        for (k = 0; k < nbNeus[nbLay-2]; k++)
        {
            nN.lays[nbLay-2].neus[k].dw[j] = nN.lays[nbLay-1].neus[j].dv * nN.lays[nbLay-2].neus[k].actv;
            nN.lays[nbLay-2].neus[k].dactv = nN.lays[nbLay-2].neus[k].outWeights[j] * nN.lays[nbLay-1].neus[j].dv;
        }

        nN.lays[nbLay-1].neus[j].dbias = nN.lays[nbLay-1].neus[j].dv;
    }

    // Hidden Layers
    for(i = nbLay-2; i > 0; i--)
    {
        for(j = 0; j < nbNeus[i]; j++)
        {
            if(nN.lays[i].neus[j].v >= 0)
                nN.lays[i].neus[j].dv = nN.lays[i].neus[j].dactv;
            else
                nN.lays[i].neus[j].dv = 0;

            for(k = 0; k < nbNeus[i-1]; k++)
            {
                nN.lays[i-1].neus[k].dw[j] = nN.lays[i].neus[j].dv * nN.lays[i-1].neus[k].actv;    
                
                if(i>1)
                    nN.lays[i-1].neus[k].dactv = nN.lays[i-1].neus[k].outWeights[j] * nN.lays[i].neus[j].dv;
            }

            nN.lays[i].neus[j].dbias = nN.lays[i].neus[j].dv;
        }
    }
}

void UpdateWeights(NN* nNp, float lR) 
{
    NN nN = *nNp;
    int* nbNeus = nN.nbNeus;
    int nbLay = nN.nbLay;
    int i,j,k;

    for(i = 0; i < nbLay-1; i++)
    {
        for(j = 0; j < nbNeus[i]; j++)
        {
            for(k = 0; k < nbNeus[i+1]; k++)
            {
                // Update Weights
                nN.lays[i].neus[j].outWeights[k] -= (lR * nN.lays[i].neus[j].dw[k]);
            }
            
            // Update Bias
            nN.lays[i].neus[j].bias -= (lR * nN.lays[i].neus[j].dbias);
        }
    }
}

void RandShuffle(int *array, int size)
{
    if (size > 1) 
    {
        for (int i = 0; i < size - 1; i++) 
        {
          int j = i + rand() / (RAND_MAX / (size - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void printArray(int array[], size_t len) 
{
    printf("[");
    for (size_t i = 0; i < len-1; i++)
    {
        printf("%i,",array[i]);
    }
    printf("%i]\n",array[len-1]);
}

void Train(NN* nNp, int nbTraining, float learningRate) 
{
    float tInputsSet[4][2] = {{0.0f,0.0f},{0.0f,1.0f},{1.0f,0.0f},{1.0f,1.0f}};
    float tOutputsSet[4][1] = {{0.0f},{1.0f},{1.0f},{0.0f}};
    int nbWin = 0;
    int nbTot = 0;
    int train, j;

    for (train = 0; train < nbTraining; train++)
    {
        //printf("Training number %i\n", train);
        int trainingOrder[4] = {0,1,2,3};
        RandShuffle(trainingOrder, 4);

        for (j = 0; j < 4; j++)
        {
            int i = trainingOrder[j];
            float* tInputs = tInputsSet[i];
            float* tOutputs = tOutputsSet[i];

            //printf("inputs are %.0f and %.0f\n", tInputs[0], tInputs[1]);

            InitInputs(nNp, tInputs);

            ForwardProp(nNp);

            nbWin += TestResults(nNp, tOutputs);
            nbTot += 1;

            BackwardProp(nNp, tOutputs);
            UpdateWeights(nNp, learningRate);

            //printf("\n");
        }
    }
    float winPercentage = (((float)nbWin) / ((float)nbTot)) * 100.0f;
    printf("Percentage of good predictions: %.3f%%\n", winPercentage);
}