#pragma once

#ifndef _FE_TIME
#define _FE_TIME

#include "FEDefine.h"

#include <chrono>

class FETimer final
{
public:
	enum class STATE : FE::UINT8
	{
		STOP,
		RUNNING,
		PAUSE
	};
	FETimer(FE::FLOAT t_timeScale = 1.0f);
	~FETimer() = default;

	void Start();
	FE::FLOAT Pause();
	FE::FLOAT Stop();

	// If timer is not working, it always returns 0.
	FE::FLOAT GetElapseTime();

	void SetTimeScale(FE::FLOAT i_timeScale);

	FE::FLOAT GetTimeScale() const;
	STATE GetState() const;

private:
	// otp = _offsetTP, to = timeOffset;
	//  otp           to          otp
	//   |              |          |
	//   |--------------___________--------------++++++++++++++++++|
	// start          pause     start        timeScale            stop
	// otp�� ���ŵǸ� to�� ���ݱ����� �帥 �ð��� ����. �� �� ���ο� otp���� now()������ ���� ���� Ÿ�̸��� �� ����
	// timeScale���� offsetTime�� �������ִ� ������ �������� ������ offsetTime�� ����Ű�� �ͺ��� ���ݱ����� timeScale�� ����Ǳ⶧����
	std::chrono::time_point<std::chrono::high_resolution_clock> _offsetTP;
	FE::FLOAT _timeScale;
	FE::FLOAT _timeOffset;
	STATE _state;
};

#endif