#include "Data.h"
#include <stdlib.h>
#include <stdio.h>


#define MAX_RANGE 50

Data::Data(size_t trainDataMatrixRowSize, size_t thetaParamVectorSize):
	trainDataMatrixRowSize(trainDataMatrixRowSize),
	trainDataMatrixColSize(thetaParamVectorSize),
	thetaParamVectorSize(thetaParamVectorSize),
	realValueVectorSize(trainDataMatrixRowSize)
{
	this->thetaParamVector = new double[this->thetaParamVectorSize]{ 0.0 };
	this->realValueVector = new double[this->realValueVectorSize]{ 0.0 };
	this->trainDataMatrix = new double*[this->trainDataMatrixRowSize];

	for (size_t i = 0; i < this->thetaParamVectorSize; i++)
	{
		this->thetaParamVector[i] = (double)(rand() % MAX_RANGE) + (rand() % RAND_MAX) / (RAND_MAX * 1.0);
	}

	for (size_t i = 0; i < this->trainDataMatrixRowSize; i++)
	{
		this->trainDataMatrix[i] = new double[this->trainDataMatrixColSize]{0.0};
		this->trainDataMatrix[i][0] = 1.0;
		double y = this->thetaParamVector[0] * 1.0;
		for (size_t j = 1; j < this->trainDataMatrixColSize; j++)
		{
			double x = (double)(rand() % MAX_RANGE) + (rand() % RAND_MAX) / (RAND_MAX * 1.0);
			this->trainDataMatrix[i][j] = x;
			y += thetaParamVector[j] * x;
		}
		this->realValueVector[i] = y;
	}
}


Data::~Data()
{
	delete[] this->thetaParamVector;
	delete[] this->realValueVector;
	for (size_t i = 0; i < this->trainDataMatrixRowSize; i++)
	{
		delete[] this->trainDataMatrix[i];
	}

	delete[] this->trainDataMatrix;
}

void Data::printData()
{
	for (size_t i = 0; i < this->trainDataMatrixRowSize; i++)
	{
		printf("[Data::printData] ");
		for (size_t j = 0; j < this->trainDataMatrixColSize; j++)
		{
			printf("x[%d][%d] = %5.5f,  ", i, j, this->trainDataMatrix[i][j]);
		}
		printf("y[%d] = %5.5f \n", i, this->realValueVector[i]);
	}
}
