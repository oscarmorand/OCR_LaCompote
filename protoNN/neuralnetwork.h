#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "structsNN.h"


void InitWeights(NN* nNp);

void InitInputs(NN* nNp, float* inputs);

Neu CreateNeuron(int nbrWeights);

Lay CreateLayer(int nbNeus);

NN CreateNN(int nbLay, int nbNeus[]);

void DestroyNN(NN* nNp);

void ForwardProp(NN* nNp);

void BackwardProp(NN* nNp, float* expOut);

void Train(NN* nNp, int nbTraining, float learningRate);

#endif