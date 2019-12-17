/*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                   BP������                            */
/*                                                      */
/*                      writed by huqunwei��2015.3.5    */
/*++++++++++++++++++++++++++++++++++++++++*/
#ifndef _NEURALNET_H_
#define _NEURALNET_H_

#include <vector>
#include <cmath>
#include "Neuron.h"


using namespace std;

#define BIAS  1 
typedef vector<double> iovector;

/* ��ʼ��Ȩ��0~0.05 */
inline double uniform(double _min, double _max)
{
	return rand()/(RAND_MAX + 1.0)*( _max - _min ) + _min;
}


class CNeuralNet 
{
private:
	int           m_nInput;        // ����ά��
	int           m_nOutput;       // ���ά��
	int           m_nNeuronsPerLyr;// ������Ԫ����
	int           m_nHiddenLayer;  // �������


	double        m_dErrorSum;    // ���

	NeuronLayer*  m_pHiddenLyr;   // ����
	NeuronLayer*  m_pOutLyr;      // �����

public:
	CNeuralNet(int nInput, int nOutput, int nNeuronsPerLyr, int nHiddenLayer = 1); // ���캯��
	~CNeuralNet();                                                                                              // ��������

	bool CalculateOutput(vector<double> Input, vector<double>& output);      //ǰ�򴫲�

	bool TrainEpoch(vector<iovector>& SetIn, vector<iovector>& SetOut, double LearnRate ); // ���򴫲����

	double GetErrorSum(){ return m_dErrorSum;}  // ���

private:
	void CreateNetWork();

	void InitializeNetwork();

	double Sigmoid(double net)
	{
		return 1.0/(1 + exp(-net));
	}

};


#endif  // NeuralNet.h