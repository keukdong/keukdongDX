#pragma once
#include "Engine.h"
ENGINE_BEGIN
class ENGINE_DLL CRef
{
public:
	CRef();
	virtual ~CRef()=0;

protected:
	std::string m_strTag;
	bool m_bEnable;
	bool m_bActive;
	int m_iRef;

public:
	void AddRef();
	int Release();
	void SetTag(const std::string& strTag);
	std::string GetTag() const;
	void Enable(bool bEnable);
	bool IsEnable() const;
	void Kill();
	bool IsActive() const;

};
ENGINE_END

