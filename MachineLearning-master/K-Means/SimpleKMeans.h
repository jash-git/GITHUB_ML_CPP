#pragma once
#include <vector>

using namespace std;

class SimpleKMeans
{
public:
	SimpleKMeans(size_t k, size_t featureNum);
	virtual ~SimpleKMeans();
	double getLabel(double* sample, int& label);
	void run(double** data, int row);

private:
	//计算两个元组间的欧几里距离  
	double getDistance(double* tuple1, double* tuple2);
	void Init(double** data, int row);

private:
	size_t m_featureNum;		// 特征数量
	size_t m_k;					// 聚类个数
	double** mlp_means;			// 聚类中心
	size_t m_maxIterNum;		// 迭代次数
	double m_endError;			// 误差
};

