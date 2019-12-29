#pragma once
#ifndef _FE_WINDOW
#define _FE_WINDOW

#include <FEDefine.h>
#include <Windows.h>

class FEWindow
{
public:
	FEWindow() = delete;
	FEWindow(const FEWindow& other) = delete;
	FEWindow(FE::UINT32 i_width, FE::UINT32 i_height, const FE::tstring& i_windowName, const FE::tstring& i_className);
	~FEWindow() = default;

	bool Create(const HINSTANCE i_hInst);
	bool Release(const HINSTANCE i_hInst);

	static LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	FE::UINT32	_width;
	FE::UINT32	_height;
	FE::tstring	_windowName;
	FE::tstring	_className;
public:
	void*		_hWnd;
};

#endif