#pragma once
class Data
{
public:
	Data(size_t trainDataVectorSize);
	virtual ~Data();
	void printData();
	double getMin();
	double getMax();

public:
	double* trainDataVector;		// ѵ����
	size_t trainDataVectorSize;		// ѵ����ά�ȴ�С
	double* realValueVector;		// ��ʵֵ��
	size_t realValueVectorSize;		// ��ʵֵά�ȴ�С
};

