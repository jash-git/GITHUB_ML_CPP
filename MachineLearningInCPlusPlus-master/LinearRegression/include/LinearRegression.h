/*******************************************************************
*����־�� ����ѧϰ��C++����
*
* htfeng
* 2018.09.28
*
* �����£�����ģ��
* ����һ�����Իع����
*******************************************************************/
#ifndef ML_LINEARREGRESSION_H//��������û�б�����
#define ML_LINEARREGRESSION_H//�����


class LinearRegression {
public:
	double *x;
	double *y;
	int m;
	double *theta;
	__declspec(dllexport) LinearRegression(double x[], double y[], int m);
	__declspec(dllexport) void train(double alpha, int iterations);
	__declspec(dllexport) double predict(double x);
private:
	//����ģ����ʧ
	__declspec(dllexport) static double compute_cost(double x[], double y[], double theta[], int m);
	//���㵥��Ԥ��ֵ
	__declspec(dllexport) static double h(double x, double theta[]);
	//Ԥ��
	__declspec(dllexport) static double *calculate_predictions(double x[], double theta[], int m);
	//�ݶ��½�
	__declspec(dllexport) static double *gradient_descent(double x[], double y[], double alpha, int iter, double *J, int m);
};

#endif
