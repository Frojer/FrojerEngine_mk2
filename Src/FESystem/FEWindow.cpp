#include "FEWindow.h"

FEWindow::FEWindow(FE::UINT32 i_width, FE::UINT32 i_height, const FE::tstring& i_windowName, const FE::tstring& i_className)
	: _width(i_width), _height(i_height), _windowName(i_windowName), _className(i_className), _hWnd()
{

}

bool FEWindow::Create(const HINSTANCE i_hInst)
{
	//-----------------------------------------------------------------
	//  ������ �������� '����'�� �����մϴ�.
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
	// �����츦 '��������(OS)' �� ����մϴ�.
	//-----------------------------------------------------------------
	RegisterClassEx(&wc);

	//-----------------------------------------------------------------
	// �����츦 �����մϴ�.
	//-----------------------------------------------------------------
	HWND hWnd = CreateWindow(_className.c_str(), _windowName.c_str(),
		WS_OVERLAPPEDWINDOW,
		100, 100,									// ������ â�� ��ġ
		_width, _height,							// ������ â�� ũ��
		GetDesktopWindow(),
		nullptr, wc.hInstance, nullptr);

	if (hWnd == nullptr)
		return false;		// ���� ���� ����..

	_hWnd = hWnd;

	//-----------------------------------------------------------------
	// ȭ�鿡 �����츦 �׸��ϴ�.
	//-----------------------------------------------------------------
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	return true;
}

bool FEWindow::Release(const HINSTANCE i_hInst)
{
	//-----------------------------------------------------------------
	// ��ϵ� Ŭ���� ����.
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
	// �̿��� �޼����� �⺻���� ���ν����� �ѱ�ϴ�. //
	//----------------------------------------// 
	return DefWindowProc(hwnd, msg, wParam, lParam);

}