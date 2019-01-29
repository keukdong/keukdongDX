#include "Mesh.h"
#include "../Device.h"
ENGINE_USING

CMesh::CMesh()
{
}


CMesh::~CMesh()
{
}

bool CMesh::CreateMesh()
{
	return false;
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
	_CONTEXT->IASetInputLayout(m_pLayout);		//renderer¿¡¼­ set

	//_CONTEXT->IASetVertexBuffers()
	//_CONTEXT->IASetPrimitiveTopology();
}

