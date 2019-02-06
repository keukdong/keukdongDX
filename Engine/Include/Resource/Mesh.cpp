#include "Mesh.h"
#include "../Device.h"

ENGINE_USING

CMesh::CMesh()
{
}


CMesh::~CMesh()
{
}

bool CMesh::CreateMesh(const string & strMesh, const string & strShader,
	const string & strLayout, void * pVtx, int iVtxSize, int iVtxCount,
	D3D11_USAGE eVtxUsage, D3D11_PRIMITIVE_TOPOLOGY ePrimitive,
	void* pIdx, int iIdxSize, int iIdxCount, D3D11_USAGE eIdxUsage, DXGI_FORMAT eFmt)
{
	m_strName = strMesh;
	m_strShader = strShader;
	m_strLayout = strLayout;

	//create vertex buffer
	D3D11_BUFFER_DESC tDesc = {};
	tDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tDesc.ByteWidth = iVtxSize * iVtxCount;
	tDesc.Usage = eVtxUsage;
	switch (eVtxUsage)
	{
	case D3D11_USAGE_DYNAMIC:
		tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case D3D11_USAGE_DEFAULT:
		tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		break;
	}
	tDesc.MiscFlags = 0;


	D3D11_SUBRESOURCE_DATA tSub = { };
	tSub.pSysMem = pVtx;

	if (FAILED(_DEVICE->CreateBuffer(&tDesc, &tSub, &m_pVertexbuffer)))
		return false;

	//create index buffer
	tDesc = {};
	tDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	tDesc.ByteWidth = iIdxSize * iIdxCount;
	tDesc.Usage = eIdxUsage;
	switch (eIdxUsage)
	{
	case D3D11_USAGE_DYNAMIC:
		tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case D3D11_USAGE_DEFAULT:
		tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		break;
	}
	tDesc.MiscFlags = 0;


	tSub = {};
	tSub.pSysMem = pIdx;

	if (FAILED(_DEVICE->CreateBuffer(&tDesc, &tSub, &m_pVertexbuffer)))
		return false;
	return true;
}

bool CMesh::Init()
{
	return true;
}

int CMesh::Update(float fTime)
{
	return 0;
}

int CMesh::LateUpdate(float fTime)
{
	return 0;
}

void CMesh::Render(float fTime)
{
	//_CONTEXT->IASetInputLayout(m_pLayout);		
	//_CONTEXT->IASetVertexBuffers()
	//_CONTEXT->IASetPrimitiveTopology();
}

