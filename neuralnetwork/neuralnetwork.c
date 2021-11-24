#include <stdio.h>
#include <stdlib.h>
#include <err.h> 
#include <math.h>

#include "structsNN.h"
#include "printNN.h"

// Return a random weight between 0.0 and 1.0
float rndWeight() {
    return (((float)rand()) / ((float)RAND_MAX)); 
}

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
    neuron.dbiasTot = 0.0f;
    neuron.outWeights = (float*) malloc(nbrWeights * sizeof(float));
    neuron.dw = (float*) malloc(nbrWeights * sizeof(float));
    neuron.dwTot = (float*) malloc(nbrWeights * sizeof(float));

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

        for (j = 0; j < nbNeus[i]; j++)
        {
            if(i < nbLay-1) 
                nN.lays[i].neus[j] = CreateNeuron(nbNeus[i+1]);
            else
                nN.lays[i].neus[j] = CreateNeuron(0);

        } 
    }

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
            free(nN.lays[i].neus[j].dwTot);
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



float QuadCostFunc(Lay* outputLayer, float* expOuts) 
{
    float sum = 0.0f;
    for (int i = 0; i < (*outputLayer).nbNeu; i++)
    {
        float diff = (*outputLayer).neus[i].actv - expOuts[i];
        sum += (diff * diff);
    }
    return sum;
}

float dCost(float output, float expOut) 
{
    return 2 * (output - expOut);
}


void BackwardProp(NN* nNp, float* expOut)
{
    NN nN = *nNp;
    int* nbNeus = nN.nbNeus;
    int nbLay = nN.nbLay;
    Lay* lays = nN.lays;
    int i,j,k;

    // Output Layer

    // for each neuron of the output layer
    int outputLayer = nbLay-1;
    for (j = 0; j < nbNeus[outputLayer]; j++)
    {
        // Calculate how much the cost function change when the output from the neuron change -> derivative of cost function
        float dCdO = dCost(lays[outputLayer].neus[j].actv, expOut[j]);
        // Calculate how much the output change when the input change -> derivative of activation function (here Sigmoid)
        float dOdi = lays[outputLayer].neus[j].actv * (1 - lays[outputLayer].neus[j].actv);
        // Calculate how much the cost function change when the input change -> product of these two partial derivatives
        float dCdi = dCdO * dOdi;
        lays[outputLayer].neus[j].dv = dCdi;

        // for each neuron of the layer before ouput layer
        for (k = 0; k < nbNeus[outputLayer-1]; k++)
        {
            // Calculate how much the input change when the weight change -> d(O*w + b)/dw = O -> only the output of previous layer
            float didw = lays[outputLayer-1].neus[k].actv;
            lays[outputLayer-1].neus[k].dw[j] = dCdi * didw;
            lays[outputLayer-1].neus[k].dwTot[j] += lays[outputLayer-1].neus[k].dw[j];

            // Calculate how much the inut change when the output of previous layer neuron change -> d(Ow+b)/dO = w -> only the weight of previous layer
            float didOh = lays[outputLayer-1].neus[k].outWeights[j];
            lays[outputLayer-1].neus[k].dactv = dCdi * didOh;
        }

        lays[outputLayer].neus[j].dbias = dCdi;
        lays[outputLayer].neus[j].dbiasTot += lays[outputLayer].neus[j].dbias;
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
                nN.lays[i-1].neus[k].dwTot[j] += nN.lays[i-1].neus[k].dw[j];  
                
                if(i>1)
                    nN.lays[i-1].neus[k].dactv = nN.lays[i-1].neus[k].outWeights[j] * nN.lays[i].neus[j].dv;
            }

            nN.lays[i].neus[j].dbias = nN.lays[i].neus[j].dv;
            nN.lays[i].neus[j].dbiasTot += nN.lays[i].neus[j].dbias;
        }
    }
}

void UpdateWeights(NN* nNp, float lR, int nbTests) 
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
                nN.lays[i].neus[j].outWeights[k] -= ((lR * nN.lays[i].neus[j].dwTot[k])/nbTests);
            }
            
            // Update Bias
            nN.lays[i].neus[j].bias -= ((lR * nN.lays[i].neus[j].dbiasTot)/nbTests);
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

float roundFromZeroToOne(float x) 
{
    if(x < 0.6f)
        return 0.f;
    return 1.f;
}

int TestResults(NN* nNp, float* expOut) 
{
    NN nN = *nNp;
    for (int i = 0; i < nN.nbNeus[nN.nbLay-1]; i++)
    {
        if(roundFromZeroToOne(nN.lays[nN.nbLay-1].neus[i].actv) != expOut[i])
            return 0;
    }
    return 1;
}

void SetValuesToZero(NN* nNp, int resTot) {
    NN nN = *nNp;
    int* nbNeus = nN.nbNeus;
    int nbLay = nN.nbLay;
    int i,j,k;

    for(i = 0; i < nbLay; i++)
    {
        for(j = 0; j < nbNeus[i]; j++)
        {
            nN.lays[i].neus[j].v = 0.0f;
            nN.lays[i].neus[j].actv = 0.0f;
            nN.lays[i].neus[j].dv = 0.0f;
            nN.lays[i].neus[j].dactv = 0.0f;
            if(resTot) {
                if(i < nbLay -1) 
                {
                    for (k = 0; k < nbNeus[i+1]; k++)
                        nN.lays[i].neus[j].dwTot[k] = 0.0f;
                }
                nN.lays[i].neus[j].dbiasTot = 0.0f;
            }
        }
    }
}

float Train(NN* nNp, int nbTraining, float learningRate) 
{
    float tInputsSet[4][2] = {{0.0f,0.0f},{0.0f,1.0f},{1.0f,0.0f},{1.0f,1.0f}};
    float tOutputsSet[4][1] = {{0.0f},{1.0f},{1.0f},{0.0f}};
    int nbWin = 0, nbTot = 0, nbTestInTraining = 4;
    int train, j;

    for (train = 0; train < nbTraining; train++)
    {
        int trainingOrder[4] = {0,1,2,3};
        RandShuffle(trainingOrder, 4);

        for (j = 0; j < nbTestInTraining; j++)
        {
            int i = trainingOrder[j];
            float* tInputs = tInputsSet[i];
            float* tOutputs = tOutputsSet[i];

            InitInputs(nNp, tInputs);

            ForwardProp(nNp);

            nbWin += TestResults(nNp, tOutputs);
            nbTot += 1;

            BackwardProp(nNp, tOutputs);
            SetValuesToZero(nNp,0);
        }

        UpdateWeights(nNp, learningRate, nbTestInTraining);

        SetValuesToZero(nNp,1);
    }
    float winPercentage = (((float)nbWin) / ((float)nbTot)) * 100.0f;
    return winPercentage;
}