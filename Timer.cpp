#include "Timer.h"

Timer::Timer(){
	QueryPerformanceFrequency(&m_frequency);
	Reset();
}

void Timer::Reset(){
	Update();
	m_startTime = m_currentTime;
	m_total = 0.0f;
	m_delta = 1.0f / 60.0f;
}

void Timer::Update(){
	QueryPerformanceCounter(&m_currentTime);

	m_total = static_cast<float>(static_cast<double>(m_currentTime.QuadPart - m_startTime.QuadPart) / static_cast<double>(m_frequency.QuadPart));

	if (m_lastTime.QuadPart == m_startTime.QuadPart) m_delta = 1.0f / 60.0f;
	else m_delta = static_cast<float>(static_cast<double>(m_currentTime.QuadPart - m_lastTime.QuadPart) / static_cast<double>(m_frequency.QuadPart));
	m_lastTime = m_currentTime;
}

float Timer::GetTotalTime(){
	return m_total;
}

float Timer::GetDeltaTime(){
	return m_delta;
}
