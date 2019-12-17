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
	//��������Ԫ����ŷ�������  
	double getDistance(double* tuple1, double* tuple2);
	void Init(double** data, int row);

private:
	size_t m_featureNum;		// ��������
	size_t m_k;					// �������
	double** mlp_means;			// ��������
	size_t m_maxIterNum;		// ��������
	double m_endError;			// ���
};

