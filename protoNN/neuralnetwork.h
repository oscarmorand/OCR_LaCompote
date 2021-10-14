#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

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

// Basic print of the neural network
//void PrintNN(Layer* layers, int nbrLayers, int nbrNeurons[]);
void PrintNN(NeuralN neuralN);

// Return a random weight between 0.0 and 1.0
float rndWeight();

// Initialize all weights between neurons of all the neural network
//void InitWeights(Layer* layers, int nbrLayers, int nbrNeurons[]);
void InitWeights(NeuralN* neuralNP);


Neuron CreateNeuron(int nbrWeights);

Layer CreateLayer(int nbrNeurons);

NeuralN CreateNN(int nbrLayers, int nbrNeurons[]);

void DestroyNN(NeuralN* neuralNP);


float Sigmoid(float x);

float Relu(float x);

void ForwardProp(Layer* layers, int nbrLayers, int nbrNeurons[]);

#endif