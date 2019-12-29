#pragma once

#ifndef _FE_TIME
#define _FE_TIME

#include "FEDefine.h"

#include <chrono>

class FETime final
{
public:
	enum class STATE : FE::UINT8
	{
		STOPPING,
		RUNNING,
		PAUSING
	};
	FETime(FE::FLOAT t_timeScale = 1.0f);
	~FETime() = default;

	void TimerStart();
	FE::FLOAT TimerPause();
	FE::FLOAT TimerStop();

	// If timer is not working, it always returns 0.
	FE::FLOAT GetElapseTime();

	void SetTimeScale(FE::FLOAT i_timeScale);

	FE::FLOAT GetTimeScale() const;
	STATE GetState() const;

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
	FE::FLOAT _timeScale;
	FE::FLOAT _elapseTime;
	STATE _state;
};

#endif