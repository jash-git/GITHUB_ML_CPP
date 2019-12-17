#include "MyWindow.h"
#include <math.h>
#include <time.h>
#include <stdio.h>


#define BUFF_SIZE 80

// ȫ�ֱ���:
double bias = -200.0;

// �˴���ģ���а����ĺ�����ǰ������:
void PaintCoordinate(HDC hdc, PAINTSTRUCT ps);
double xd2(double x, double bias = 0.0);
double xd(double x, double y = 0.0, double bias = 0.0);
void PaintFunction(HDC hdc, PAINTSTRUCT ps);
void PaintTipInfo(HDC hdc, PAINTSTRUCT ps);
void NewtonIteration(HDC hdc, PAINTSTRUCT ps, double x, double threshold);


MyWindow::MyWindow(HINSTANCE hInst, WCHAR* szTitle, WCHAR* szWindowClass) :BaseWindow(hInst, szTitle, szWindowClass)
{
}


MyWindow::~MyWindow()
{
}

// ��Ϣ����
LRESULT MyWindow::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		//PAINTSTRUCT ��ͼ�ṹ�壬�洢Ŀ�괰�ڿ��Ի�ͼ�Ŀͻ�������(client area)
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps); // DC(�ɻ�ͼ���ڴ����) �ľ��
		//TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
		this->OnPaint(hdc, ps);
		EndPaint(hWnd, &ps);
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}

void MyWindow::OnPaint(HDC hdc, PAINTSTRUCT ps)
{
	PaintTipInfo(hdc, ps);
	PaintCoordinate(hdc, ps);
	PaintFunction(hdc, ps);
	srand((unsigned int)time(NULL));
	double start = (double)(rand() % (ps.rcPaint.right - ps.rcPaint.right / 5)) + ps.rcPaint.right / 5.0;
	NewtonIteration(hdc, ps, start, 5.0);
}

void PaintTipInfo(HDC hdc, PAINTSTRUCT ps)
{
	WCHAR BUFF[BUFF_SIZE];
	ZeroMemory(BUFF, BUFF_SIZE);
	swprintf(BUFF, BUFF_SIZE, L"ţ�ٵ������󷽳� y = %.3f * x * x + %d ���ĸ�", 0.005, (int)bias);
	//wsprintfW(BUFF, L"ţ�ٵ������󷽳� y = 0.005 * x * x + %d ���ĸ�", (int)bias);
	int x = ps.rcPaint.right - 350;
	int y = ps.rcPaint.bottom - 100;
	TextOut(hdc, x, y, BUFF, lstrlenW(BUFF));
	//RECT rect = { 500, 500, 100, 100 };
	//DrawText(hdc, BUFF, -1, &rect, DT_CENTER | DT_VCENTER);
}

#define OFFSET_BOTTOM 250

// ��������
void PaintCoordinate(HDC hdc, PAINTSTRUCT ps)
{
	HPEN hpen; // ����
	hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hpen = (HPEN)SelectObject(hdc, hpen);

	WCHAR BUFF[BUFF_SIZE];
	ZeroMemory(BUFF, BUFF_SIZE);

	//���� x ��
	//MoveToEx(hdc, 0, ps.rcPaint.bottom / 2, NULL);
	//LineTo(hdc, ps.rcPaint.right, ps.rcPaint.bottom / 2);

	int y = ps.rcPaint.bottom - OFFSET_BOTTOM;
	for (int x = 0; x < ps.rcPaint.right; x++)
	{
		SetPixel(hdc, x, y, RGB(0, 0, 0));
		if (x % 40 == 0)
		{
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x, y + 10);
			wsprintf(BUFF, L"%d", x);
			TextOut(hdc, x - 10, y + 20, BUFF, lstrlenW(BUFF));
			ZeroMemory(BUFF, BUFF_SIZE);
		}
	}

	//���� y ��
	//MoveToEx(hdc, ps.rcPaint.right / 2, 0, NULL);
	//LineTo(hdc, ps.rcPaint.right / 2, ps.rcPaint.bottom);
	int x = 80;
	for (int y = ps.rcPaint.bottom - OFFSET_BOTTOM; y >= 0; y--)
	{
		SetPixel(hdc, x, y, RGB(0, 0, 0));
		if (y % 20 == 0)
		{
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x - 10, y);
			wsprintf(BUFF, L"%d", ps.rcPaint.bottom - OFFSET_BOTTOM - y);
			TextOut(hdc, x - 40, y - 8, BUFF, lstrlenW(BUFF));
			ZeroMemory(BUFF, BUFF_SIZE);
		}
	}

	for (int y = ps.rcPaint.bottom - OFFSET_BOTTOM; y < ps.rcPaint.bottom; y++)
	{
		SetPixel(hdc, x, y, RGB(0, 0, 0));
		if (y % 20 == 0)
		{
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x - 10, y);
			wsprintf(BUFF, L"%d", ps.rcPaint.bottom - OFFSET_BOTTOM - y);
			TextOut(hdc, x - 40, y - 8, BUFF, lstrlenW(BUFF));
			ZeroMemory(BUFF, BUFF_SIZE);
		}
	}
	hpen = (HPEN)SelectObject(hdc, hpen);
	DeleteObject(hpen);
}

double xd2(double x, double bias)
{
	return 0.005* (x * x) + bias;
}

double xd(double x, double y, double bias)
{
	double k = 0.01 * x;
	double b = xd2(x, bias) - k * x;
	return (y - b) / k;
}

// ���ƺ���ͼ��
void PaintFunction(HDC hdc, PAINTSTRUCT ps)
{
	HPEN hpen; // ����
	hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	hpen = (HPEN)SelectObject(hdc, hpen);

	double offset = ps.rcPaint.right / 2.0;
	double x = ps.rcPaint.right / 5.0;
	double threshold = xd2(x - offset, bias);
	double y = threshold;
	do {
		SetPixel(hdc, (int)x, ps.rcPaint.bottom - OFFSET_BOTTOM - (int)y, RGB(0, 0, 255));
		y = xd2(x - offset, bias);
		x += 0.02;
	} while (y <= threshold);

	hpen = (HPEN)SelectObject(hdc, hpen);
	DeleteObject(hpen);
}

// ţ�ٵ�����
void NewtonIteration(HDC hdc, PAINTSTRUCT ps, double x, double threshold)
{
	HPEN hpen; // ����
	hpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	hpen = (HPEN)SelectObject(hdc, hpen);

	double x_offset = ps.rcPaint.right / 2.0;
	double y_offset = (long double)ps.rcPaint.bottom - OFFSET_BOTTOM;
	double y = xd2(x - x_offset, bias);
	do
	{
		MoveToEx(hdc, (int)x, (int)y_offset - (int)y, NULL);
		x = xd(x - x_offset, 0.0, bias) + x_offset; // �����X�������ཻ�ĵ㲢����ת��
		y = xd2(x - x_offset, bias); // ����ĵ��x^2��ֵ
		LineTo(hdc, (int)x, (int)y_offset); // ����
		LineTo(hdc, (int)x, (int)y_offset - (int)y); // ����
		LineTo(hdc, 80, (int)y_offset - (int)y); // ����
	} while (fabs(y) > threshold);

	hpen = (HPEN)SelectObject(hdc, hpen);
	DeleteObject(hpen);
}
