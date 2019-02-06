#include "ShaderManager.h"
#include "Shader.h"
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
	auto iter1 = m_mapLayout.begin();
	auto iter1End = m_mapLayout.end();
	for (; iter1 != iter1End;)
	{
		SAFE_RELEASE(iter1->second);
	}
	m_mapLayout.clear();

	auto iter2 = m_mapShader.begin();
	auto iter2End = m_mapShader.end();
	for (; iter2 != iter2End;)
	{
		SAFE_RELEASE(iter2->second);
	}
	m_mapLayout.clear();
}

bool CShaderManager::Init()
{
	// load shader, create layout 
	return true;
}

bool CShaderManager::LoadVertexPixelShader(const string& strName, const char* pFileName,
	const string& strVertex, const string& strPixel, const string& strPath)
{
	// one shader has vertex, pixel shader

	CShader *pShader = FindShader(strName);
	
	if (pShader)
	{
		SAFE_RELEASE(pShader);
		return false;
	}

	pShader = new CShader;

	_IFFAILED(pShader->LoadShader(strName, strVertex, strPixel, pFileName, strPath))
	{
		SAFE_RELEASE(pShader);
		return false;
	}

	m_mapShader.insert(make_pair(strName, pShader));
	return true;
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
	CShader *pShader = FindShader(strShaderKey);
	
	if (!pShader)
		return false;
	
	// 그렇다면 shader에서 한번에 input layout처리하는게 낫다.
	void *pShadercode = pShader->GetVSCodeAddress();
	SIZE_T pShadercodeSize = pShader->GetVSCodeSize();

	if (FAILED(_DEVICE->CreateInputLayout(&m_vecLayoutDesc[0], m_vecLayoutDesc.size(),
		pShadercode, pShadercodeSize, &pLayout)))
	{
		m_vecLayoutDesc.clear();
		m_iLayoutOffset = 0;

		return false;
	}

	// mesh에서 input layout 묶어주고 렌더한다. 
	
	// add map
	m_mapLayout.insert(make_pair(strName, pLayout));

	// clear variable to create next inputLayout
	m_vecLayoutDesc.clear();
	m_iLayoutOffset = 0;
	return true;
}

ID3D11InputLayout * CShaderManager::FindLayout(const string & strName)
{
	auto iter = m_mapLayout.find(strName);
	if(iter == m_mapLayout.end())
		return nullptr;

	return iter->second;
}

CShader * CShaderManager::FindShader(const string & strName)
{
	auto iter = m_mapShader.find(strName);
	if (iter == m_mapShader.end())
		return nullptr;
	iter->second->AddRef();
	return iter->second;
}
