#include <stdio.h>
#include <stdlib.h>
#include <err.h> 
#include <math.h>

typedef struct neuron_t
{
	float actv;
	float* outWeights;
	float bias;
	float z;

	float dactv;
	float *dw;
	float dbias;
	float dz;
  
} Neuron;

typedef struct layer_t
{
    int nbrNeu;
    struct neuron_t* neurons;
} Layer;

typedef struct neuraln_t
{
    int nbrLayers;
    int* nbrNeurons;
    struct layer_t* layers;
} NeuralN;

void PrintNN(NeuralN neuralN) 
{
    int* nbrNeurons = neuralN.nbrNeurons;
    int nbrLayers = neuralN.nbrLayers;
    Layer* layers = neuralN.layers;

    printf("Input Layer\n");
    for (int j = 0; j < nbrNeurons[0]; j++)
    {
        printf("  i%i: %f, %f  ", j, layers[0].neurons[j].actv, layers[0].neurons[j].bias);
    }
    printf("\nHidden Layer\n");
    for (int i = 1; i < nbrLayers-1; i++)
    {
        for (int j = 0; j < nbrNeurons[i]; j++)
            printf("  h%i%i: %f, %f  ", i, j, layers[i].neurons[j].actv, layers[i].neurons[j].bias);
    }
    printf("\nOutput Layer\n");
    for (int j = 0; j < nbrNeurons[nbrLayers-1]; j++)
    {
        printf("  o%i: %f, %f  ", j, layers[nbrLayers-1].neurons[j].actv, layers[nbrLayers-1].neurons[j].bias);
    }
    printf("\n");
}


// Return a random weight between 0.0 and 1.0
float rndWeight() {return ((float)rand()) / ((float)RAND_MAX); }

void InitWeights(NeuralN* neuralNP) 
{
    NeuralN neuralN = *neuralNP;

    int i, j, k;
    for (i = 0; i < neuralN.nbrLayers-1; i++)
    {
        for (j = 0; j < neuralN.nbrNeurons[i]; j++)
        {
            for (k = 0; k < neuralN.nbrNeurons[i+1]; k++)
                neuralN.layers[i].neurons[j].outWeights[k] = rndWeight();
        }
    }
}


Neuron CreateNeuron(int nbrWeights) 
{
    Neuron neuron;

    neuron.z = 0.0f;
    neuron.actv = 0.0f;
    neuron.bias = 0.0f;
    neuron.outWeights = (float*) malloc(nbrWeights * sizeof(float));

    return neuron;
}

Layer CreateLayer(int nbrNeurons) 
{
    Layer layer;

    layer.nbrNeu = nbrNeurons;
    layer.neurons = (Neuron*) malloc(nbrNeurons * sizeof(Neuron));

    return layer;
}

NeuralN CreateNN(int nbrLayers, int nbrNeurons[]) 
{
    NeuralN neuralN;

    neuralN.nbrLayers = nbrLayers;
    neuralN.nbrNeurons = (int*) malloc(sizeof(nbrNeurons) * sizeof(int));
    neuralN.layers = (Layer*) malloc(nbrLayers * sizeof(Layer));

    int i=0, j=0;
    for (i = 0; i < nbrLayers; i++)
    {
        neuralN.nbrNeurons[i] = nbrNeurons[i];
        neuralN.layers[i] = CreateLayer(nbrNeurons[i]);

        printf("Created Layer number %i\n", i+1);
        printf("Number of Neurons in Layer %i: %i\n", i+1, neuralN.layers[i].nbrNeu);

        for (j = 0; j < nbrNeurons[i]; j++)
        {
            if(i < nbrLayers-1) 
                neuralN.layers[i].neurons[j] = CreateNeuron(nbrNeurons[i+1]);
            else
                neuralN.layers[i].neurons[j] = CreateNeuron(0);

            printf("Neuron %i in Layer %i created\n", j+1, i+1);
        }
        printf("\n"); 
    }
    printf("\n");

    InitWeights(&neuralN);

    return neuralN;
}

void DestroyNN(NeuralN* neuralNP) 
{
    NeuralN neuralN = *neuralNP;
    for (int i = 0; i < neuralN.nbrLayers; i++)
    {
        for (int j = 0; j < neuralN.nbrNeurons[i]; j++)
        {
            free(neuralN.layers[i].neurons[j].outWeights);
        }
        free(neuralN.layers[i].neurons);
    }
    free(neuralN.layers);
    free(neuralN.nbrNeurons);
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

void ForwardProp(Layer* layers, int nbrLayers, int nbrNeurons[])
{
    int i,j,k;

    for (i = 1; i < nbrLayers; i++)                                 // for each layers except the input layer which hasn't a previous layer
    {
        for (j = 0; j < nbrNeurons[i]; j++)                         // for each neurons in the layer
        {
            layers[i].neurons[j].z = layers[i].neurons[j].bias;     // first term of the formula is the biais

            for (k = 0; k < nbrNeurons[i-1]; k++)                   // for each neuron of the previous layer
            {
                layers[i].neurons[j].z = layers[i].neurons[j].z + ((layers[i-1].neurons[k].outWeights[j]) * (layers[i-1].neurons[k].actv));
                //layers[i].neurons[j].z += ((layers[i-1].neurons[k].outWeights[j]) * (layers[i-1].neurons[k].actv));
            }
            
            // Relu activation function for hidden layers
            if(i < nbrLayers - 1) {
                layers[i].neurons[j].actv = Relu(layers[i].neurons[j].z);
            }

            // Sigmoid activation function for output layer
            else {
                layers[i].neurons[j].actv = Sigmoid(layers[i].neurons[j].z);
                printf("OUTPUT: %d\n", (int)round(layers[i].neurons[j].actv));
            }
        }
    }
}