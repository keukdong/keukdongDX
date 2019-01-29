#include "ShaderManager.h"
#include "../Device.h"

ENGINE_USING
DEFINITION_SINGLE(CShaderManager)

CShaderManager::CShaderManager():
	m_iLayoutOffset(0)
{
	m_vecLayoutDesc.clear();
}

CShaderManager::~CShaderManager()
{
	auto iter = m_mapLayout.begin();
	auto iterEnd = m_mapLayout.end();
	for (; iter != iterEnd;)
	{
		SAFE_RELEASE(iter->second);
	}
	m_mapLayout.clear();
}

bool CShaderManager::AddLayoutDesc(const char * pSemantic, int iSemanticIdx,
	DXGI_FORMAT eFormat, UINT iInputSlot, UINT iOffset,
	D3D11_INPUT_CLASSIFICATION eSlotClass, UINT iInstanceData)
{
	/*
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = 
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	*/

	D3D11_INPUT_ELEMENT_DESC tDesc = {};
	tDesc.SemanticName		= pSemantic;
	tDesc.SemanticIndex		= iSemanticIdx;
	tDesc.Format			= eFormat;
	tDesc.InputSlot			= iInputSlot;
	tDesc.AlignedByteOffset = m_iLayoutOffset;
	m_iLayoutOffset			+= iOffset;
	tDesc.InputSlotClass	= eSlotClass;
	tDesc.InstanceDataStepRate = iInstanceData;

	m_vecLayoutDesc.push_back(tDesc);
	return true;
}

bool CShaderManager::CreateLayout(const string & strName, const string & strShaderKey)
{
	ID3D11InputLayout* pLayout = FindLayout(strName);
	
	if (pLayout)
		return false;

	// shader compile 되어있어야한다.
	// 그렇다면 shader에서 한번에 input layout처리하는게 낫다.
	void *pShadercode = nullptr;
	SIZE_T pShadercodeSize = 0;

	if (FAILED(_DEVICE->CreateInputLayout(&m_vecLayoutDesc[0], m_vecLayoutDesc.size(),
		pShadercode, pShadercodeSize, &pLayout)))
	{
		m_vecLayoutDesc.clear();
		m_iLayoutOffset = 0;

		return false;
	}

	//mesh에서 input layout 묶어주고 렌더한다. 
	

	// clear variable to create next inputLayout
	m_vecLayoutDesc.clear();
	m_iLayoutOffset = 0;
	return true;
}

ID3D11InputLayout * CShaderManager::FindLayout(const string & strName)
{
	return nullptr;
}
