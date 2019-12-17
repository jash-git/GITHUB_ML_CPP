#pragma once
class Data
{
public:
	Data(size_t trainDataMatrixColSize);
	virtual ~Data();
	void readData(const char* fileName, size_t row);
	void printData();

public:
	double** trainDataMatrix;			// 训练集
	size_t trainDataMatrixRowSize;		// 训练集维度大小
	size_t trainDataMatrixColSize;		// 训练集维度大小
	int* realValueVector;				// 真实值集
	size_t realValueVectorSize;			// 真实值维度大小
};

