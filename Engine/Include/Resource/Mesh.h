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
	ID3D11InputLayout* m_pLayout;

public:
	bool CreateMesh();

public:
	bool Init();
	int Update(float fTime);
	int LateUpdate(float fTime);
	void Render(float fTime);

};

ENGINE_END
