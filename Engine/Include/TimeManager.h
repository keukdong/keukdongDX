#pragma once
#include "Engine.h"
ENGINE_BEGIN
class ENGINE_DLL CTimeManager
{

private:
	unordered_map<string, class CTimer*> m_mapTimer;
public:
	class CTimer* CreateTimer(const string& strName);
	class CTimer* FindTimer(const string& strName);

public:
	bool Init();

	DECLARE_SINGLE(CTimeManager)
};
ENGINE_END

