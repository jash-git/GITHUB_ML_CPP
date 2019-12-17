//----------------------------------------------------------------------
//                             KNN������
//                    ��װCKNN�࣬���ڷ������
//
//----------------------------------------------------------------------
//                                                       writed by huqunwei��2015.3.2                                                
//----------------------------------------------------------------------

#ifndef _CKNN_H_
#define _CKNN_H_

#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<cmath>
#include<algorithm>


#define ATTR_NUM    4         //����ά�� 

using namespace std;

//�ṹ��
struct sample 
{
	string classLabel;                  //���
	double features[ATTR_NUM]; //��������
};

// sort����   �ȽϺ���
struct CmpByValue
{
	bool operator()  (const pair<int ,double>& lhs, const pair<int ,double>& rhs)
	{
		return lhs.second < rhs.second;
	}
};

//���CKNN��
class CKNN
{
public:
	CKNN(int k); // ���캯��

	~CKNN();     // ��������

	int Load(const char* SampleSet); 

	double  Distance(struct sample v1, struct sample v2); 

	void get_all_distance(struct sample TestSample );

    string  get_max_freq_label(); 

	void  get_accuracy();                

public:
	vector<struct sample > TrainSet;              //ѵ������
	vector<struct sample > TestSet;               //���Լ���
	int k;                                                         //K���ڲ���
	map<int, double> map_index_dis;            
    map<string, int> map_label_freq;           
	vector<pair<int ,double>> vec_index_dis; 
};

#endif