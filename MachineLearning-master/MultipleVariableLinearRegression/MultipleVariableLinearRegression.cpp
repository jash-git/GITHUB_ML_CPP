
#include <iostream>
#include <time.h>
#include "Data.h"
#include "LinearRegressionAlgorithm.h"


#define THETA_SIZE 5
#define DATA_SIZE 100

void printDataTheta(const Data& data)
{
	printf("[main::DataTheta]  ");
	for (size_t i = 0; i < data.thetaParamVectorSize; i++)
	{
		printf("theta[%d] = %5.8f, ", i, data.thetaParamVector[i]);
	}
	printf("\n");
}

void printLinearRegressionAlgorithmTheta(const LinearRegressionAlgorithm& lra)
{
	printf("[main::TrainTheta] ");
	for (size_t i = 0; i < lra.thetaParamVectorSize; i++)
	{
		printf("theta[%d] = %5.8f, ", i, lra.thetaParamVector[i]);
	}
	printf("\n");
}

int main()
{
	srand((unsigned int)time(0));
	Data data(DATA_SIZE, THETA_SIZE);
	data.printData();
	printDataTheta(data);
	
	LinearRegressionAlgorithm lra(THETA_SIZE);
	printLinearRegressionAlgorithmTheta(lra);
	lra.train(data);
	printDataTheta(data);
	printLinearRegressionAlgorithmTheta(lra);
}
