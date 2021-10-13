
#include <stdio.h>
#include <stdlib.h>
#include <err.h> 
#include <string.h>
#include <math.h>

#include "arrayaux.h"

#define NUM_INPUT 2
#define NUM_HIDDEN 2
#define NUM_OUTPUT 1
#define NUM_TRAINING_SET 4

// Activation function
double sigmoid(double x) { return (1 / (1 + exp(-x))); }

// Return a random weight between 0.0 and 1.0
double rndWeight() {return ((double)rand()) / ((double)RAND_MAX); }


void PrintNN(double inputLayer[NUM_INPUT], double hiddenLayer[NUM_HIDDEN], double outputLayer[NUM_OUTPUT]) 
{
	printf("Input Layer\n");
	for (int input = 0; input < NUM_INPUT; input++)
	{
		printf("  i%i=%f  ",input,inputLayer[input]);
	}
	printf("\nHidden Layer\n");
	for (int hidden = 0; hidden < NUM_HIDDEN; hidden++)
	{
		printf("  h%i=%f  ",hidden,hiddenLayer[hidden]);
	}
	printf("\nOutput Layer\n");
	for (int output = 0; output < NUM_OUTPUT; output++)
	{
		printf("  o%i=%f  ",output,outputLayer[output]);
	}
	printf("\n");
}


void Calculate_OutputLayer()
{

}

void Calculate_HiddenLayer()
{
	/*for (int j=0; j<numHiddenNodes; j++) {
		double activation = hiddenLayerBias[j];
		for (int k=0; k<numInputs; k++) {
			activation += training_inputs[
		}
        }*/
}

void Calculate_Output() 
{
	Calculate_HiddenLayer();
	Calculate_OutputLayer();
}

void TrainNN(int trainNbr, double hiddenLayer[NUM_HIDDEN], double outputLayer[NUM_OUTPUT]) 
{
	printf("training %i times\n", trainNbr);

	double training_inputs[NUM_TRAINING_SET][NUM_INPUT] = {{0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f}};

	double training_outputs[NUM_TRAINING_SET][NUM_OUTPUT] = {{0.0},{1.0f},{1.0f},{0.0f}};

	for (int n = 0; n < trainNbr; n++)
	{
		printf("training number %i\n",n);

		int trainingSetOrder[] = {0,1,2,3};
		RndShuffle(trainingSetOrder, NUM_TRAINING_SET);
		printf("training order = ");
		PrintIntArray(trainingSetOrder,NUM_TRAINING_SET);

		for (int x = 0; x < NUM_TRAINING_SET; x++)
		{
			int i = trainingSetOrder[x];
			double inputLayer[NUM_INPUT];
			for (int input = 0; input < NUM_INPUT; input++)
			{
				inputLayer[input] = training_inputs[i][input];
			}
			double expectedOutput = training_outputs[i][0];

			printf("Random inputs are %f and %f and expected result is %f\n", inputLayer[0], inputLayer[1], expectedOutput);

			PrintNN(inputLayer,hiddenLayer,outputLayer);
		}
	}
}


void UseNN(double inputLayer[NUM_INPUT], double hiddenLayer[NUM_HIDDEN], double outputLayer[NUM_OUTPUT]) 
{
	printf("using with %f and %f\n", inputLayer[0], inputLayer[1]);
}

int IsStrBin(char* str) {
	return ((strcmp(str,"0") == 0) || (strcmp(str,"1") == 0));
}

int main(int argc, char *argv[])
{
	
	double inputLayer[NUM_INPUT];
	double hiddenLayer[NUM_HIDDEN];
	double outputLayer[NUM_OUTPUT];

	double hiddenLayerBias[NUM_HIDDEN];
	double outputLayerBias[NUM_OUTPUT];

	double hiddenWeights[NUM_INPUT][NUM_HIDDEN];
	double outputWeights[NUM_HIDDEN][NUM_OUTPUT];

	char* param1;
	char* param2;
	int trainNbr;

	if(argc != 3) {
		errx(1,"protoNN/testNN.c : incorrect number of parameters, please enter '-train x' with x the number of iterations or 'a b' with a and b two binary numbers\n");
	}
	else {
		param1 = argv[1];
		param2 = argv[2];
		if(strcmp(param1,"-train") == 0) {
			trainNbr = atoi(param2);
			TrainNN(trainNbr, hiddenLayer, outputLayer);
		}
		else if(IsStrBin(param1) && IsStrBin(param2)) {
			inputLayer[0] = (double)(*param1)-'0';
			inputLayer[1] = (double)(*param2)-'0';
			UseNN(inputLayer, hiddenLayer, outputLayer);
		}
		else {
			errx(1,"protoNN/testNN.c : one or more parameters are not recognized, please enter '-train x' with x the number of iterations or 'a b' with a and b two binary numbers\n");
		}
	}
}
