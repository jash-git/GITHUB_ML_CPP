#pragma once
#include "Data.h"

class LogisticRegressionAlgorithm
{
public:
	LogisticRegressionAlgorithm(size_t thetaParamVectorSize, double thresholdValue = 0.000001, double learningRate = 0.0001);
	virtual ~LogisticRegressionAlgorithm();

	void train(const Data& data);						// ѵ��
	double predict(double* paramVector) const;				// Ԥ��

private:
	void GradientBoostAlgorithm(const Data& data);	// �ݶ������㷨
	double sigmoid(double x) const;	// �߼�����

public:
	double* thetaParamVector;		// ����
	size_t thetaParamVectorSize;	// ��������
	double learningRate;			// ѧϰ����
	double thresholdValue;			// ѵ��ֹͣ��ֵ
};

