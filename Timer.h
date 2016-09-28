
#pragma once

#include "stdafx.h"
class Timer
{
private:
	LARGE_INTEGER m_frequency;
	LARGE_INTEGER m_currentTime;
	LARGE_INTEGER m_startTime;
	LARGE_INTEGER m_lastTime;
	float m_total;
	float m_delta;

public:
	Timer();
	void Reset();
	void Update();




	float GetTotalTime();

	float GetDeltaTime();



};
