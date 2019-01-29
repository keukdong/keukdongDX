#include "Scene.h"
ENGINE_USING

CScene::CScene()
{
}

CScene::~CScene()
{
}

bool CScene::Init()
{
	return true;
}

int CScene::Update(float fTime)
{
	return 0;
}

int CScene::LateUpdate(float fTime)
{
	return 0;
}

void CScene::Render(float fTime)
{
	OutputDebugString(TEXT("Rendering\n"));
	// 여기서 렌더 그린다. 
}
