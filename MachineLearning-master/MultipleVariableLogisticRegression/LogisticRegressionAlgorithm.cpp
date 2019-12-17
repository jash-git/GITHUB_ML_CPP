#include "LogisticRegressionAlgorithm.h"
#include <math.h>
#include <stdio.h>


LogisticRegressionAlgorithm::LogisticRegressionAlgorithm(size_t thetaParamVectorSize, double thresholdValue, double learningRate) :
	thetaParamVectorSize(thetaParamVectorSize), thresholdValue(thresholdValue), learningRate(learningRate)
{
	this->thetaParamVector = new double[this->thetaParamVectorSize]{ 0.0 };
}


LogisticRegressionAlgorithm::~LogisticRegressionAlgorithm()
{
	delete[] this->thetaParamVector;
}

// 逻辑函数
double LogisticRegressionAlgorithm::sigmoid(double x) const
{
	return 1.0 / (1.0 + exp(-x));
}

// 预测
double LogisticRegressionAlgorithm::predict(double* paramVector) const
{
	double sum = 0.0;
	for (size_t i = 0; i < this->thetaParamVectorSize; i++)
	{
		sum += this->thetaParamVector[i] * paramVector[i];
	}
	return this->sigmoid(sum);
}

// 梯度提升算法
void LogisticRegressionAlgorithm::GradientBoostAlgorithm(const Data& data)
{
	// 梯度向量
	double* gradient = new double[this->thetaParamVectorSize]{ 0.0 };
	for (size_t j = 0; j < data.trainDataMatrixColSize; j++)
	{
		for (size_t i = 0; i < data.trainDataMatrixRowSize; i++)
		{
			gradient[j] += ( data.realValueVector[i] * 1.0 - this->predict(data.trainDataMatrix[i]) ) * data.trainDataMatrix[i][j];
		}
		this->thetaParamVector[j] = this->thetaParamVector[j] + this->learningRate * gradient[j];
	}
	delete[] gradient;
}

// 训练
void LogisticRegressionAlgorithm::train(const Data & data)
{
	double* beforeThetaVector = new double[this->thetaParamVectorSize]{ 0.0 };
	double* afterThetaVector = new double[this->thetaParamVectorSize]{ 0.0 };

	// 迭代梯度下降
	while (true)
	{
		printf("[LogisticRegressionAlgorithm::train] ");
		bool breakflag = true;
		for (size_t i = 0; i < this->thetaParamVectorSize; i++)
		{
			beforeThetaVector[i] = this->thetaParamVector[i];
		}

		this->GradientBoostAlgorithm(data);

		for (size_t i = 0; i < this->thetaParamVectorSize; i++)
		{
			afterThetaVector[i] = this->thetaParamVector[i];
			printf("theta[%02d] = %5.5f,	", i, afterThetaVector[i]);
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
