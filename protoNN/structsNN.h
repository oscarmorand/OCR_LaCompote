#ifndef STRUCTSNN_H
#define STRUCTSNN_H

typedef struct neu_t
{
	float actv;
	float* outWeights;
	float bias;
	float v;

	float dactv;
	float* dw;
	float dbias;
	float dv;
  
} Neu;

typedef struct lay_t
{
    int nbNeu;
    struct neu_t* neus;
} Lay;

typedef struct nn_t
{
    int nbLay;
    int* nbNeus;
    struct lay_t* lays;
} NN;

#endif