#include "FEWindow.h"

FEWindow::FEWindow(FE::UINT32 i_width, FE::UINT32 i_height, const FE::tstring& i_windowName, const FE::tstring& i_className)
	: _width(i_width), _height(i_height), _windowName(i_windowName), _className(i_className), _hWnd()
{

}

bool FEWindow::Create(const HINSTANCE i_hInst)
{
	//-----------------------------------------------------------------
	//  생성할 윈도우의 '정보'를 설정합니다.
	//-----------------------------------------------------------------
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = FEWindow::MsgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = i_hInst;
	wc.hIcon = LoadIcon(i_hInst, static_cast<LPCTSTR>(IDI_APPLICATION));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = _className.c_str();
	wc.hIconSm = LoadIcon(i_hInst, static_cast<LPCTSTR>(IDI_APPLICATION));


	//-----------------------------------------------------------------
	// 윈도우를 '윈도우즈(OS)' 에 등록합니다.
	//-----------------------------------------------------------------
	RegisterClassEx(&wc);

	//-----------------------------------------------------------------
	// 윈도우를 생성합니다.
	//-----------------------------------------------------------------
	HWND hWnd = CreateWindow(_className.c_str(), _windowName.c_str(),
		WS_OVERLAPPEDWINDOW,
		100, 100,									// 윈도우 창의 위치
		_width, _height,							// 윈도우 창의 크기
		GetDesktopWindow(),
		nullptr, wc.hInstance, nullptr);

	if (hWnd == nullptr)
		return false;		// 윈도 생성 실패..

	_hWnd = hWnd;

	//-----------------------------------------------------------------
	// 화면에 윈도우를 그립니다.
	//-----------------------------------------------------------------
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	return true;
}

bool FEWindow::Release(const HINSTANCE i_hInst)
{
	//-----------------------------------------------------------------
	// 등록된 클레스 제거.
	//-----------------------------------------------------------------
	UnregisterClass(_className.c_str(), i_hInst);

	return true;
}

LRESULT CALLBACK FEWindow::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	//-----------------------------------------// 
	// 이외의 메세지는 기본윈도 프로시져로 넘깁니다. //
	//----------------------------------------// 
	return DefWindowProc(hwnd, msg, wParam, lParam);

}