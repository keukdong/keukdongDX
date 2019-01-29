#include "EngineMath.h"

ENGINE_DLL float RadianToDegree(float fAngle)
{
	return fAngle * 180.f / PI;
}

ENGINE_DLL float DegreeToRadian(float fAngle)
{
	return fAngle * PI / 180.f;
}
