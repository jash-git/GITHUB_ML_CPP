#include "LinearRegressionAlgorithm.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

LinearRegressionAlgorithm::LinearRegressionAlgorithm(double thresholdValue, double learningRate, size_t thetaParamVectorSize) :
	thresholdValue(thresholdValue), learningRate(learningRate), thetaParamVectorSize(thetaParamVectorSize)
{
	this->thetaParamVector = new double[this->thetaParamVectorSize]{ 0.0 };
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