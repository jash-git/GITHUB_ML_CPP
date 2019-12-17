/*
*
*          logistic regression
* 
*
*/
class LogisticRegression 
{

public: 
  LogisticRegression(int, int, int);
  ~LogisticRegression();
  void train(int*, int*, double);
  void softmax(double*);
  void predict(int*, double*);
private:  
  int N;       // ������Ŀ
  int n_in;    // ����㵥Ԫ����
  int n_out;   // ����㵥Ԫ����
  double **W;  // Ȩ�ؾ���
  double *b;   // ƫ��

};