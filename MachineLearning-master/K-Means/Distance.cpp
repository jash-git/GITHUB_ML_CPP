#include "Distance.h"
#include <math.h>


// ŷ�Ͼ���
double Distance::getEuclideanDistance(double* tuple1, double* tuple2, size_t tupleSize)
{
	double sum = 0.0;
	for (size_t i = 0; i < tupleSize; i++)
	{
		double var = tuple1[i] - tuple2[i];
		sum += var * var;
	}
	return sqrt(sum);
}

// �����پ���
double Distance::getManhattanDistance(double* tuple1, double* tuple2, size_t tupleSize)
{
	double sum = 0.0;
	for (size_t i = 0; i < tupleSize; i++)
	{
		double var = tuple1[i] - tuple2[i];
		sum += fabs(var);
	}
	return sum;
}

// �б�ѩ�����
double Distance::getChebyshevDistance(double* tuple1, double* tuple2, size_t tupleSize)
{
	double max = 0.0;
	for (size_t i = 0; i < tupleSize; i++)
	{
		double var = fabs(tuple1[i] - tuple2[i]);
		if (var > max)
		{
			max = var;
		}
	}
	return max;
}
// ���Ҿ���
double Distance::getCosineDistance(double* tuple1, double* tuple2)
{
	double x1 = tuple1[0];
	double y1 = tuple1[1];
	double x2 = tuple2[0];
	double y2 = tuple2[1];
	return (x1 * x2 + y1 * y2) / sqrt( ((x1 * x1) + (y1 * y1)) * ((x2 * x2) + (y2 * y2)) );
}

// �����������
double Distance::getSphericalDistance(double* tuple1, double* tuple2) {
#define PI (3.14159265358979323846)
	// γ��
	double lat1 = (PI / 180) * tuple1[1];
	double lat2 = (PI / 180) * tuple2[1];

	// ����
	double lng1 = (PI / 180) * tuple1[0];
	double lng2 = (PI / 180) * tuple2[0];

	// ����뾶
	double R = 6370996.81; //6370.99681D
	//�����������빫ʽ m
	double distance = acos( sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lng2 - lng1) ) * R;
	return distance;
}