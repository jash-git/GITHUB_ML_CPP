#pragma once
#include "Data.h"

class LogisticRegressionAlgorithm
{
public:
	LogisticRegressionAlgorithm(size_t thetaParamVectorSize, double thresholdValue = 0.000001, double learningRate = 0.0001);
	virtual ~LogisticRegressionAlgorithm();

	void train(const Data& data);						// 训练
	double predict(double* paramVector) const;				// 预测

private:
	void GradientBoostAlgorithm(const Data& data);	// 梯度提升算法
	double sigmoid(double x) const;	// 逻辑函数

public:
	double* thetaParamVector;		// 参数
	size_t thetaParamVectorSize;	// 参数数量
	double learningRate;			// 学习速率
	double thresholdValue;			// 训练停止阈值
};

