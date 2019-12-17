#pragma once
class Distance
{
public:
	virtual ~Distance(){}
	// Å·ÊÏ¾àÀë
	static double getEuclideanDistance(double* tuple1, double* tuple2, size_t tupleSize);
	// Âü¹ş¶Ù¾àÀë
	static double getManhattanDistance(double* tuple1, double* tuple2, size_t tupleSize);
	// ÇĞ±ÈÑ©·ò¾àÀë
	static double getChebyshevDistance(double* tuple1, double* tuple2, size_t tupleSize);
	// ÓàÏÒ¾àÀë
	static double getCosineDistance(double* tuple1, double* tuple2);
	// µØÇòÇòÃæ¾àÀë
	static double getSphericalDistance(double* tuple1, double* tuple2);

private:
	Distance() {}
};

