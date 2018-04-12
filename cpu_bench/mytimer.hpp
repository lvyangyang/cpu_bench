#pragma once
#include "windows.h"
class CStopWatch
{
public:
	CStopWatch();
	void start();
	void stop();
	double getElapsedTime(); //in s
	LARGE_INTEGER m_start;
	LARGE_INTEGER m_stop;
	LARGE_INTEGER m_frequency;
};
CStopWatch::CStopWatch()
{
	m_start.QuadPart = 0;
	m_stop.QuadPart = 0;
	QueryPerformanceFrequency(&m_frequency);
}

void CStopWatch::start()
{
	QueryPerformanceCounter(&m_start);
}

void CStopWatch::stop()
{
	QueryPerformanceCounter(&m_stop);
}

double CStopWatch::getElapsedTime()
{
	LARGE_INTEGER time;
	time.QuadPart = m_stop.QuadPart - m_start.QuadPart;
	return (double)time.QuadPart / (double)m_frequency.QuadPart;
}