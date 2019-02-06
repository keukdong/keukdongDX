#pragma once
#include "EngineMath.h"
ENGINE_BEGIN

typedef struct ENGINE_DLL _tagVertexColor
{
	XMFLOAT3	vPos;
	XMFLOAT4	vColor;

	_tagVertexColor()
	{
	}
	_tagVertexColor(const _tagVertexColor &vtx)
	{
		vPos = vtx.vPos;
		vColor = vtx.vColor;
	}
	_tagVertexColor(const XMFLOAT3 _vPos, const XMFLOAT4 _vColor)
	{
		vPos = _vPos;
		vColor = _vColor;
	}
}VertexColor, *PVertexColor;

typedef struct ENGINE_DLL _tagVertexTex
{
	XMFLOAT3	vPos;
	XMFLOAT2	vUV;

	_tagVertexTex()
	{
	}
	_tagVertexTex(const _tagVertexTex& vtx)
	{
		vPos = vtx.vPos;
		vUV = vtx.vUV;
	}
	_tagVertexTex(const XMFLOAT3& _vP, const XMFLOAT2& _vUV)
	{
		vPos = _vP;
		vUV = _vUV;
	}
}VertexTex, *PVertexTex;

ENGINE_END