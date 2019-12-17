//main.cpp
#include "include/Ann.h"


int main()
{
	const int hidnodes = 8; //�������ز�Ľ����
	const int inNodes = 10;   //���������
	const int outNodes = 5;  //���������

	const int trainClass = 5; //5�����
	const int numPerClass = 30;  //ÿ�����30��������

	int sampleN = trainClass * numPerClass;     //ÿ��ѵ��������Ϊ30��5������ܵ�������Ϊ150
	float **trainMat = new float*[sampleN];                         //����ѵ������
	for (int k = 0; k < trainClass; ++k) {
		for (int i = k * numPerClass; i < (k + 1) * numPerClass; ++i) {
			trainMat[i] = new float[inNodes];
			for (int j = 0; j < inNodes; ++j) {
				trainMat[i][j] = rand() % 1000 / 10000.0 + 0.1*(2 * k + 1);

			}
		}
	}

	int **labelMat = new int*[sampleN]; //���ɱ�ǩ����
	for (int k = 0; k < trainClass; ++k) {
		for (int i = k * numPerClass; i < (k + 1) * numPerClass; ++i) {
			labelMat[i] = new int[outNodes];
			for (int j = 0; j < trainClass; ++j) {
				if (j == k)
					labelMat[i][j] = 1;
				else
					labelMat[i][j] = 0;
			}

		}
	}

	Ann ann_classify(sampleN, inNodes, outNodes, hidnodes, 0.12);  //�����Ϊ10����㣬�����5����㣬�������ز�
	ann_classify.train(sampleN, trainMat, labelMat);


	for (int i = 0; i < 30; ++i) {
		ann_classify.predict(trainMat[i + 120], NULL);
		std::cout << std::endl;
	}


	//�ͷ��ڴ�
	for (int i = 0; i < sampleN; ++i)
		delete[] trainMat[i];
	delete[] trainMat;

	for (int i = 0; i < sampleN; ++i)
		delete[] labelMat[i];
	delete[] labelMat;

	system("pause");
	return 0;
}