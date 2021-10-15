#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "structsNN.h"

// Return a random weight between 0.0 and 1.0
float rndWeight();
void InitWeights(NN* nNp);

void InitInputs(NN* nNp, float* inputs);

Neu CreateNeuron(int nbrWeights);

Lay CreateLayer(int nbNeus);

NN CreateNN(int nbLay, int nbNeus[]);

void DestroyNN(NN* nNp);


float Sigmoid(float x);
float Relu(float x);

void ForwardProp(NN* nNp);

void BackwardProp(NN* nNp, float* expOut);

void RandShuffle(int *array, int size);
void Train(NN* nNp, int nbTraining);

#endif