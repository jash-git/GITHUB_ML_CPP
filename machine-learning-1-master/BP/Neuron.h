/*+++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*         ������Ԫ�ṹ���Լ���ṹ��               */        
/*                                                  */
/*                  writed by huqunwei��2015.3.5    */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifndef _NEURON_H_
#define _NEURON_H_

/*��Ԫ �ṹ��*/
struct Neuron
{
	int     m_nInput;         //����ά��
	double* m_pWeights;       //Ȩ��

	double  m_dActivation;    //���ֵ
	double  m_dDelta;         //���ж�

	void Init(int nInput)
	{
		m_nInput = nInput + 1;
		m_pWeights = new double[m_nInput];
		m_dActivation = 0;
		m_dDelta = 0;
	}

	~Neuron()
	{
		delete []  m_pWeights;
	}
};


struct NeuronLayer
{
	int     m_nNeuron;        //��Ԫ����
	Neuron* m_pNeurons;  // ��Ԫ   

	NeuronLayer(int nNeuron, int nInputsPerNeuron)
	{
		m_nNeuron = nNeuron;
		m_pNeurons = new Neuron[m_nNeuron];

		for(int i = 0; i < nNeuron; ++i)
		{
			m_pNeurons[i].Init(nInputsPerNeuron);
		}

	}
	~NeuronLayer()
	{
		delete [] m_pNeurons;
	}
};


#endif // Neuron.h
