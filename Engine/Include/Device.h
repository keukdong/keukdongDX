#pragma once
#include "Engine.h"

ENGINE_BEGIN

class ENGINE_DLL CDevice
{
private:
	ID3D11Device *m_pDevice;
	ID3D11DeviceContext *m_pContext;
	IDXGISwapChain*			m_pSwapChain;
	ID3D11RenderTargetView*	m_pTargetView;
	ID3D11DepthStencilView*	m_pDepthView;

public:
	bool Init(HWND hWnd, UINT iWidth, UINT iHeight, bool bWindowMode);
	void ClearTarget(float fClearColor[4]);
	void Present();
private:
	DECLARE_SINGLE(CDevice)
};

ENGINE_END

