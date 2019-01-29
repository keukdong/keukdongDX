#include "Timer.h"
#include "System.h"

ENGINE_USING

CTimer::CTimer():
	m_fFPS(0),
	m_fFPSTime(0),
	m_fDeltaTime(0),
	m_iFrame(0)
{
}

CTimer::~CTimer()
{
}

bool CTimer::Init()
{
	QueryPerformanceFrequency(&m_tSecond);
	QueryPerformanceCounter(&m_tTick);

	return true;
}

void CTimer::Update()
{
	LARGE_INTEGER tTick;
	QueryPerformanceCounter(&tTick);

	m_fDeltaTime = (tTick.QuadPart - m_tTick.QuadPart)
		/ static_cast<float>(m_tSecond.QuadPart);

	m_tTick = tTick;

	m_fFPSTime += m_fDeltaTime;
	++m_iFrame;

	if (m_iFrame == 60)
	{
		m_fFPS = m_iFrame / m_fFPSTime;
		m_fFPSTime = 0.f;
		m_iFrame = 0;

		char strFPS[256] = {};
		sprintf_s(strFPS, "FPX : %5.f", m_fFPS);
		SetWindowTextA(_WINDOWHANDLE, strFPS);
	}
}
