#pragma once

#include <windows.h>
#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ�ļ����ų�����ʹ�õ�����


class BaseWindow
{
public:
	BaseWindow(HINSTANCE hInst, WCHAR* szTitle, WCHAR* szWindowClass);
	virtual ~BaseWindow();

public:
	virtual BOOL InitInstance();
	virtual int run();

protected:
	virtual LRESULT HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnPaint(HDC hdc, PAINTSTRUCT ps) {}
	virtual void OnExit() {}

private:
	LRESULT CALLBACK MWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	// ȫ�ֱ���:
	HINSTANCE hInst;									// ��ǰʵ��
	HWND hWnd;											// ��ǰ���ھ��
	WCHAR *szTitle;										// �������ı�
	WCHAR *szWindowClass;								// ����������
};

