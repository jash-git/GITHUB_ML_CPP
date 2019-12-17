#pragma once

#include "BaseWindow.h"

class MyWindow :
	public BaseWindow
{
public:
	MyWindow(HINSTANCE hInst, WCHAR* szTitle, WCHAR* szWindowClass);
	~MyWindow();
protected:
	LRESULT HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnPaint(HDC hdc, PAINTSTRUCT ps);
	void OnKeyDown(WPARAM keyCode);
	void OnKeyUp(WPARAM keyCode);
	void OnExit();
};

