#include "NeuralNet.h"
#include <assert.h>

/* ���캯�� */
CNeuralNet::CNeuralNet(int nInput, int nOutput, int nNeuronsPerLyr, int nHiddenLayer)
{
	assert(nInput>0 && nOutput>0 && nNeuronsPerLyr >0 &&nHiddenLayer>0 );
	m_nInput = nInput;   // ����ά��
	m_nOutput = nOutput; // ���ά��
	m_nNeuronsPerLyr = nNeuronsPerLyr; // ���㵥Ԫ��
	if (nHiddenLayer != 1) // ��֧����������
		m_nHiddenLayer = 1;
	else
		m_nHiddenLayer = nHiddenLayer;

	m_pHiddenLyr = NULL;
	m_pOutLyr    = NULL;
	CreateNetWork(); // ��������
	InitializeNetwork();// ��ʼ���������
}

CNeuralNet::~CNeuralNet()
{
	delete m_pHiddenLyr;
	delete m_pOutLyr;
}

/* ��������*/
void CNeuralNet::CreateNetWork()
{
	m_pHiddenLyr = new NeuronLayer(m_nNeuronsPerLyr, m_nInput);
	m_pOutLyr    = new NeuronLayer(m_nOutput, m_nNeuronsPerLyr);
}

/* ��ʼ��Ȩ�� 0 ~ 0.05*/
void CNeuralNet::InitializeNetwork()
{
	for(int i = 0; i < m_pHiddenLyr->m_nNeuron; ++i)
	{
		for(int j = 0; j < m_pHiddenLyr->m_pNeurons[i].m_nInput; ++j)
			m_pHiddenLyr->m_pNeurons[i].m_pWeights[j] = uniform(0, 0.05);
	}

	for(int i = 0;i < m_pOutLyr->m_nNeuron; ++i)
	{
		for(int j = 0; j < m_pOutLyr->m_pNeurons[i].m_nInput; ++j)
			m_pOutLyr->m_pNeurons[i].m_pWeights[j] = uniform(0, 0.05);
	}
}

/*  ǰ�򴫲�  */ 
bool CNeuralNet::CalculateOutput(vector<double> Input, vector<double>& output)
{
	int i,j;
	double net;  // ������

	/* ����������� */
	for( i = 0;i < m_pHiddenLyr->m_nNeuron; ++i)
	{
		net = 0;
		for( j = 0; j < m_pHiddenLyr->m_pNeurons[i].m_nInput - 1; ++j)
		{
			net += m_pHiddenLyr->m_pNeurons[i].m_pWeights[j]*Input[j];
		}
		net += m_pHiddenLyr->m_pNeurons[i].m_pWeights[j]*BIAS;
		m_pHiddenLyr->m_pNeurons[i].m_dActivation = Sigmoid(net);
	}

	/* ��������� ���*/
	for(i = 0; i < m_pOutLyr->m_nNeuron; ++i )
	{
		net = 0;
		for( j = 0; j < m_pOutLyr->m_pNeurons[i].m_nInput -1; ++j)
		{
			net += m_pOutLyr->m_pNeurons[i].m_pWeights[j]
			*m_pHiddenLyr->m_pNeurons[j].m_dActivation;
		}
		net += m_pOutLyr->m_pNeurons[i].m_pWeights[j]*BIAS;
		m_pOutLyr->m_pNeurons[i].m_dActivation = Sigmoid( net );
		output.push_back(m_pOutLyr->m_pNeurons[i].m_dActivation);
	}
	return true;
}

/* һ���غϣ�epoch�������������μ���ѵ������*/
bool CNeuralNet::TrainEpoch(vector<iovector>& SetIn, vector<iovector>& SetOut, double LearnRate )
{
	int i , j , k;
	double  WeightUpdate;
	double err;

	m_dErrorSum = 0;
	for( i = 0; i < SetIn.size(); ++i)
	{
		iovector vecOutputs;
		if( !CalculateOutput( SetIn[i], vecOutputs))
			return false;
		/* ����������Ȩֵ */
		for( j = 0; j < m_pOutLyr->m_nNeuron; ++j)
		{
			    err = ((double)SetOut[i][j] - vecOutputs[j] )*vecOutputs[j]*(1 - vecOutputs[j]);
			    m_pOutLyr->m_pNeurons[j].m_dDelta = err;

			    m_dErrorSum += ((double)SetOut[i][j] - vecOutputs[j])*((double)SetOut[i][j] - vecOutputs[j]);

			for(k = 0; k < m_pOutLyr->m_pNeurons[j].m_nInput -1; ++k)
			{
				   WeightUpdate = err * LearnRate * m_pHiddenLyr->m_pNeurons[k].m_dActivation;
                   m_pOutLyr->m_pNeurons[j].m_pWeights[k] += WeightUpdate;
			}
			/*  ���������bias��Ȩֵ*/
			WeightUpdate = err * LearnRate * BIAS;
			m_pOutLyr->m_pNeurons[j].m_pWeights[k] += WeightUpdate;
		}
		/* ���������Ȩֵ*/
		for( j = 0; j < m_pHiddenLyr->m_nNeuron; ++j)
		{
			err = 0;
			for(int k = 0; k <m_pOutLyr->m_nNeuron; ++k)
			{
				err += m_pOutLyr->m_pNeurons[k].m_dDelta*m_pOutLyr->m_pNeurons[k].m_pWeights[j];
			}
			err *= m_pHiddenLyr->m_pNeurons[j].m_dActivation *(1 - m_pHiddenLyr->m_pNeurons[j].m_dActivation );
			m_pHiddenLyr->m_pNeurons[j].m_dDelta = err;

			for( k = 0; k < m_pHiddenLyr->m_pNeurons[j].m_nInput - 1; ++k)
			{
				WeightUpdate = err * LearnRate *SetIn[i][k];
				m_pHiddenLyr->m_pNeurons[j].m_pWeights[k] += WeightUpdate;
			}
			/* ��������biasȨֵ*/
			WeightUpdate = err * LearnRate *BIAS;
			m_pHiddenLyr->m_pNeurons[j].m_pWeights[k] += WeightUpdate;
		}

	}
	return true;
}