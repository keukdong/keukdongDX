#pragma once
#include "Engine.h"
ENGINE_BEGIN

class ENGINE_DLL CTimer
{
	friend class CTimeManager;

private:
	CTimer();
	~CTimer();

private:
	LARGE_INTEGER m_tSecond;
	LARGE_INTEGER m_tTick;

	float m_fDeltaTime;
	float m_fFPS;
	float m_fFPSTime;
	int m_iFrame;

public:
	float GetDeltaTime() const
	{
		return m_fDeltaTime;
	}

public:
	bool Init();
	void Update();

};
ENGINE_END

