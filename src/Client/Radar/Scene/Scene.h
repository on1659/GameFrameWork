
// Copyright �� http://radar92.tistory.com 
// ���� ���� �� ����� ����
// �ڵ� ��� �� on1659@naver.com�� �����Ͻñ� �ٶ��ϴ�.

#pragma once

#include "Shader.h"

class CScene
{
public:
    CScene();
    ~CScene();

	void Start();
	void Relese();

	ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	ID3D12RootSignature *GetGraphicsRootSignature() { return(m_pd3dGraphicsRootSignature); }

    void Update(float fTimeElapsed);
    void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera=NULL);

	void ReleaseUploadBuffers();

protected:
	ID3D12RootSignature			*m_pd3dGraphicsRootSignature = NULL;

	CShader					*m_pShaders = NULL;
	int							m_nShaders = 0;
};
