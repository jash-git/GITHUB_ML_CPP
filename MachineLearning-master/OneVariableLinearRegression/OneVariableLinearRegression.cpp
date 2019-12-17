
#include <iostream>
#include <time.h>
#include "LinearRegressionAlgorithm.h"

#define DATA_SIZE 100

int main()
{
	srand((unsigned int)time(0));
	Data data(DATA_SIZE);
	data.printData();
	printf("[main::DataTheta]  theta[0] = x = %5.8f, theta[1] = %5.8f\n", data.thetaParamVector[0], data.thetaParamVector[1]);
	LinearRegressionAlgorithm lra(0.0000000001);
	lra.train(data);
	printf("[main::DataTheta]  theta[0] = x = %5.8f, theta[1] = %5.8f\n", data.thetaParamVector[0], data.thetaParamVector[1]);
	printf("[main::TrainTheta] theta[0] = x = %5.8f, theta[1] = %5.8f\n", lra.thetaParamVector[0], lra.thetaParamVector[1]);
}
