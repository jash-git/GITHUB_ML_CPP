#pragma once
class Distance
{
public:
	virtual ~Distance(){}
	// ŷ�Ͼ���
	static double getEuclideanDistance(double* tuple1, double* tuple2, size_t tupleSize);
	// �����پ���
	static double getManhattanDistance(double* tuple1, double* tuple2, size_t tupleSize);
	// �б�ѩ�����
	static double getChebyshevDistance(double* tuple1, double* tuple2, size_t tupleSize);
	// ���Ҿ���
	static double getCosineDistance(double* tuple1, double* tuple2);
	// �����������
	static double getSphericalDistance(double* tuple1, double* tuple2);

private:
	Distance() {}
};

