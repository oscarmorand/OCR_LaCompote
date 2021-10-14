#include <stdio.h>
#include <stdlib.h>
#include <err.h> 
#include <string.h>
#include <math.h>

#include "neuralnetwork.h"
#include "printNN.h"

int main()
{
	int nbrLayers = 3;
	int nbrNeurones[] = {2,2,1};

	NN nN = CreateNN(nbrLayers, nbrNeurones);
	PrintNN(nN);

	nN.lays[0].neus[0].actv = 1.0f;
	nN.lays[0].neus[1].actv = 0.0f;
	ForwardProp(&nN);

	PrintNN(nN);

	printf("OUTPUT: %d\n\n", (int)round(nN.lays[2].neus[0].actv));

	DestroyNN(&nN);

}
