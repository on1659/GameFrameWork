
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#include "PreComplie.h"
#include "Mesh.h"

CMesh::CMesh(const tstring& name) : CDXObject(name)
{
	Initialize();
}

WARP_RESULT_ENUM CMesh::Initialize()
{
	m_pd3dVertexBuffer = nullptr;
	m_pd3dVertexUploadBuffer = nullptr;
	m_pd3dIndexBuffer = nullptr;
	m_pd3dIndexUploadBuffer = nullptr;
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_nVertices = 0;
	m_pVertices = nullptr;
	m_nSlot = 0;
	m_nStride = 0;
	m_nOffset = 0;
	m_nIndices = 0;
	m_pnIndices = nullptr;
	m_nStartIndex = 0;
	m_nBaseVertex = 0;
	return WARP_RESULT_ENUM::OK;
}

CMesh::~CMesh()
{
	//if (m_pd3dVertexBuffer) m_pd3dVertexBuffer->Release();
	//if (m_pd3dIndexBuffer) m_pd3dIndexBuffer->Release();
	//if (m_pd3dVertexUploadBuffer) m_pd3dVertexUploadBuffer->Release();
	//if (m_pd3dIndexUploadBuffer) m_pd3dIndexUploadBuffer->Release();

	if (m_pVertices) delete[] m_pVertices;
	if (m_pnIndices) delete[] m_pnIndices;
}

WARP_RESULT_ENUM CMesh::ReleaseUploadBuffers()
{
	//if (m_pd3dVertexUploadBuffer) m_pd3dVertexUploadBuffer->Release();
	//if (m_pd3dIndexUploadBuffer) m_pd3dIndexUploadBuffer->Release();
	//m_pd3dVertexUploadBuffer = NULL;
	//m_pd3dIndexUploadBuffer = NULL;

	return WARP_RESULT_ENUM::OK;
};

void CMesh::Render(ID3D12GraphicsCommandList *pd3dCommandList)
{
	__super::Render(pd3dCommandList);

	pd3dCommandList->IASetPrimitiveTopology(m_d3dPrimitiveTopology);
	pd3dCommandList->IASetVertexBuffers(m_nSlot, 1, &m_d3dVertexBufferView);

	if (m_pd3dIndexBuffer)		// 인덱스 버퍼가 있다면
	{
		pd3dCommandList->IASetIndexBuffer(&m_d3dIndexBufferView);
		pd3dCommandList->DrawIndexedInstanced(m_nIndices, 1, 0, 0, 0);
	}
	else
	{
		pd3dCommandList->DrawInstanced(m_nVertices, 1, m_nOffset, 0);
	}
}

//////////////////////////////////////////////////////////////////////////////////
//
CCubeMeshDiffused::CCubeMeshDiffused(const tstring name, float fWidth, float fHeight, float fDepth) : CMesh(name)
{
	m_nVertices = 8;
	m_nStride = sizeof(VertexPositionColor);
	m_nOffset = 0;
	m_nSlot = 0;
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	float fx = fWidth*0.5f, fy = fHeight*0.5f, fz = fDepth*0.5f;

	VertexPositionColor *pVertices = new VertexPositionColor[m_nVertices];

	pVertices[0] = VertexPositionColor{ XMFLOAT3(-fx, +fy, -fz), RANDOM_COLOR };
	pVertices[1] = VertexPositionColor{ XMFLOAT3(+fx, +fy, -fz), RANDOM_COLOR };
	pVertices[2] = VertexPositionColor{ XMFLOAT3(+fx, +fy, +fz), RANDOM_COLOR };
	pVertices[3] = VertexPositionColor{ XMFLOAT3(-fx, +fy, +fz), RANDOM_COLOR };
	pVertices[4] = VertexPositionColor{ XMFLOAT3(-fx, -fy, -fz), RANDOM_COLOR };
	pVertices[5] = VertexPositionColor{ XMFLOAT3(+fx, -fy, -fz), RANDOM_COLOR };
	pVertices[6] = VertexPositionColor{ XMFLOAT3(+fx, -fy, +fz), RANDOM_COLOR };
	pVertices[7] = VertexPositionColor{ XMFLOAT3(-fx, -fy, +fz), RANDOM_COLOR };

	m_pd3dVertexBuffer = Radar::Util::CreateBuffer(pVertices, m_nStride * m_nVertices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);

	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

	m_pVertices = pVertices;

	m_nIndices = 36;
	m_pnIndices = new UINT[m_nIndices];

	m_pnIndices[0] = 3; m_pnIndices[1] = 1; m_pnIndices[2] = 0;
	m_pnIndices[3] = 2; m_pnIndices[4] = 1; m_pnIndices[5] = 3;
	m_pnIndices[6] = 0; m_pnIndices[7] = 5; m_pnIndices[8] = 4;
	m_pnIndices[9] = 1; m_pnIndices[10] = 5; m_pnIndices[11] = 0;
	m_pnIndices[12] = 3; m_pnIndices[13] = 4; m_pnIndices[14] = 7;
	m_pnIndices[15] = 0; m_pnIndices[16] = 4; m_pnIndices[17] = 3;
	m_pnIndices[18] = 1; m_pnIndices[19] = 6; m_pnIndices[20] = 5;
	m_pnIndices[21] = 2; m_pnIndices[22] = 6; m_pnIndices[23] = 1;
	m_pnIndices[24] = 2; m_pnIndices[25] = 7; m_pnIndices[26] = 6;
	m_pnIndices[27] = 3; m_pnIndices[28] = 7; m_pnIndices[29] = 2;
	m_pnIndices[30] = 6; m_pnIndices[31] = 4; m_pnIndices[32] = 5;
	m_pnIndices[33] = 7; m_pnIndices[34] = 4; m_pnIndices[35] = 6;

	m_pd3dIndexBuffer = ::Radar::Util::CreateBuffer(m_pnIndices, sizeof(UINT) * m_nIndices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pd3dIndexUploadBuffer);

	m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
	m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices;

	m_xmBoundingBox = BoundingBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fx, fy, fz));
}

