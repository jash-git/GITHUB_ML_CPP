
#include "../../../Src/LDecisionTree.h"
#include "../../../Src/LCSVIo.h"
#include "../../../Src/LPreProcess.h"

#include <cstdio>
#include <cstdlib>


/// @brief ��ӡ����
void MatrixPrint(IN const LDataMatrix& dataMatrix)
{
    printf("Matrix Row: %u  Col: %u\n", dataMatrix.RowLen, dataMatrix.ColumnLen);
    for (unsigned int i = 0; i < dataMatrix.RowLen; i++)
    {
        for (unsigned int j = 0; j < dataMatrix.ColumnLen; j++)
        {
            printf("%.2f  ", dataMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    // �������ݼ�
    LCSVParser csvParser(L"../../../DataSet/iris.csv");
    csvParser.SetSkipHeader(true);
    LDataMatrix dataMatrix;
    csvParser.LoadAllData(dataMatrix);

    // �������ݼ�
    DoubleMatrixShuffle(0, dataMatrix);

    // �����ݼ����Ϊѵ�����Ͳ��Լ�, ���Լ�ռ�ܼ��ϵ�20%
    unsigned int testSize = (unsigned int)(dataMatrix.RowLen * 0.2);
    LDTMatrix testData;
    LDTMatrix trainData;
    dataMatrix.SplitRow(testSize, testData, trainData);

    // ��ѵ�������Ϊѵ���������Ϻͱ�ǩ��
    LDTMatrix trainXMatrix;
    LDTMatrix trainYVector;
    trainData.SplitCloumn(trainData.ColumnLen - 1, trainXMatrix, trainYVector);

    // �����Լ����Ϊ�����������Ϻͱ�ǩ��
    LDTMatrix testXMatrix;
    LDTMatrix testYVector;
    testData.SplitCloumn(testData.ColumnLen - 1, testXMatrix, testYVector);


    // ��������ֵ�ֲ�����
    double featureN[4] =
    {
        DT_FEATURE_CONTINUUM,
        DT_FEATURE_CONTINUUM,
        DT_FEATURE_CONTINUUM,
        DT_FEATURE_CONTINUUM
    };
    LDTMatrix nVector(1, 4, featureN);

    // ʹ��ѵ����ѵ��ģ��
    LDecisionTreeClassifier clf;
    clf.TrainModel(trainXMatrix, nVector, trainYVector);
    clf.PrintTree();

    // ʹ�ò��Լ�����ģ�͵÷�
    double score = clf.Score(testXMatrix, testYVector);

    printf("Decision Tree Classifier Score: %.2f\n", score);

    system("pause");

    return 0;
}