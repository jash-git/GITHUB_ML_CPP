/***************************************************************************
Module Name:
	KMeans

History:
	2003/10/16	Fei Wang
	2013 luxiaoxun
    modify by  huqunwei, 2015 
***************************************************************************/

//#pragma once
#ifndef K_MEANS_H
#define K_MEANS_H
#include <fstream>

class KMeans
{
public:
	enum InitMode
	{
		InitRandom,
		InitManual,
		InitUniform,
	}; //�������ĳ�ʼ��ģʽ

	KMeans(int dimNum = 1, int clusterNum = 1);  // constructor
	~KMeans();  // destructor

	void SetMean(int i, const double* u){ memcpy(m_means[i], u, sizeof(double) * m_dimNum); } // ���þ�������
	void SetInitMode(int i)				{ m_initMode = i; }   // ���ó�ʼ��ģʽ
	void SetMaxIterNum(int i)			{ m_maxIterNum = i; } // ��������
	void SetEndError(double f)			{ m_endError = f; }   

	double* GetMean(int i)	{ return m_means[i]; }  
	int GetInitMode()		{ return m_initMode; }
	int GetMaxIterNum()		{ return m_maxIterNum; }
	double GetEndError()	{ return m_endError; }


	/*	SampleFile: <size><dim><data>...
		LabelFile:	<size><label>...
	*/
	void Cluster(const char* sampleFileName, const char* labelFileName); // cluster
	void Init(std::ifstream& sampleFile);
	void Init(double *data, int N); 
	void Cluster(double *data, int N, int *Label);  // cluster
	friend std::ostream& operator<<(std::ostream& out, KMeans& kmeans);

private: 
	int       m_dimNum;           //dimension
	int       m_clusterNum;       //����������Ŀ
	double**  m_means;       //��������
	 
	int       m_initMode;         // �������ĳ�ʼ��ģʽ
	int       m_maxIterNum;		// The stopping criterion regarding the number of iterations
	double    m_endError;		// The stopping criterion regarding the error

	double GetLabel(const double* x, int* label); // ��ȡ�������ı�ǩ
	double CalcDistance(const double* x, const double* u, int dimNum); // ����ŷʽ����
};


#endif //k-means.h
