#include "System.h"
#include "Device.h"
#include "TimeManager.h"
#include "Timer.h"
#include "Scene/SceneManager.h"

ENGINE_USING
DEFINITION_SINGLE(CSystem)
bool CSystem::m_bRun = true;

CSystem::CSystem()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(202);
}

CSystem::~CSystem()
{
	DESTROY_SINGLE(CSceneManager);
	DESTROY_SINGLE(CTimeManager);
	DESTROY_SINGLE(CDevice);
}

bool CSystem::Init(HINSTANCE hInst, const TCHAR * titleName, const TCHAR * className,
	unsigned int iWidth, unsigned int iHeight, int iIcon, int iSmallIcon,bool bWindowMode)
{
	m_hInst = hInst;

	Register(className, iIcon, iSmallIcon);
	// ���⼭ �ڵ� �޾ƿ�
	CreateWnd(titleName, className, iWidth, iHeight);
	
	// Init device
	if (!GET_SINGLE(CDevice)->Init(m_hWnd, iWidth, iHeight, bWindowMode))
		return false;
	// Init Timer
	if (!GET_SINGLE(CTimeManager)->Init())
		return false;
	// Init SceneManager
	if (!GET_SINGLE(CSceneManager)->Init())
		return false;

	return true;
}

int CSystem::Run()
{
	MSG msg;

	// �⺻ �޽��� �����Դϴ�.
	while (m_bRun)
	{
		// PeekMessage : �޼����� �������� FALSE�� ��ȯ�ϸ鼭 �ٷ� �������´�.
		// �޼����� ���� ��� TRUE�� ��ȯ�ϰ� �ȴ�.
		// �� �޼����� �̿��ϸ� �������� ����Ÿ���� �̿��ؼ� ������ ������ �� �ִ�.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			Logic();			
		}
	}
	return (int)msg.wParam;
}

void CSystem::Register(const TCHAR * className, int iIcon, int iSmallIcon)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CSystem::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(iIcon));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_MY180629);
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(iSmallIcon));

	RegisterClassEx(&wcex);
}

void CSystem::CreateWnd(const TCHAR * titleName, const TCHAR * className, UINT iWidth, UINT iHeight)
{
	m_hWnd = CreateWindow(className, titleName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, iWidth, iHeight,
		nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
		return;

	RECT	rc = { 0, 0, static_cast<LONG>(iWidth), static_cast<LONG>(iHeight) };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top,
		SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
}

LRESULT __stdcall CSystem::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		// WM_PAINT : ������â�� ������ ���� �׸��� ȣ��Ǵ� �޼����̴�.
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		// BeginPaint �Լ��� �̿��ؼ� �ش� �����쿡 �׸� �� �ִ� �׸��� ������ �����
		// ����. HDC �� ȭ�鿡 �׸��� ���� �����ε� ���⼭�� �� �������� �ڵ�(HWND)��
		// �������־ ���� �����쿡 ����� �� �ִ� �׸��� ������ ������.
		HDC hdc = BeginPaint(hWnd, &ps);

		// EndPaint�� �̿��ؼ� �׸��⸦ �����Ѵ�.
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		m_bRun = false;
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void CSystem::Logic()
{
	CTimer *pTimer = GET_SINGLE(CTimeManager)->FindTimer("EngineTimer");
	pTimer->Update();

	float fDeltaTime = pTimer->GetDeltaTime();

	Input(fDeltaTime);
	Update(fDeltaTime);
	LateUpdate(fDeltaTime);
	Render(fDeltaTime);
}

int CSystem::Input(float fTime)
{
	return GET_SINGLE(CSceneManager)->Input(fTime);
}

int CSystem::Update(float fTime)
{
	return GET_SINGLE(CSceneManager)->Update(fTime);
}

int CSystem::LateUpdate(float fTime)
{
	return GET_SINGLE(CSceneManager)->LateUpdate(fTime);
}

void CSystem::Render(float fTime)
{
	float	fColor[4] = { 0.f, 1.f, 0.f, 1.f };
	//device run
	GET_SINGLE(CDevice)->ClearTarget(fColor);
	GET_SINGLE(CSceneManager)->Render(fTime);
	GET_SINGLE(CDevice)->Present();
}
