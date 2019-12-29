#include "FESystem.h"

FESystem* FESystem::s_pSystem = nullptr;

FESystem::FESystem(void* i_hInst)
	: _hInst(i_hInst), m_bExit(false)
{
	_windows.reserve(8);
	//_systemTimer.TimerStart();
}

bool FESystem::CreateSystem()
{
	std::unique_ptr<FEWindow> window;
	bool result;

	//-----------------------------------------------------------------------------
	// 추후에 파일을 읽어서 생성 시 window에 만들어서 성공하면 벡터에 집어넣는걸로..
	//-----------------------------------------------------------------------------

	window = std::make_unique<FEWindow>(1600, 900, L"WindowName", L"ClassName");
	result = window->Create(static_cast<HINSTANCE>(_hInst));

	if (result == false)
	{
		assert(result);

		window->Release(static_cast<HINSTANCE>(_hInst));
		return false;
	}

	else
		_windows.push_back(std::move(window));

	////////////////////////////////////////////////////////////////////////////////

	return true;
}

bool FESystem::DataLoading()
{
	bool result = true;

	assert(result);

	return true;
}

bool FESystem::MessagePump()
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		// 메세지가 있는지 체크
		// 메세지 큐에 메세지가 있으면 처리를 합니다
		if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)			// 윈도우 종료
				break;

			//나머지 메세지 처리.
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			// 특별한 메세지가 없다면 게임(렌더링)을 진행합니다.
			return true;
		}
	}

	return false;
}

void FESystem::Run()
{
	static FE::FLOAT oldTime = _systemTimer.GetElapseTime();
	FE::FLOAT curTime;

	_systemTimer.Start();
	
	while (m_bExit == false)
	{
		if (MessagePump() == false)
			break;

		curTime = _systemTimer.GetElapseTime();
		_deltaTime = curTime - oldTime;
		oldTime = curTime;
	}
}

void FESystem::Release()
{
	for (auto& window : _windows)
		window->Release(static_cast<HINSTANCE>(_hInst));

	_windows.clear();
}

FE::FLOAT FESystem::GetDeltaTime()
{
	return s_pSystem->_deltaTime;
}

FESystem* FESystem::GetInstance()
{
	return s_pSystem;
}