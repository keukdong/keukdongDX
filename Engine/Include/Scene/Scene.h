#pragma once

#include "../Engine.h"

ENGINE_BEGIN
class ENGINE_DLL CScene
{
	friend class CSceneManager;

private:
	CScene();
	~CScene();

public:
	bool Init();
	int Update(float fTime);
	int LateUpdate(float fTime);
	void Render(float fTime);
};
ENGINE_END

