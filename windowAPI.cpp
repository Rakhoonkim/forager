﻿#include "stdafx.h"
#include "playGround.h"
//API : Application Programming Interface

HINSTANCE	_hInstance;
HWND		_hWnd;

POINT _ptMouse;		//마우스 용 POINT
BOOL _leftButtonDown;	//중복 클릭 방지용

playGround _pg;

//함수의 프로토타입 선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowsSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG			message;
	WNDCLASS	wndClass;
	HRESULT hr = E_FAIL;
	//D2D 컴포넌트 추가 
	/*CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	hr = ::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_gp_D2DFactory);
	assert(hr == S_OK);
	hr = ::CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_gp_WICFactory));
	assert(hr == S_OK);*/
	
	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	ShowCursor(false);  // 커서를 감추기 위한 
//	wndClass.hCursor = LoadCursorFromFile("mouseCursor.cur");
	
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,
		WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	ShowWindow(_hWnd, cmdShow);

	//메시지 루프 돌기이전에
	if (FAILED(_pg.init()))
	{
		return 0;
	}
	/*
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	*/
	//PeekMessage를 끄는 이유는 윈도우 자체 메시지 버튼에서 눌려졌을때만 메시지가 가야하는데
	//픽메세지는 계속해서 루프도니까 너무 화면이 심하게 껌뻑거려서 잠깐 끈거임
	//당연하겠지만 원래 우리가 이미지로 씌워서 버튼 사용할꺼면 픽메세지로 해도 무방!

	
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else  // 가끔여기서 터지는데 원인 찾아보기
		{
			TIMEMANAGER->update(60.0f);
			_pg.update();
			_pg.render();
		}
	}
	

	//루프문이 다돌면 플레이그라운드 해제
	_pg.release();
	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _pg.MainProc(hWnd, iMessage, wParam, lParam);
}

//클라이언트 영역 재조정
void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	//실절적으로 클라이언트 영역 크기 셋팅 함수
	SetWindowPos(_hWnd, NULL, x, y,
		(winRect.right - winRect.left),
		(winRect.bottom - winRect.top),
		SWP_NOZORDER | SWP_NOMOVE);
}