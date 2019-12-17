#pragma once
class Data
{
public:
	Data(size_t trainDataMatrixRowSize, size_t thetaParamVectorSize);
	virtual ~Data();

	void printData();

public:
	double* thetaParamVector;			// ����
	size_t thetaParamVectorSize;		// ��������
	double** trainDataMatrix;			// ѵ����
	size_t trainDataMatrixRowSize;		// ѵ����ά�ȴ�С
	size_t trainDataMatrixColSize;		// ѵ����ά�ȴ�С
	double* realValueVector;			// ��ʵֵ��
	size_t realValueVectorSize;			// ��ʵֵά�ȴ�С
};

