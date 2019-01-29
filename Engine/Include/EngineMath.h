
#pragma once

/* DirectX math library, header */

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <assert.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")		

#pragma warning(disable : 4251)
using namespace DirectX;
using namespace DirectX::PackedVector;

#define	PI	3.141592f

#include "Macro.h"

ENGINE_DLL float RadianToDegree(float fAngle);
ENGINE_DLL float DegreeToRadian(float fAngle);
