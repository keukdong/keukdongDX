#pragma once
#include "Engine.h"

ENGINE_BEGIN
class ENGINE_DLL CSystem
{
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	static bool	m_bRun;
public:
	bool Init(HINSTANCE hInst, const TCHAR* titleName, const TCHAR* className,
		unsigned int iWidth, unsigned int iHeight, int iIcon, int iSmallIcon,bool bWindowMode=true);
	int Run();

public:
	HINSTANCE GetHInst() const
	{
		return m_hInst;
	}
	HWND GetHWnd() const
	{
		return m_hWnd;
	}

private:
	void Register(const TCHAR * className, int iIcon, int iSmallIcon);
	void CreateWnd(const TCHAR* titleName, const TCHAR* className, UINT iWidth,
		UINT iHeight);
	static LRESULT WINAPI WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void Logic();

private:
	int Input(float fTime);
	int Update(float fTime);
	int LateUpdate(float fTime);
	void Render(float fTime);
	DECLARE_SINGLE(CSystem)
	

};

ENGINE_END
