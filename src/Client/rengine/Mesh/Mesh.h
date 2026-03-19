//------------------------------------------------------- ----------------------
// File: Mesh.h
//-----------------------------------------------------------------------------

// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.


#pragma once


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CMesh : public CDXObject
{
public:
    CMesh(const tstring& name = _XTT("Mesh"));

    virtual ~CMesh();

	virtual WARP_RESULT_ENUM Initialize() override;

	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList = nullptr) override;

	virtual	WARP_RESULT_ENUM ReleaseUploadBuffers() override;

protected:
	ComPtr<ID3D12Resource>			m_pd3dVertexBuffer;
	ComPtr<ID3D12Resource>			m_pd3dVertexUploadBuffer;

	ComPtr<ID3D12Resource>			m_pd3dIndexBuffer;
	ComPtr<ID3D12Resource>			m_pd3dIndexUploadBuffer;

	D3D12_VERTEX_BUFFER_VIEW		m_d3dVertexBufferView;
	D3D12_INDEX_BUFFER_VIEW			m_d3dIndexBufferView;

	D3D12_PRIMITIVE_TOPOLOGY		m_d3dPrimitiveTopology;

	UINT							m_nVertices;
	VertexPositionColor				*m_pVertices;

	UINT							m_nSlot;
	UINT							m_nStride;
	UINT							m_nOffset;

	UINT							m_nIndices;
	UINT							*m_pnIndices;

	UINT							m_nStartIndex;
	UINT							m_nBaseVertex;
};

class CCubeMeshDiffused : public CMesh
{
public:
	CCubeMeshDiffused(const tstring name = _XTT("CubeMeshDiffused"), float fWidth = 2.0f, float fHeight = 2.0f, float fDepth = 2.0f);
	virtual ~CCubeMeshDiffused();
};

class CSphereMeshDiffused : public CMesh
{
public:
	CSphereMeshDiffused(const tstring name = _XTT("SphereMeshDiffused"), float fRadius=2.0f, int nSlices=20, int nStacks=20);
	virtual ~CSphereMeshDiffused();
};
