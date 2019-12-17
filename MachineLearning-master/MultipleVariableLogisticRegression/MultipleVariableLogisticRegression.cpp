#include <iostream>
#include <stdio.h>
#include "LogisticRegressionAlgorithm.h"

#include "Data.h"

#define THETA_SIZE 3

void saveModel(const LogisticRegressionAlgorithm& lra)
{
	printf("[main::saveModel] ");
	for (size_t i = 0; i < lra.thetaParamVectorSize; i++)
	{
		printf("theta[%02d] = %5.8f, ", i, lra.thetaParamVector[i]);
	}
	printf("\n");
	FILE* fpw;
	fopen_s(&fpw, "model.txt", "w");
	fprintf_s(fpw, "%lf	%lf	%lf\r\n", lra.thetaParamVector[0], lra.thetaParamVector[1], lra.thetaParamVector[2]);
	fclose(fpw);
}

void test(const LogisticRegressionAlgorithm& lra)
{
	FILE* fpr;
	fopen_s(&fpr, "testSet.txt", "r");
	double x1, x2;
	int y;
	while (fscanf_s(fpr, "%lf	%lf	%d", &x1, &x2, &y) != EOF)
	{
		double* testDataVector = new double[3]{1.0, x1 , x2};
		double predictValue = lra.predict(testDataVector);
		int val = 0;
		if (predictValue >= 0.5) {
			val = 1;
		}
		delete[] testDataVector;
		printf("[main::test] x1 = %5.5f,	x2 = %5.5f,	real = %d,	pre = %d, prev = %5.5f\n", x1, x2, y, val, predictValue);
	}
	fclose(fpr);
}

int main()
{
	Data data(3);
	data.readData("trainSet.txt", 90);
	data.printData();
	LogisticRegressionAlgorithm lra(THETA_SIZE);
	lra.train(data);
	saveModel(lra);
	test(lra);
	system("pause");
}