#include <stdio.h>
#include <stdlib.h>
#include <err.h> 
#include <string.h>
#include <math.h>
#include <time.h>

#include "neuralnetwork.h"
#include "printNN.h"
#include "saveandload.h"

int nbrLayers = 5;
int nbrNeurones[] = {784, 512, 256, 128, 10};

void Help() 
{
	printf("./testNN -help\nor\n");
	printf("./testNN [Neural network creation mode] [action]\n");
	printf("[Neural network creation mode]:\n");
	printf("	-create\n");
	printf("	-load [load path]\n");
	printf("[action]:\n");
	printf("	-train [number of trainings] [learning rate] [save path]\n");
	printf("	-test [input1] [input2]\n");
	printf("	[save path] (ONLY in -create mode)\n");
}

void ErrorArgument() 
{
	printf("Error in arguments of the command\n\nHere is some documentation about this command:\n");
	Help();
	printf("\n");
	errx(1,"Arguments error");
}

void TrainNN(NN* nNp, int nbTraining, float learningRate, char* savePath)
{
	 // call to store mnist in array
    load_mnist();

	/*
    // print pixels of first data in test dataset
    int i;
    for (i=0; i<784; i++) {
        printf("%1.1f ", test_image[0][i]);
        if ((i+1) % 28 == 0) putchar('\n');
    }

    // print first label in test dataset
    printf("label: %d\n", test_label[0]);

    // save image of first data in test dataset as .pgm file
    save_mnist_pgm(test_image, 0);

    // show all pixels and labels in test dataset
    print_mnist_pixel(test_image, NUM_TEST);
    print_mnist_label(test_label, NUM_TEST);
	*/

	NN nN = *nNp;
	float winPercentage = Train(&nN, nbTraining, learningRate);;

	/*
	while(winPercentage < 95.0f) {
		DestroyNN(&nN);
		nN = CreateNN(nbrLayers, nbrNeurones);
		winPercentage = Train(&nN, nbTraining, learningRate);
	}*/

	printf("Percentage of good predictions: %f%%\n", winPercentage);

	SaveNN(nNp,savePath);
	DestroyNN(nNp);
}



void TestXOR(NN* nNp, int i1, int i2) 
{
	printf("Inputs are %i and %i\n", i1, i2);
	int expectedOut = i1^i2;
	printf("Outpout should be %i (XOR operator between the two inputs)\n", expectedOut);

	float inputs[] = {(float)i1,(float)i2};
	InitInputs(nNp, inputs);
	ForwardProp(nNp);

	NN nN = *nNp;
	int output =  (int) roundFromZeroToOne(nN.lays[nN.nbLay-1].neus[0].actv);
	printf("Output of the neural network is %i\n", output);

	if(output == expectedOut)
		printf("Successful prediction!\n");
	else
		printf("Prediction failure...\n");

	DestroyNN(nNp);
}


int main(int argc, char *argv[])
{
	srand(time(NULL));

	NN nN;
	char* savePath = NULL;
	int supArg = 0;
	if(argc == 2 && (strcmp(argv[1],"-help") == 0))
		Help();
	else if(argc >= 3) {
		// Create new neural network
		if(strcmp(argv[1],"-create") == 0) {							
			nN = CreateNN(nbrLayers, nbrNeurones);
			
			// Save the randomly generated network
			if(argc == 3) {
				savePath = argv[2];
				SaveNN(&nN, savePath);
				DestroyNN(&nN);
			}
		}
		// Load an existing neural network
		else if(strcmp(argv[1], "-load") == 0) {
			char* loadPath = argv[2];
			nN = LoadNN(loadPath);
			supArg = 1;
		}
		else
			ErrorArgument();

		// Testing mode
		if(argc == 5+supArg && (strcmp(argv[2+supArg], "-test") == 0)) { 
			int i1 = atof(argv[3+supArg]);
			int i2 = atof(argv[4+supArg]);
			TestXOR(&nN, i1, i2);
		}
		// Training mode
		else if(argc == 6+supArg && (strcmp(argv[2+supArg], "-train") == 0)) {
			int nbTraining = atoi(argv[3+supArg]);
			float learningRate = atof(argv[4+supArg]);
			savePath = argv[5+supArg];
			TrainNN(&nN, nbTraining, learningRate, savePath);
		}
		else
			ErrorArgument();
	}
	else
		ErrorArgument();
}
