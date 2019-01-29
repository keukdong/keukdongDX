#include "TimeManager.h"
#include "Timer.h"
ENGINE_USING

DEFINITION_SINGLE(CTimeManager)

CTimeManager::CTimeManager()
{
}


CTimeManager::~CTimeManager()
{
	unordered_map<string, CTimer*>::iterator iter = m_mapTimer.begin();
	unordered_map<string, CTimer*>::iterator iterEnd = m_mapTimer.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

CTimer * CTimeManager::CreateTimer(const string & strName)
{
	CTimer* pTimer = FindTimer(strName);
	
	if (pTimer)
		return nullptr;
	
	pTimer = new CTimer;
	pTimer->Init();
	m_mapTimer.insert(make_pair(strName, pTimer));

	return pTimer;
}

CTimer * CTimeManager::FindTimer(const string & strName)
{
	unordered_map<string, CTimer*>::iterator iter = m_mapTimer.find(strName);

	if (iter == m_mapTimer.end())
		return nullptr;

	return iter->second;
}

bool CTimeManager::Init()
{
	CreateTimer("EngineTimer");

	return true;
}

