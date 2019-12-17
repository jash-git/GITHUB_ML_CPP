#include "Data.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_RANGE 10

Data::Data(size_t trainDataVectorSize):
	trainDataVectorSize(trainDataVectorSize), realValueVectorSize(trainDataVectorSize)
{
	this->trainDataVector = new double[this->trainDataVectorSize]{ 0.0 };
	this->realValueVector = new double[this->realValueVectorSize]{ 0.0 };

	for (size_t i = 0; i < trainDataVectorSize; i++)
	{
		double theta0 = (double)(rand() % MAX_RANGE) + (rand() % RAND_MAX) / (RAND_MAX * 1.0);
		double theta1 = (double)(rand() % MAX_RANGE) + (rand() % RAND_MAX) / (RAND_MAX * 1.0);
		double x = (double)(rand() % 150) + (rand() % RAND_MAX) / (RAND_MAX * 1.0);
		double y = theta0 * 1.0 + theta1 * x;
		this->trainDataVector[i] = x;
		this->realValueVector[i] = y;
	}
}


Data::~Data()
{
	delete[] this->trainDataVector;
	delete[] this->realValueVector;
}

void Data::printData()
{
	for (size_t i = 0; i < this->trainDataVectorSize; i++)
	{
		printf("[Data::printData] x = %5.5f, y = %5.5f\n", this->trainDataVector[i], this->realValueVector[i]);
	}
}

double Data::getMin()
{
	double min = this->trainDataVector[0];
	for (size_t i = 0; i < this->trainDataVectorSize; i++)
	{
		if (this->trainDataVector[i] < min && fabs(this->trainDataVector[i] - min) > 1e-6)
		{
			min = this->trainDataVector[i];
		}
	}
	return min;
}
double Data::getMax()
{
	double max = this->trainDataVector[0];
	for (size_t i = 0; i < this->trainDataVectorSize; i++)
	{
		if (this->trainDataVector[i] > max && fabs(this->trainDataVector[i] - max) > 1e-6)
		{
			max = this->trainDataVector[i];
		}
	}
	return max;
}
