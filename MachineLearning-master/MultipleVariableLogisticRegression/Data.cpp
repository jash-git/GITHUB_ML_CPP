#include "Data.h"
#include <stdio.h>



Data::Data(size_t trainDataMatrixColSize):trainDataMatrixColSize(trainDataMatrixColSize)
{
	this->realValueVector = nullptr;
	this->realValueVectorSize = 0;
	this->trainDataMatrix = nullptr;
	this->trainDataMatrixRowSize = 0;
}


Data::~Data()
{
	delete[] this->realValueVector;
	for (size_t i = 0; i < this->trainDataMatrixRowSize; i++)
	{
		delete[] this->trainDataMatrix[i];
	}

	delete[] this->trainDataMatrix;
}

void Data::readData(const char* fileName, size_t row)
{
	this->trainDataMatrixRowSize = row;
	this->realValueVector = new int[row]{ 0 };
	this->trainDataMatrix = new double* [row];

	FILE* fpr;
	fopen_s(&fpr, fileName, "r");
	double x1, x2;
	int y;
	int i = 0;
	while (fscanf_s(fpr, "%lf	%lf	%d", &x1, &x2, &y) != EOF)
	{
		this->trainDataMatrix[i] = new double[this->trainDataMatrixColSize]{ 0.0 };
		this->trainDataMatrix[i][0] = 1.0;
		this->trainDataMatrix[i][1] = x1;
		this->trainDataMatrix[i][2] = x2;
		this->realValueVector[i] = y;
		i++;
	}
	this->realValueVectorSize = i;
	fclose(fpr);
}
void Data::printData()
{
	for (size_t i = 0; i < this->trainDataMatrixRowSize; i++)
	{
		printf("[Data::printData] ");
		for (size_t j = 0; j < this->trainDataMatrixColSize; j++)
		{
			printf("x[%02d][%02d] = %5.5f,	", i, j, this->trainDataMatrix[i][j]);
		}
		printf("y[%02d] = %d \n", i, this->realValueVector[i]);
	}
}
