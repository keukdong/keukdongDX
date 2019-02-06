#pragma once
#include "../Ref.h"

ENGINE_BEGIN

class CShader
	:public CRef
{
	// �ڽ��� pixel, vertex shader code�� ����ִ´�. 
	//shader manager������ ����Բ� 
	friend class CShaderManager;
private:
	CShader();
	~CShader();

private:
	string m_strName;

private:
	ID3DBlob*			m_pVSBlob;
	ID3D11VertexShader*	m_pVS;
	ID3DBlob*			m_pPSBlob;
	ID3D11PixelShader*	m_pPS;

public:
	bool LoadShader(const string & strName, const string & strVertex,
		const string & strPixel, const char* pFilename, const string& strPath);

public:
	void* GetVSCodeAddress()
	{
		return m_pVSBlob->GetBufferPointer();
	}
	SIZE_T GetVSCodeSize() const
	{
		return m_pVSBlob->GetBufferSize();
	}
	
};

ENGINE_END

