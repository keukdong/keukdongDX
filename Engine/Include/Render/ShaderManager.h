#pragma once
#include "../Engine.h"
ENGINE_BEGIN
class ENGINE_DLL CShaderManager
{
private:
	unordered_map<string, ID3D11InputLayout* >	m_mapLayout;
	
	vector<D3D11_INPUT_ELEMENT_DESC> m_vecLayoutDesc;
	int		m_iLayoutOffset = 0;

public:
	bool AddLayoutDesc(const char* pSemantic, int iSemanticIdx, DXGI_FORMAT eFormat,
		UINT iInputSlot, UINT iOffset, D3D11_INPUT_CLASSIFICATION eSlotClass,
		UINT iInstanceData);
	bool CreateLayout(const string& strName, const string& strShaderKey);
	ID3D11InputLayout* FindLayout(const string &strName);


	DECLARE_SINGLE(CShaderManager)
};
ENGINE_END
