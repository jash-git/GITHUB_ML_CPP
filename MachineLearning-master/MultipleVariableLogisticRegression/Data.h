#pragma once
class Data
{
public:
	Data(size_t trainDataMatrixColSize);
	virtual ~Data();
	void readData(const char* fileName, size_t row);
	void printData();

public:
	double** trainDataMatrix;			// ѵ����
	size_t trainDataMatrixRowSize;		// ѵ����ά�ȴ�С
	size_t trainDataMatrixColSize;		// ѵ����ά�ȴ�С
	int* realValueVector;				// ��ʵֵ��
	size_t realValueVectorSize;			// ��ʵֵά�ȴ�С
};

