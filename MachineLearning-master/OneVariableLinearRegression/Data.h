#pragma once
class Data
{
public:
	Data(size_t trainDataVectorSize, size_t thetaParamVectorSize = 2);
	virtual ~Data();
	void printData();

public:
	double* thetaParamVector;		// ����
	size_t thetaParamVectorSize;	// ��������
	double* trainDataVector;		// ѵ����
	size_t trainDataVectorSize;		// ѵ����ά�ȴ�С
	double* realValueVector;		// ��ʵֵ��
	size_t realValueVectorSize;		// ��ʵֵά�ȴ�С
};

