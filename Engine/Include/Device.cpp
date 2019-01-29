#include "Device.h"

ENGINE_USING

DEFINITION_SINGLE(CDevice);
CDevice::CDevice() :
	m_pDevice(nullptr),
	m_pContext(nullptr),
	m_pSwapChain(nullptr)
{
}

CDevice::~CDevice()
{
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pTargetView);
	SAFE_RELEASE(m_pDepthView);

	if (m_pContext)
		m_pContext->ClearState();

	SAFE_RELEASE(m_pContext);
	SAFE_RELEASE(m_pDevice);
}

bool CDevice::Init(HWND hWnd, UINT iWidth, UINT iHeight, bool bWindowMode)
{
	UINT	iFlag = 0;

#ifdef _DEBUG
	iFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG


	D3D_FEATURE_LEVEL	eFLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL	eFLevel1 = D3D_FEATURE_LEVEL_11_0;

	DXGI_SWAP_CHAIN_DESC	tSwapDesc = {};

	tSwapDesc.BufferDesc.Width = iWidth;
	tSwapDesc.BufferDesc.Height = iHeight;
	tSwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tSwapDesc.BufferDesc.RefreshRate.Numerator = 1;
	tSwapDesc.BufferDesc.RefreshRate.Denominator = 60;
	tSwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	tSwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	tSwapDesc.BufferCount = 1;
	tSwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	tSwapDesc.OutputWindow = hWnd;
	tSwapDesc.SampleDesc.Count = 1;
	tSwapDesc.SampleDesc.Quality = 0;
	tSwapDesc.Windowed = bWindowMode;
	tSwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0,
		iFlag, &eFLevel, 1, D3D11_SDK_VERSION, &tSwapDesc,
		&m_pSwapChain, &m_pDevice, &eFLevel1, &m_pContext)))
	{
		MessageBox(hWnd, "Failed to create device, swapchain", 0, 0);
		return false;
	}

	ID3D11Texture2D*	pBuffer = nullptr;

	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		(void**)&pBuffer);

	m_pDevice->CreateRenderTargetView(pBuffer, nullptr,
		&m_pTargetView);

	SAFE_RELEASE(pBuffer);

	D3D11_TEXTURE2D_DESC	tDepthDesc = {};

	tDepthDesc.Width = iWidth;
	tDepthDesc.Height = iHeight;
	tDepthDesc.ArraySize = 1;
	tDepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tDepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tDepthDesc.Usage = D3D11_USAGE_DEFAULT;
	tDepthDesc.SampleDesc.Count = 1;
	tDepthDesc.SampleDesc.Quality = 0;
	tDepthDesc.MipLevels = 1;

	m_pDevice->CreateTexture2D(&tDepthDesc, nullptr,
		&pBuffer);

	m_pDevice->CreateDepthStencilView(pBuffer, nullptr,
		&m_pDepthView);

	SAFE_RELEASE(pBuffer);

	m_pContext->OMSetRenderTargets(1, &m_pTargetView, m_pDepthView);

	D3D11_VIEWPORT	tVP = {};

	tVP.Width = iWidth;
	tVP.Height = iHeight;
	tVP.MaxDepth = 1.f;

	m_pContext->RSSetViewports(1, &tVP);

	return true;
}
void CDevice::ClearTarget(float fClearColor[4])
{
	m_pContext->ClearRenderTargetView(m_pTargetView, fClearColor);
	m_pContext->ClearDepthStencilView(m_pDepthView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void CDevice::Present()
{
	m_pSwapChain->Present(0, 0);
}

