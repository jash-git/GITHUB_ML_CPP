#pragma once

#include "Data.h"


class LinearRegressionAlgorithm
{
public:
	LinearRegressionAlgorithm(double thresholdValue = 0.00000001, double learningRate = 0.0001, size_t thetaParamVectorSize = 2);
	virtual ~LinearRegressionAlgorithm();
	void train(const Data& data);						// 训练
	double predict(double param);						// 预测

private:
	void GradientDescentAlgorithm(const Data& data);	// 梯度下降算法

public:
	double* thetaParamVector;		// 参数
	size_t thetaParamVectorSize;	// 参数数量
	double learningRate;			// 学习速率
	double thresholdValue;			// 训练停止阈值
};

