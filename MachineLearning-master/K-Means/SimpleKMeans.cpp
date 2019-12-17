#include<assert.h>
#include <math.h>
#include <time.h>
#include<windows.h>
#include "Distance.h"
#include "SimpleKMeans.h"


SimpleKMeans::SimpleKMeans(size_t k, size_t featureNum):
	m_k(k), m_featureNum(featureNum)
{
	mlp_means = new double* [m_k] {nullptr};
	for (int i = 0; i < m_k; i++)
	{
		mlp_means[i] = new double[m_featureNum];
		memset(mlp_means[i], 0, sizeof(double) * m_featureNum);
	}

	m_maxIterNum = 200;
	m_endError = 0.001;
}

SimpleKMeans::~SimpleKMeans()
{
	for (int i = 0; i < m_k; i++)
	{
		delete[] mlp_means[i];
	}
	delete[] mlp_means;
}

//计算两个元组间的欧几里距离  
double SimpleKMeans::getDistance(double* tuple1, double* tuple2)
{
	return Distance::getEuclideanDistance(tuple1, tuple2, m_featureNum);
}

//根据聚类中心，求当前特征元祖的最近聚类中心
double SimpleKMeans::getLabel(double* sample, int& label)
{
	double distance = getDistance(sample, mlp_means[0]);
	label = 0;
	for (int i = 1; i < m_k; i++)
	{
		double temp = getDistance(sample, mlp_means[i]);
		if (temp < distance)
		{
			distance = temp;
			//标示属于哪一个簇
			label = i;
		}
	}
	return distance;
}

//求当前簇的均值
//double* SimpleKMeans::getMeans(vector<double*> cluster)
//{
//	double* sum = new double[m_featureNum] {0.0};
//	size_t size = cluster.size();
//	for (size_t i = 0; i < size; i++)
//	{
//		double* tmp = cluster[i];
//		for (size_t j = 0; j < m_featureNum; j++)
//		{
//			sum[i] += tmp[j];
//		}
//	}
//	for (size_t i = 0; i < m_featureNum; i++)
//	{
//		sum[i] /= size;
//	}
//	return sum;
//}

//获得给定簇集的平均误差  
//double SimpleKMeans::getVar()
//{
//	double var = 0;
//	double count = 0;
//	for (int i = 0; i < m_k; i++)
//	{
//		vector<double*> cluster = mp_clusters->at(i);
//		for (int j = 0; j < cluster.size(); j++)
//		{
//			count++;
//			var += getDistance(cluster[j], mlp_means[i]);
//		}
//	}
//	return var / count;
//}

void SimpleKMeans::Init(double** data, int row)
{
	int size = row;
	int inteval = size / m_k;
	double* sample = new double[m_featureNum];
	srand((unsigned)time(NULL));

	// 随机初始化
	for (int i = 0; i < m_k; i++)
	{
		int select = rand() % inteval;
		for (size_t j = 0; j < m_featureNum; j++)
		{
			sample[j] = data[i * inteval + select][j];
		}
		memcpy(mlp_means[i], sample, sizeof(double) * m_featureNum);
	}

	// 标准初始化
	//for (int i = 0; i < m_k; i++)
	//{
	//	int select = i * size / m_k;
	//	for (int j = 0; j < m_featureNum; j++)
	//	{
	//		sample[j] = data[select * m_featureNum][j];
	//	}
	//	memcpy(mlp_means[i], sample, sizeof(double) * m_featureNum);
	//}
	delete[] sample;
}

void SimpleKMeans::run(double ** data, int row)
{
	assert(data);
	assert(row > 0);

	Init(data, row);

	int label = -1;		// cluster index 每个特征向量被分配的标签 标签为聚类中心/簇索引
	double iterNum = 0; // 迭代次数计数器
	double lastCost = 0; // 
	double newCost = 0; // 迭代代价梯度
	int unchanged = 0;
	bool loop = true;
	int* counts = new int[m_k]; // 统计每个聚类中心/簇的标签数量

	double** next_means = new double* [m_k];	// New model for reestimation 临时存储新的族类中心
	for (int i = 0; i < m_k; i++)
	{
		next_means[i] = new double[m_featureNum];
	}

	while (loop)
	{
		//clean buffer for classification
		memset(counts, 0, sizeof(int) * m_k);
		for (int i = 0; i < m_k; i++)
		{
			//清零每个临时存储新的族类中心
			memset(next_means[i], 0, sizeof(double) * m_featureNum);
		}
		lastCost = newCost;
		newCost = 0;

		// Classification
		for (int i = 0; i < row; i++)
		{
			newCost += getLabel(data[i], label);
			counts[label]++;
			for (int j = 0; j < m_featureNum; j++)
			{
				next_means[label][j] += data[i][j];
			}
		}
		newCost /= row;

		//for (int i = 0; i < data_num; ++i)
		//{
		//	lable = this->getLabel(data[i]);
		//	this->mp_clusters->at(lable).push_back(data[i]);
		//}

		// 在估计 即更新每个簇的中心点  
		for (int i = 0; i < m_k; i++)
		{
			if (counts[i] > 0)
			{
				for (int j = 0; j < m_featureNum; j++)
				{
					// 求每个聚类中心每个特征的均值
					next_means[i][j] /= counts[i];
				}
				memcpy(mlp_means[i], next_means[i], sizeof(double) * m_featureNum);
			}
		}

		for (size_t i = 0; i < row; i++)
		{
			int label = -1;
			getLabel(data[i], label);
			printf("|%10d|", i);
			for (size_t k = 0; k < m_featureNum; k++)
			{
				printf("%15.5lf|", data[i][k]);
			}
			printf(" cluster %d|%15.5lf|%15.5lf |\n", label + 1, mlp_means[label][0], mlp_means[label][1]);
		}
		printf("------------------------------------------------------------------------------------------\n");

		// Terminal conditions  算法终终止条件
		iterNum++;
		if (fabs(lastCost - newCost) < m_endError * lastCost)
		{
			unchanged++;
		}
		if (iterNum >= m_maxIterNum || unchanged >= 3)
		{
			loop = false;
		}
		Sleep(10);
	}
	
	delete[] counts;
	for (int i = 0; i < m_k; i++)
	{
		delete[] next_means[i];
	}
	delete[] next_means;
}