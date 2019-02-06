#include "Shader.h"

ENGINE_USING

CShader::CShader():
	m_pVSBlob(nullptr),
	m_pVS(nullptr),
	m_pPSBlob(nullptr),
	m_pPS(nullptr)
{
}

CShader::~CShader()
{
	SAFE_RELEASE(m_pVSBlob);
	SAFE_RELEASE(m_pVS);
	SAFE_RELEASE(m_pPSBlob);
	SAFE_RELEASE(m_pPS);
}

bool CShader::LoadShader(const string & strName, const string & strVertex,
	const string & strPixel, const char* pFilename, const string& strPath)
{
	//vertex


	//pixel
	return true;
}
