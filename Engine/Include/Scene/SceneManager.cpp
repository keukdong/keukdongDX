#include "SceneManager.h"
#include "Scene.h"
ENGINE_USING
DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager():
	m_pScene(nullptr),
	m_pNextScene(nullptr)
{
}


CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_pScene);
	SAFE_DELETE(m_pNextScene);
}

bool CSceneManager::Init()
{
	m_pScene = new CScene;
	return true;
}

int CSceneManager::Input(float fTime)
{
	return m_pScene->Input(fTime);
}

int CSceneManager::Update(float fTime)
{
	return m_pScene->Update(fTime);
}

int CSceneManager::LateUpdate(float fTime)
{
	return m_pScene->LateUpdate(fTime);
}

void CSceneManager::Render(float fTime)
{
	m_pScene->Render(fTime);
}
