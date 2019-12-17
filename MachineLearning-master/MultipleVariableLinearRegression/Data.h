#pragma once
class Data
{
public:
	Data(size_t trainDataMatrixRowSize, size_t thetaParamVectorSize);
	virtual ~Data();

	void printData();

public:
	double* thetaParamVector;			// 参数
	size_t thetaParamVectorSize;		// 参数数量
	double** trainDataMatrix;			// 训练集
	size_t trainDataMatrixRowSize;		// 训练集维度大小
	size_t trainDataMatrixColSize;		// 训练集维度大小
	double* realValueVector;			// 真实值集
	size_t realValueVectorSize;			// 真实值维度大小
};

