#pragma once

#include <windows.h>
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容


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
	// 全局变量:
	HINSTANCE hInst;									// 当前实例
	HWND hWnd;											// 当前窗口句柄
	WCHAR *szTitle;										// 标题栏文本
	WCHAR *szWindowClass;								// 主窗口类名
};