CCubeMeshDiffused::~CCubeMeshDiffused()
{
}

CSphereMeshDiffused::CSphereMeshDiffused(const tstring name, float fRadius, int nSlices, int nStacks) : CMesh(name)
{
	m_nStride = sizeof(VertexPositionColor);
	m_d3dPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_nVertices = 2 + (nSlices * (nStacks - 1));

	VertexPositionColor *pVertices = new VertexPositionColor[m_nVertices];

	float fDeltaPhi = float(XM_PI / nStacks);
	float fDeltaTheta = float((2.0f * XM_PI) / nSlices);

	int k = 0;
	pVertices[k++] = VertexPositionColor{XMFLOAT3(0.0f, +fRadius, 0.0f), RANDOM_COLOR};	
	float theta_i, phi_j;
	for (int j = 1; j < nStacks; j++)
	{
		phi_j = fDeltaPhi * j;
		for (int i = 0; i < nSlices; i++)
		{
			theta_i = fDeltaTheta * i;
			pVertices[k++] = VertexPositionColor{ XMFLOAT3(fRadius*sinf(phi_j)*cosf(theta_i), fRadius*cosf(phi_j), fRadius*sinf(phi_j)*sinf(theta_i)), RANDOM_COLOR };
		}
	}
	pVertices[k] = VertexPositionColor{ XMFLOAT3(0.0f, -fRadius, 0.0f), RANDOM_COLOR };

	m_pd3dVertexBuffer = Radar::Util::CreateBuffer(pVertices, m_nStride * m_nVertices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);

	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

	m_pVertices = pVertices;

	m_nIndices = (nSlices * 3) * 2 + (nSlices * (nStacks - 2) * 3 * 2);

	m_pnIndices = new UINT[m_nIndices];

	k = 0;
	for (int i = 0; i < nSlices; i++)
	{
		m_pnIndices[k++] = 0;
		m_pnIndices[k++] = 1 + ((i + 1) % nSlices);
		m_pnIndices[k++] = 1 + i;
	}
	for (int j = 0; j < nStacks-2; j++)
	{
		for (int i = 0; i < nSlices; i++)
		{
			m_pnIndices[k++] = 1 + (i + (j * nSlices));
			m_pnIndices[k++] = 1 + (((i + 1) % nSlices) + (j * nSlices));
			m_pnIndices[k++] = 1 + (i + ((j + 1) * nSlices));
			m_pnIndices[k++] = 1 + (i + ((j + 1) * nSlices));
			m_pnIndices[k++] = 1 + (((i + 1) % nSlices) + (j * nSlices));
			m_pnIndices[k++] = 1 + (((i + 1) % nSlices) + ((j + 1) * nSlices));
		}
	}
	for (int i = 0; i < nSlices; i++)
	{
		m_pnIndices[k++] = (m_nVertices - 1);
		m_pnIndices[k++] = ((m_nVertices - 1) - nSlices) + i;
		m_pnIndices[k++] = ((m_nVertices - 1) - nSlices) + ((i + 1) % nSlices);
	}

	m_pd3dIndexBuffer = Radar::Util::CreateBuffer(m_pnIndices, sizeof(UINT) * m_nIndices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pd3dIndexUploadBuffer);

	m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
	m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices;

	m_xmBoundingBox = BoundingBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fRadius, fRadius, fRadius));
}

CSphereMeshDiffused::~CSphereMeshDiffused()
{
}
