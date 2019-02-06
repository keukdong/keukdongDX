#pragma once
#include "../Ref.h"

ENGINE_BEGIN
class ENGINE_DLL CMesh :
	public CRef
{
	friend class CResourceManager;

private:
	CMesh();
	~CMesh();

private:
	ID3D11Buffer* m_pIndexbuffer;
	ID3D11Buffer* m_pVertexbuffer;
	ID3D11InputLayout* m_pLayout;

private:
	string m_strName;
	string m_strShader;
	string m_strLayout;

public:
	bool CreateMesh(const string & strMesh, const string & strShader,
		const string & strLayout, void * pVtx, int iVtxSize, int iVtxCount,
		D3D11_USAGE eVtxUsage, D3D11_PRIMITIVE_TOPOLOGY ePrimitive,
		void* pIdx, int iIdxSize, int iIdxCount, D3D11_USAGE eIdxUsage, DXGI_FORMAT eFmt);

public:
	bool Init();
	int Update(float fTime);
	int LateUpdate(float fTime);
	void Render(float fTime);

};

ENGINE_END
