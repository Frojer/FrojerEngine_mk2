#include "FESystem.h"


//-----------------
// WinMain 함수
//-----------------
int APIENTRY WinMain(_In_ HINSTANCE hInstance,	// 프로그램의 인스턴스 핸들
	_In_opt_ HINSTANCE hPrevInstance,			// 바로 앞에 실행된 현재 프로그램의 인스턴스 핸들.없을 경우는 NULL이 되며 WIN32에서는 항상 NULL이다.호환성을 위해서만 존재하는 인수이므로 신경쓰지 않아도 된다.
	_In_ LPSTR lpCmdLine,						// 명령행으로 입력된 프로그램 인수이다.도스의 argv인수에 해당한다.
	_In_ int nShowCmd)							// 프로그램이 실행될 형태이며 최소화, 보통모양 등이 전달된다.
{
	bool result;

	FESystem::s_pSystem = new FESystem(static_cast<void*>(hInstance));

	result = FESystem::s_pSystem->CreateSystem();
	assert(result);

	result = FESystem::s_pSystem->DataLoading();
	assert(result);

	FESystem::s_pSystem->Run();

	FESystem::s_pSystem->Release();

	delete FESystem::s_pSystem;
	return 0;
}