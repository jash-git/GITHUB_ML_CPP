#include "LinearRegressionAlgorithm.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_RANGE 50

LinearRegressionAlgorithm::LinearRegressionAlgorithm(double thresholdValue, double learningRate, size_t thetaParamVectorSize) :
	thresholdValue(thresholdValue), learningRate(learningRate), thetaParamVectorSize(thetaParamVectorSize)
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
double LinearRegressionAlgorithm::predict(double param)
{
	return this->thetaParamVector[0] * 1.0 + this->thetaParamVector[1] * param;
}

// 梯度下降算法
void LinearRegressionAlgorithm::GradientDescentAlgorithm(const Data& data)
{
	// 梯度向量
	double* gradient = new double[this->thetaParamVectorSize]{ 0.0 };
	for (size_t i = 0; i < data.trainDataVectorSize; i++)
	{
		double predictVal = this->predict(data.trainDataVector[i]);
		gradient[0] += predictVal - data.realValueVector[i];
		gradient[1] += (predictVal - data.realValueVector[i]) * data.trainDataVector[i];
	}
	this->thetaParamVector[0] -= (this->learningRate * gradient[0]) / (data.trainDataVectorSize * 1.0);
	this->thetaParamVector[1] -= (this->learningRate * gradient[1]) / (data.trainDataVectorSize * 1.0);
	delete[] gradient;
}

// 训练
void LinearRegressionAlgorithm::train(const Data & data)
{
	double* beforeThetaVector = new double[this->thetaParamVectorSize];
	double* afterThetaVector = new double[this->thetaParamVectorSize];

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