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
	double* trainDataVector;		// 训练集
	size_t trainDataVectorSize;		// 训练集维度大小
	double* realValueVector;		// 真实值集
	size_t realValueVectorSize;		// 真实值维度大小
};

