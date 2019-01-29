#include "Engine.h"
#include "System.h"
#include "resource.h"

ENGINE_USING

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	if (!GET_SINGLE(CSystem)->Init(hInstance, TEXT("title"), TEXT("Client"), 1280, 720, IDI_ICON1, IDI_ICON1))
	{
		DESTROY_SINGLE(CSystem);
		return 0;
	}
	GET_SINGLE(CSystem)->Run();
	DESTROY_SINGLE(CSystem);
	return 1;
}

