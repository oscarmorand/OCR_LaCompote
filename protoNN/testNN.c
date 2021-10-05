
#include <stdio.h>

Calculate_OutputLayer()
{

}

Calculate_HiddenLayer()
{
	for (int j=0; j<numHiddenNodes; j++) {
		double activation = hiddenLayerBias[j];
		for (int k=0; k<numInputs; k++) {
			activation += training_inputs[
		}
        }
}

Calculate_Output() 
{
	Calculate_HiddenLayer();
	Calculate_OutputLayer();
}

int main()
{
	static const int numInputs = 2;
	static const int numHiddenNodes = 2;
	static const int numOutputs = 1;

	double hiddenLayer [numHiddenNodes];
	double outputLayer [numOutputs];

	double hiddenLayerBias[numHiddenNodes];
	double outputLayerBias[numOutputs];

	double hiddenWeights[numInputs][numHiddenNodes];
	double outputWeights[numHiddenNodes][numOutputs];


	static const int numTrainingSets = 4;

	double training_inputs[numTrainingSets][numInputs] = {{0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f}};

	double training_outputs[numTrainingSets][numOutputs] = {{0.0},{1.0f},{1.0f},{0.0f}};

	Calculate_Output();
}
