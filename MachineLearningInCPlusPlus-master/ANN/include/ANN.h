/*******************************************************************
*����־�� ����ѧϰ��C++����
*
* htfeng
* 2018.10.15
*
* �����£�������
* ����һ�����������
*******************************************************************/
#ifndef _ANN_H_
#define _ANN_H_

#include<assert.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<Windows.h>
#include<ctime>

class Ann {
public:
	explicit Ann(int _SampleN, int nNIL, int nNOL, const int nNHL, float _sR = 0);
	~Ann();
	void train(int _sampleNum, float** _trainMat, int** _labelMat);
	void predict(float* in, float* proba);

private:
	int numNodesInputLayer;
	int numNodesOutputLayer;
	int numNodesHiddenLayer;
	int SampleCount;   // �ܵ�ѵ��������
	double ***weights;  // ����Ȩֵ
	double **bias;      // ����ƫ��
	float studyRate;    // ѧϰ��

	double *hidenLayerOutput;     //���ز���������ֵ
	double *outputLayerOutput;     //�������������ֵ

	double ***allDeltaBias;        //����������ƫ�ø�����
	double ****allDeltaWeights;    //����������Ȩֵ������
	double **outputMat;            //�����������������
	
	void train_vec(const float* _trainVec, const int* _labelVec, int index);
	double sigmod(double x) { return 1 / (1 + exp(-1 * x)); }
	bool isNotConver(const int _sampleNum, int** _labelMat, double _thresh);

};
#endif // !_ANN_H_
