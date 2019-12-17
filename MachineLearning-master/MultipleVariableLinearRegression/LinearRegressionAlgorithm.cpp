#include "LinearRegressionAlgorithm.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_RANGE 50

LinearRegressionAlgorithm::LinearRegressionAlgorithm(size_t thetaParamVectorSize, double thresholdValue, double learningRate):
	thetaParamVectorSize(thetaParamVectorSize), thresholdValue(thresholdValue), learningRate(learningRate)
{
	this->thetaParamVector = new double[this->thetaParamVectorSize]{ 0.0 };
	for (size_t i = 0; i < this->thetaParamVectorSize; i++)
	{
		this->thetaParamVector[i] = (double)(rand() % MAX_RANGE) + (rand() % RAND_MAX) / (RAND_MAX * 1.0);
	}
}

LinearRegressionAlgorithm::~LinearRegressionAlgorithm()
{
	delete[] this->thetaParamVector;
}

// 预测
double LinearRegressionAlgorithm::predict(double *paramVector)
{
	double sum = 0.0;
	for (size_t i = 0; i < this->thetaParamVectorSize; i++)
	{
		sum += this->thetaParamVector[i] * paramVector[i];
	}
	return sum;
}

// 梯度下降算法
void LinearRegressionAlgorithm::GradientDescentAlgorithm(const Data& data)
{
	// 梯度向量
	double* gradient = new double[this->thetaParamVectorSize]{ 0.0 };
	for (size_t j = 0; j < data.trainDataMatrixColSize; j++)
	{
		for (size_t i = 0; i < data.trainDataMatrixRowSize; i++)
		{
			gradient[j] += (this->predict(data.trainDataMatrix[i]) - data.realValueVector[i]) * data.trainDataMatrix[i][j];
		}
		this->thetaParamVector[j] = this->thetaParamVector[j] - (this->learningRate * gradient[j]) / (data.trainDataMatrixRowSize * 1.0);
	}
	delete[] gradient;
}

// 训练
void LinearRegressionAlgorithm::train(const Data& data)
{
	double* beforeThetaVector = new double[this->thetaParamVectorSize]{0.0};
	double* afterThetaVector = new double[this->thetaParamVectorSize]{0.0};

	// 迭代梯度下降
	while (true)
	{
		printf("[LinearRegressionAlgorithm::train] ");
		bool breakflag = true;
		for (size_t i = 0; i < this->thetaParamVectorSize; i++)
		{
			beforeThetaVector[i] = this->thetaParamVector[i];
		}

		this->GradientDescentAlgorithm(data);

		for (size_t i = 0; i < this->thetaParamVectorSize; i++)
		{
			afterThetaVector[i] = this->thetaParamVector[i];
			printf("theta[%d] = %5.10f,  ", i, afterThetaVector[i]);
			if (fabs(afterThetaVector[i] - beforeThetaVector[i]) > this->thresholdValue)
			{
				breakflag = false;
			}
		}
		printf("\n");
		if (breakflag) break;
	}
	delete[] beforeThetaVector;
	delete[] afterThetaVector;
}
