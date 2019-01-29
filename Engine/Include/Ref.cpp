#include "Ref.h"

ENGINE_USING

CRef::CRef()	:
	m_bActive(true),
	m_bEnable(true),
	m_iRef(1)
{

}

CRef::~CRef()
{
}

inline void CRef::AddRef()
{
	++m_iRef;
}

int CRef::Release()
{
	--m_iRef;
	
	if (m_iRef == 0)
	{
		delete this;
		return 0;
	}
	return m_iRef;
}

inline void CRef::SetTag(const std::string & strTag)
{
	m_strTag = strTag;
}

inline std::string CRef::GetTag() const
{
	return m_strTag;
}

inline void CRef::Enable(bool bEnable)
{
	m_bEnable = bEnable;
}

inline bool CRef::IsEnable() const
{
	return m_bEnable;
}

inline void CRef::Kill()
{
	m_bActive = false;
}

inline bool CRef::IsActive() const
{
	return m_bActive;
}

