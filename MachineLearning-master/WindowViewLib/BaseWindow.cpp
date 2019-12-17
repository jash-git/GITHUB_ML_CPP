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
	//HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);  //GetMOduleHandle������õ�ǰӦ�ó���ʵ�����
	//assert(hInstance);

	// ������
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

	// ע�ᴰ��
	if (!::RegisterClassEx(&wcex))
	{
		::MessageBoxW(NULL, L"ע�ᴰ��ʧ��", L"����", MB_OK);
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

	//����Ϣѭ��:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

// ��Ϣ����
LRESULT BaseWindow::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	//case WM_NCPAINT:
	//{

	//}
	case WM_PAINT:
	{
		// PAINTSTRUCT ��ͼ�ṹ�壬�洢Ŀ�괰�ڿ��Ի�ͼ�Ŀͻ�������(client area)
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps); // DC(�ɻ�ͼ���ڴ����) �ľ��
		// TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
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
	if (message == WM_CREATE)   // �ڴ���Ϣ�յ�ʱ���Ѵ��ڶ���������C++�����Ա��ͬʱ��C++�����ַ�������ڶ����Ա  
	{
		mBaseWindow = (BaseWindow*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		mBaseWindow->hWnd = hWnd;                                            // �ڴ˴���ȡHWND����ʱCreateWindow()��δ���ء�  
		::SetWindowLong(hWnd, GWL_USERDATA, (LONG)mBaseWindow);             // ͨ��USERDATA��HWND��C++�����������  
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
