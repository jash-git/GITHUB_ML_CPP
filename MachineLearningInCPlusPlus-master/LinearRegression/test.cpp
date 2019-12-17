/*******************************************************************
*����־�� ����ѧϰ��C++����
*
* htfeng
* 2018.09.28
*
* �����£�����ģ��
* ���Դ���
*******************************************************************/
#include <iostream>
#include "include/LinearRegression.h"
#include<fstream>

using namespace std;

double* readFile(string fileName) {
	ifstream in;
	in.open(fileName);
	double temp;
	int index = 0;
	double* data = new double[50];
	while (in >> temp) {
		data[index] = temp;
		index++;
	}
	for (int i = 0; i < 50; i++)
		cout << "X,Y" << data[i] << endl;
	return data;
}

int main() {
	double alpha = 0.07;
	int iterations = 200;
	double x_predict = 2.1212;
	double y_predict;

	// ��ȡ�ļ�
	string fileNameX = "data/ex2x.dat";
	string fileNameY = "data/ex2y.dat";
	ifstream in;
	in.open(fileNameX);
	double temp;
	int length = 0;
	while (in >> temp) {
		length++;
	}
	double* X = new double[length];
	double* Y = new double[length];

	// ģ��ѵ��Ԥ��
	X = readFile(fileNameX);
	Y = readFile(fileNameY);
	LinearRegression lr(X, Y, length);
	lr.train(alpha, iterations);
	y_predict = lr.predict(x_predict);
	cout << y_predict << endl;

	system("pause");
	return 0;
}