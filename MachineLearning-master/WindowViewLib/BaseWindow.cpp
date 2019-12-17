#include "pch.h"
#include "BaseWindow.h"



BaseWindow::BaseWindow(HINSTANCE hInst, WCHAR* szTitle, WCHAR* szWindowClass)
{
	this->hWnd = nullptr;
	this->hInst = hInst;
	this->szTitle = szTitle;
	this->szWindowClass = szWindowClass;
}


BaseWindow::~BaseWindow()
{
}

BOOL BaseWindow::InitInstance()
{
	//HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);  //GetMOduleHandle函数获得当前应用程序实例句柄
	//assert(hInstance);

	// 窗口类
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BaseWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = this->hInst;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // (HBRUSH)::GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = nullptr;/*LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));*/

	// 注册窗口
	if (!::RegisterClassEx(&wcex))
	{
		::MessageBoxW(NULL, L"注册窗口失败", L"错误", MB_OK);
		return FALSE;
	}

	this->hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, this->hInst, (LPVOID)this);

	if (!this->hWnd)
	{
		return FALSE;
	}
	ShowWindow(this->hWnd, SW_SHOW);
	UpdateWindow(this->hWnd);
	return TRUE;
}

int BaseWindow::run()
{
	MSG msg;

	//主消息循环:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

// 消息处理
LRESULT BaseWindow::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	//case WM_NCPAINT:
	//{

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
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}

LRESULT CALLBACK BaseWindow::MWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
	{
		::DestroyWindow(hWnd);
		break;
	}
	case WM_DESTROY:
	{
		this->OnExit();
		::PostQuitMessage(0);
		break;
	}
	default:
	{
		return this->HandleMessage(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}

LRESULT CALLBACK BaseWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BaseWindow* mBaseWindow = nullptr;
	if (message == WM_CREATE)   // 在此消息收到时，把窗口对象句柄赋给C++对象成员，同时把C++对象地址赋给窗口对象成员  
	{
		mBaseWindow = (BaseWindow*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		mBaseWindow->hWnd = hWnd;                                            // 在此处获取HWND，此时CreateWindow()尚未返回。  
		::SetWindowLong(hWnd, GWL_USERDATA, (LONG)mBaseWindow);             // 通过USERDATA把HWND和C++对象关联起来  
	}
	mBaseWindow = (BaseWindow*)::GetWindowLong(hWnd, GWL_USERDATA);
	if (mBaseWindow)
	{
		return mBaseWindow->MWndProc(hWnd, message, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
