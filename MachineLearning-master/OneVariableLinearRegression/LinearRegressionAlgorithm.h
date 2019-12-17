#pragma once

#include "Data.h"


class LinearRegressionAlgorithm
{
public:
	LinearRegressionAlgorithm(double thresholdValue = 0.00000001, double learningRate = 0.0001, size_t thetaParamVectorSize = 2);
	virtual ~LinearRegressionAlgorithm();
	void train(const Data& data);						// ѵ��
	double predict(double param);						// Ԥ��

private:
	void GradientDescentAlgorithm(const Data& data);	// �ݶ��½��㷨

public:
	double* thetaParamVector;		// ����
	size_t thetaParamVectorSize;	// ��������
	double learningRate;			// ѧϰ����
	double thresholdValue;			// ѵ��ֹͣ��ֵ
};

