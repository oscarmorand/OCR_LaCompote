#include <stdio.h>
#include <stdlib.h>
#include <err.h> 
#include <string.h>
#include <math.h>

#include "neuralnetwork.h"
#include "printNN.h"
#include "saveandload.h"

int main()
{
	int nbrLayers = 3;
	int nbrNeurones[] = {2,2,1};

	NN nN = CreateNN(nbrLayers, nbrNeurones);
	PrintNN(nN);

	Train(&nN,2);

	Save(&nN, NULL);
	PrintNN(nN);

	NN nN2 = Load(NULL);
	PrintNN(nN2);

	Save(&nN2, "savedNN2.txt");

	DestroyNN(&nN);
	DestroyNN(&nN2);

}
