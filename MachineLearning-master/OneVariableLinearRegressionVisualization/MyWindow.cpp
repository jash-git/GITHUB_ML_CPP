#include "MyWindow.h"
#include "LinearRegressionAlgorithm.h"
#include<stdio.h>
#include <time.h>

#define DATA_SIZE 250

// 全局变量:
Data* mData = nullptr;
LinearRegressionAlgorithm* lra = nullptr;
HANDLE hThread = nullptr;

// 此代码模块中包含的函数的前向声明:
DWORD WINAPI ThreadPro(LPVOID lpThreadParameter);
void PaintFunction(HDC hdc, PAINTSTRUCT ps);

MyWindow::MyWindow(HINSTANCE hInst, WCHAR* szTitle, WCHAR* szWindowClass) :BaseWindow(hInst, szTitle, szWindowClass)
{
	srand((unsigned int)time(0));
	mData = new Data(DATA_SIZE);
	lra = new LinearRegressionAlgorithm(0.0000000001, 0.0001);
}


MyWindow::~MyWindow()
{
}

void MyWindow::OnExit()
{
	CloseHandle(hThread);
}

// 消息处理
LRESULT MyWindow::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//case WM_ERASEBKGND:
		//{
		//	break;
		//}
		case WM_PAINT:
		{
			// PAINTSTRUCT 绘图结构体，存储目标窗口可以绘图的客户端区域(client area)
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps); // DC(可画图的内存对象) 的句柄
			// TODO: 在此处添加使用 hdc 的任何绘图代码...
			this->OnPaint(hdc, ps);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_KEYDOWN:
		{
			this->OnKeyDown(wParam);
			break;
		}
		case WM_KEYUP:
		{
			this->OnKeyUp(wParam);
			break;
		}
		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	return 0;
}

void MyWindow::OnKeyDown(WPARAM keyCode)
{
	switch (keyCode)
	{
	case VK_UP:break;
	default:
		break;
	}
}
void MyWindow::OnKeyUp(WPARAM keyCode)
{
	hThread = CreateThread(
		NULL,
		0,
		ThreadPro,
		hWnd,
		0,
		(DWORD*)0);
}

DWORD WINAPI ThreadPro(LPVOID lpThreadParameter)
{
	HWND hWnd = (HWND)lpThreadParameter;
	// 训练
	while (true)
	{
		Sleep(5);
		lra->GradientDescentAlgorithm(*mData);
		//SendMessageW(hWnd, WM_PAINT, 0, 0);
		//UpdateWindow(hWnd);
		InvalidateRect(hWnd, NULL, false);
	}
	return 0;
}

void drawEllipse(HDC hdc, int L, int T, int R, int B)
{
	HPEN hpen;
	HBRUSH hbrush;
	hpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	hbrush = CreateSolidBrush(RGB(255, 0, 0));
	hpen = (HPEN)SelectObject(hdc, hpen);
	hbrush = (HBRUSH)SelectObject(hdc, hbrush);
	Ellipse(hdc, L, T, R, B);
	hpen = (HPEN)SelectObject(hdc, hpen);
	hbrush = (HBRUSH)SelectObject(hdc, hbrush);

	DeleteObject(hpen);
	DeleteObject(hbrush);
}

// 绘制散点图
void PaintFunction(HDC hdc, PAINTSTRUCT ps)
{
	HPEN hpen; // 画笔
	//hpen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	//hpen = (HPEN)SelectObject(hdc, hpen);

	for (size_t i = 0; i < mData->trainDataVectorSize; i++)
	{
		double x = mData->trainDataVector[i];
		double y = mData->realValueVector[i];
		
		//SetPixel(hdc, (int)x + ps.rcPaint.right / 2, ps.rcPaint.bottom - 10 - (int)y, RGB(255, 0, 0));
		drawEllipse(hdc, 
			(int)x + ps.rcPaint.right / 2 - 2, ps.rcPaint.bottom - 10 - (int)y - 2, 
			(int)x + ps.rcPaint.right / 2 + 2, ps.rcPaint.bottom - 10 - (int)y + 2);
	}

	//hpen = (HPEN)SelectObject(hdc, hpen);
	//DeleteObject(hpen);
}

void MyWindow::OnPaint(HDC hdc, PAINTSTRUCT ps)
{
	HDC mdc = CreateCompatibleDC(hdc);
	HBITMAP bmp = CreateCompatibleBitmap(hdc, ps.rcPaint.right, ps.rcPaint.bottom);
	bmp = (HBITMAP)SelectObject(mdc, bmp);

	HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));// 画刷
	FillRect(mdc, &(ps.rcPaint), hbrush);

	int x = 10;
	int y = ps.rcPaint.bottom - 160;

#define MAX 80
//#define _UNICODE
	wchar_t  BUFF[MAX];

	ZeroMemory(BUFF, MAX);
	swprintf(BUFF, MAX, L"一元线性回归梯度下降可视化");
	TextOutW(mdc, x, y, BUFF, lstrlenW(BUFF));

	ZeroMemory(BUFF, MAX);
	swprintf(BUFF, MAX, L"初始化参数 theta[0] = %f, mtheta[1] = %f", lra->thetaParamVector[0], lra->thetaParamVector[1]);
	TextOutW(mdc, x, y + 40, BUFF, lstrlenW(BUFF));

	double xMin = mData->getMin();
	double yMin = lra->predict(xMin);
	ZeroMemory(BUFF, MAX);
	swprintf(BUFF, MAX, L"训练数据集最小数据 xMin = %f, yMin = %f", xMin, yMin);
	TextOutW(mdc, x, y + 60, BUFF, lstrlenW(BUFF));

	double xMax = mData->getMax();
	double yMax = lra->predict(xMax);
	ZeroMemory(BUFF, MAX);
	swprintf(BUFF, MAX, L"训练数据集最大数据 xMax = %f, yMax = %f", xMax, yMax);
	TextOutW(mdc, x, y + 80, BUFF, lstrlenW(BUFF));

	ZeroMemory(BUFF, MAX);
	swprintf(BUFF, MAX, L"X坐标偏移 %d", ps.rcPaint.right / 2);
	TextOutW(mdc, x, y + 100, BUFF, lstrlenW(BUFF));

	ZeroMemory(BUFF, MAX);
	swprintf(BUFF, MAX, L"请按任意键开始训练");
	TextOutW(mdc, x, y + 120, BUFF, lstrlenW(BUFF));

	MoveToEx(mdc, (int)xMin + ps.rcPaint.right / 2, ps.rcPaint.bottom - 10 - (int)yMin, NULL);
	LineTo(mdc, (int)xMax + ps.rcPaint.right / 2, ps.rcPaint.bottom - 10 - (int)yMax);

	PaintFunction(mdc, ps);

	BitBlt(hdc, 0, 0, ps.rcPaint.right, ps.rcPaint.bottom, mdc, 0, 0, SRCCOPY);
	bmp = (HBITMAP)SelectObject(mdc, bmp);
	DeleteObject(bmp);
	DeleteDC(mdc);
}
