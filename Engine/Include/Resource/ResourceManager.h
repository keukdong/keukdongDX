#pragma once
#include "../Engine.h"

ENGINE_BEGIN

class ENGINE_DLL CResourceManager
{
private:
	unordered_map<string, class CMesh*>		m_mapMesh;

private:
	class CMesh* FindMesh(const string& strName);

public:
	bool Init();
	bool CreateMesh(const string &strMesh, const string& strShader, const string& strLayout,
		void* pVtx, int iVtxSize, int iVtxCount, D3D11_USAGE eVtxUsage,
		D3D11_PRIMITIVE_TOPOLOGY ePrimitive, void* pIdx, int iIdxSize,
		int iIdxCount, D3D11_USAGE eIdxUsage, DXGI_FORMAT eFmt);
	DECLARE_SINGLE(CResourceManager)

};
ENGINE_END

