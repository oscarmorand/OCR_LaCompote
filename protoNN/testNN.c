#include <stdio.h>
#include <stdlib.h>
#include <err.h> 
#include <string.h>
#include <math.h>
#include <time.h>

#include "neuralnetwork.h"
#include "printNN.h"
#include "saveandload.h"

int main(int argc, char *argv[])
{
	srand(time(NULL));

	int nbTraining = 100000;
	float learningRate = 0.1f;
	if(argc > 1) 
	{
		nbTraining = atoi(argv[1]);
		if(argc > 2)
			learningRate = atof(argv[2]);
	}

	int nbrLayers = 3;
	int nbrNeurones[] = {2,2,1};

	NN nN = CreateNN(nbrLayers, nbrNeurones);
	//NN nN = Load("perfectNN.txt");

	PrintNN(nN);

	Train(&nN,nbTraining, learningRate);

	Train(&nN, 10, 0);

	PrintNN(nN);

	//Save and Load

	Save(&nN, NULL);
	//PrintNN(nN);

	NN nN2 = Load(NULL);
	//PrintNN(nN2);

	Save(&nN2, "savedNN2.txt");

	DestroyNN(&nN);
	DestroyNN(&nN2);

}
