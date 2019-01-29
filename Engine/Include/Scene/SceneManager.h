#pragma once
#include "../Engine.h"
ENGINE_BEGIN

class ENGINE_DLL CSceneManager
{
private:
	class CScene *m_pScene;
	class CScene *m_pNextScene;

public:
	bool Init();
	int Update(float fTime);
	int LateUpdate(float fTime);
	void Render(float fTime);
	DECLARE_SINGLE(CSceneManager)
};

ENGINE_END