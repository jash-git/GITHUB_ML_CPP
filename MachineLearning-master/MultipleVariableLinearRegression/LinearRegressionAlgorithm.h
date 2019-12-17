#pragma once
#include "Data.h"

class LinearRegressionAlgorithm
{
public:
	LinearRegressionAlgorithm(size_t thetaParamVectorSize, double thresholdValue = 0.00000001, double learningRate = 0.0001);
	virtual ~LinearRegressionAlgorithm();

	void train(const Data& data);						// ѵ��
	double predict(double *paramVector);				// Ԥ��

private:
	void GradientDescentAlgorithm(const Data& data);	// �ݶ��½��㷨

public:
	double* thetaParamVector;		// ����
	size_t thetaParamVectorSize;	// ��������
	double learningRate;			// ѧϰ����
	double thresholdValue;			// ѵ��ֹͣ��ֵ
};

