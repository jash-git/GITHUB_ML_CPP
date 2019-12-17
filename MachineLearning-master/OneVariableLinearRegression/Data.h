#pragma once
class Data
{
public:
	Data(size_t trainDataVectorSize, size_t thetaParamVectorSize = 2);
	virtual ~Data();
	void printData();

public:
	double* thetaParamVector;		// 参数
	size_t thetaParamVectorSize;	// 参数数量
	double* trainDataVector;		// 训练集
	size_t trainDataVectorSize;		// 训练集维度大小
	double* realValueVector;		// 真实值集
	size_t realValueVectorSize;		// 真实值维度大小
};

