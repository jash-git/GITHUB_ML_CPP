// NewtonIterationMethod.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "NewtonIterationMethod.h"
#include "MyWindow.h"

#define MAX_LOADSTRING 100

// 全局变量:
MyWindow* myWindow = nullptr;
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_NEWTONITERATIONMETHOD, szWindowClass, MAX_LOADSTRING);
  
	MyWindow* myWindow = new MyWindow(hInstance, szTitle, szWindowClass);
	myWindow->InitInstance();

	return myWindow->run();
}
