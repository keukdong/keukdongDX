#include "ResourceManager.h"
#include "Mesh.h"			//create mesh

ENGINE_USING
DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
}

bool CResourceManager::Init()
{
	/*
	VertexColor	tVtx[3]	=
	{
		VertexColor(Vector3(0.f, 0.5f, 0.f), Vector4::Gold),
		VertexColor(Vector3(0.5f, -0.5f, 0.f), Vector4::HotPink),
		VertexColor(Vector3(-0.5f, -0.5f, 0.f), Vector4::Green)
	};
	
	*/
	VertexColor tVtx[3] = 
	{
		VertexColor(XMFLOAT3(0.f, 0.5f, 0.f), XMFLOAT4(1.f, 1.f, 1.f, 1.f)),
		VertexColor(XMFLOAT3(0.5f, -0.5f, 0.f), XMFLOAT4(0.f, 0.f, 0.f, 0.f)),
		VertexColor(XMFLOAT3(-0.5f, -0.5f, 0.f), XMFLOAT4(1.f, 0.f, 0.f, 0.f)),
	};

	short	sIdx[3] = { 0, 1, 2 };

	_IFFAILED(CreateMesh("meshName", "meshShader", "meshLayout", tVtx, sizeof(VertexColor), 3,
		D3D11_USAGE_DEFAULT, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		sIdx, sizeof(short), 3, D3D11_USAGE_DEFAULT, DXGI_FORMAT_R16_UINT))
	{
		return false;
	}
	
	return true;
}

CMesh * CResourceManager::FindMesh(const string & strName)
{
	unordered_map<string, CMesh*>::iterator iter = m_mapMesh.find(strName);
	
	if (iter == m_mapMesh.end())
		return nullptr;

	return iter->second;
}

bool CResourceManager::CreateMesh(const string & strMesh, const string & strShader,
	const string & strLayout, void * pVtx, int iVtxSize, int iVtxCount,
	D3D11_USAGE eVtxUsage, D3D11_PRIMITIVE_TOPOLOGY ePrimitive,
	void* pIdx, int iIdxSize, int iIdxCount, D3D11_USAGE eIdxUsage, DXGI_FORMAT eFmt)
{
	CMesh *pMesh = FindMesh(strMesh);
	
	if (pMesh)
		return false;
	
	pMesh = new CMesh;
	_IFFAILED(pMesh->CreateMesh(strMesh, strShader, strLayout, pVtx, iVtxSize, iVtxCount,
		eVtxUsage, ePrimitive, pIdx, iIdxSize, iIdxCount, eIdxUsage, eFmt))
	{
		SAFE_RELEASE(pMesh);
		return false;
	}

	return true;
}
