#pragma once
#ifndef _FE_SYSTEM
#define _FE_SYSTEM

#include <FEDefine.h>
#include "FETimer.h"
#include "FEWindow.h"

class FESystem final
{
public:
	FESystem(const FESystem& other) = delete;
	FESystem& operator=(const FESystem& rhs) = delete;

	static FE::FLOAT GetDeltaTime();
	static FESystem* GetInstance();

private:
	FESystem(void* i_hInst);
	~FESystem() = default;

	bool CreateSystem();
	bool DataLoading();
	bool MessagePump();
	void Run();
	void Release();

private:
	std::vector<std::unique_ptr<FEWindow>> _windows;
	FETimer _systemTimer;
	FE::FLOAT _deltaTime;
	void* _hInst;

	static FESystem* s_pSystem;

public:
	bool m_bExit;

	friend int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
};
#endif