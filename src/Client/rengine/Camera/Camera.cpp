
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.
 
#include "PreComplie.h"
#include "Camera.h"

CCamera::CCamera(const tstring& name)
	: CDXObject(name)
	, m_pGBufferUnpackingBuffer(nullptr)
	//, m_pPlayer(nullptr)
{
	m_pViewProjectionBuffer = nullptr;					//Camera Const Buffer

	XMStoreFloat4x4(&m_xmf4x4View, XMMatrixIdentity());
	XMStoreFloat4x4(&m_xmf4x4Projection, XMMatrixIdentity());

	m_xmf4x4View = Radar::Math::Identity();
	m_xmf4x4Projection = Radar::Math::Identity();
	m_d3dViewport = { 0, 0, FRAME_BUFFER_WIDTH , FRAME_BUFFER_HEIGHT, 0.0f, 1.0f };
	m_d3dScissorRect = { 0, 0, FRAME_BUFFER_WIDTH , FRAME_BUFFER_HEIGHT };
	Start();

}

WARP_RESULT_ENUM CCamera::Start()
{
	//변수 초기화
	XMStoreFloat4x4(&m_xmf4x4View, XMMatrixIdentity());
	////ProjectionMtx 제작
	//GenerateProjectionMatrix(fFov, fWidth / fHeight, fNear, fFar);

	m_xmf3Right = XMFLOAT3{ 1.0f, 0.0f, 0.0f };
	m_xmf3Up = XMFLOAT3{ 0.0f, 1.0f, 0.0f };
	m_xmf3Look = XMFLOAT3{ 0.0f, 0.0f, 1.0f };
	m_xmf3Pos = XMFLOAT3{ 0.0f, 0.0f, 0.0f };

	return CWARPResult::OK();
}

WARP_RESULT_ENUM CCamera::Release()
{
	if (m_pViewProjectionBuffer) m_pViewProjectionBuffer->Release();

	return CWARPResult::OK();
}

void CCamera::SetPosition(const XMVECTOR& xmPosition)
{
	XMStoreFloat3(&m_xmf3Pos, xmPosition);	//바뀐 벡터 설정 후 
	UpdateViewMatrix();						//ViewMatrix 업데이트
}

void CCamera::CreatesProjectionMatrix(const float& fFov, const float& fRatio, const float& fNear, const float& fFar)
{
	//XMStoreFloat4x4(&m_xmf4x4Projection, XMMatrixPerspectiveFovLH(fFov, fRatio, fNear, fFar));
	//m_xmf4x4Projection = Radar::Math::PerspectiveFovLH(XMConvertToRadians(fFov), fRatio, fNear, fFar);
	m_xmf4x4Projection = Radar::Math::PerspectiveFovLH(XMConvertToRadians(fFov), fRatio, fNear, fFar);

	//create oriented frustum
	BoundingFrustum::CreateFromMatrix(m_OriBoundingFrustum, XMLoadFloat4x4(&m_xmf4x4Projection));
}

void CCamera::SetScissorRect(LONG xLeft, LONG yTop, LONG xRight, LONG yBottom)
{
	m_d3dScissorRect.left = xLeft;
	m_d3dScissorRect.top = yTop;
	m_d3dScissorRect.right = xRight;
	m_d3dScissorRect.bottom = yBottom;
}

void CCamera::UpdateViewMatrix()
{
	XMStoreFloat3(&m_xmf3Look, XMVector3Normalize(XMLoadFloat3(&m_xmf3Look)));
	XMStoreFloat3(&m_xmf3Right, XMVector3Cross(XMLoadFloat3(&m_xmf3Up), XMLoadFloat3(&m_xmf3Look)));
	XMStoreFloat3(&m_xmf3Right, XMVector3Normalize(XMLoadFloat3(&m_xmf3Right)));
	XMStoreFloat3(&m_xmf3Up, XMVector3Cross(XMLoadFloat3(&m_xmf3Look), XMLoadFloat3(&m_xmf3Right)));
	XMStoreFloat3(&m_xmf3Up, XMVector3Normalize(XMLoadFloat3(&m_xmf3Up)));

	m_xmf4x4View._11 = m_xmf3Right.x;
	m_xmf4x4View._12 = m_xmf3Up.x;
	m_xmf4x4View._13 = m_xmf3Look.x;

	m_xmf4x4View._21 = m_xmf3Right.y;
	m_xmf4x4View._22 = m_xmf3Up.y;
	m_xmf4x4View._23 = m_xmf3Look.y;

	m_xmf4x4View._31 = m_xmf3Right.z;
	m_xmf4x4View._32 = m_xmf3Up.z;
	m_xmf4x4View._33 = m_xmf3Look.z;

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, XMVector3Dot(XMLoadFloat3(&m_xmf3Pos), XMLoadFloat3(&m_xmf3Right)));
	m_xmf4x4View._41 = -xmfPos.x;

	XMStoreFloat3(&xmfPos, XMVector3Dot(XMLoadFloat3(&m_xmf3Pos), XMLoadFloat3(&m_xmf3Up)));
	m_xmf4x4View._42 = -xmfPos.x;

	XMStoreFloat3(&xmfPos, XMVector3Dot(XMLoadFloat3(&m_xmf3Pos), XMLoadFloat3(&m_xmf3Look)));
	m_xmf4x4View._43 = -xmfPos.x;

	//update frustum
	m_OriBoundingFrustum.Transform(m_BoundingFrustum, GetWorldMatrix());
}

bool CCamera::IsInFrustum(const BoundingBox& boundingBox)
{
	return (m_BoundingFrustum.Intersects(boundingBox));
}


void CCamera::SetLookAt(XMFLOAT3 xmvPos, XMFLOAT3 xmvLookAt, XMFLOAT3 xmvUp)
{
	m_xmf4x4View = Radar::Math::LookAtLH(xmvPos, xmvLookAt, xmvUp);

	m_xmf3Pos	= xmvPos;
	m_xmf3Right = XMFLOAT3(m_xmf4x4View._11, m_xmf4x4View._21, m_xmf4x4View._31);
	m_xmf3Up	= XMFLOAT3(m_xmf4x4View._12, m_xmf4x4View._22, m_xmf4x4View._32);
	m_xmf3Look  = XMFLOAT3(m_xmf4x4View._13, m_xmf4x4View._23, m_xmf4x4View._33);
}

void CCamera::SetViewport(const DWORD& xTopLeft, const DWORD& yTopLeft, const DWORD& nWidth, const DWORD& nHeight, const float& fMinZ, const float& fMaxZ)
{
	////0,0, r, b
	m_d3dViewport.TopLeftX = float(xTopLeft);
	m_d3dViewport.TopLeftY = float(yTopLeft);
	m_d3dViewport.Width = float(nWidth);
	m_d3dViewport.Height = float(nHeight);
	m_d3dViewport.MinDepth = fMinZ;
	m_d3dViewport.MaxDepth = fMaxZ;

	// SetScissorRect((LONG)xTopLeft, (LONG)yTopLeft, (LONG)nWidth, (LONG)nHeight);
}

void CCamera::SetViewportsAndScissorRects(ID3D12GraphicsCommandList *pd3dCommandList)
{
	pd3dCommandList->RSSetViewports(1, &m_d3dViewport);
	pd3dCommandList->RSSetScissorRects(1, &m_d3dScissorRect);
}

void CCamera::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	XMFLOAT4X4 xmf4x4View;
	XMStoreFloat4x4(&xmf4x4View, XMMatrixTranspose(XMLoadFloat4x4(&m_xmf4x4View)));
	pd3dCommandList->SetGraphicsRoot32BitConstants(1, 16, &xmf4x4View, 0);

	XMFLOAT4X4 xmf4x4Projection;
	XMStoreFloat4x4(&xmf4x4Projection, XMMatrixTranspose(XMLoadFloat4x4(&m_xmf4x4Projection)));
	pd3dCommandList->SetGraphicsRoot32BitConstants(1, 16, &xmf4x4Projection, 16);

	UpdateViewMatrix();
}

void CCamera::BaseMove(const float& fTime)
{
	XMVECTOR xmvShift = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

	if (INPUT->KeyDown(WARP_KEY::WP_W) || INPUT->KeyDown(WARP_KEY::WP_UP))
		xmvShift += XMLoadFloat3(&m_xmf3Look);
	if (INPUT->KeyDown(WARP_KEY::WP_S) || INPUT->KeyDown(WARP_KEY::WP_DOWN))
		xmvShift -= XMLoadFloat3(&m_xmf3Look);

	if (INPUT->KeyDown(WARP_KEY::WP_A) || INPUT->KeyDown(WARP_KEY::WP_LEFT)) 	 xmvShift -= XMLoadFloat3(&m_xmf3Right);
	if (INPUT->KeyDown(WARP_KEY::WP_D) || INPUT->KeyDown(WARP_KEY::WP_RIGHT))	 xmvShift += XMLoadFloat3(&m_xmf3Right);
	if (INPUT->KeyDown(WARP_KEY::WP_X)) 								 xmvShift += XMLoadFloat3(&m_xmf3Up);
	if (INPUT->KeyDown(WARP_KEY::WP_Z)) 								 xmvShift -= XMLoadFloat3(&m_xmf3Up);

	XMVector3Normalize(xmvShift);

	float fSpeedUp = DEFAULT_CAM_SPEED;

	if (INPUT->KeyDown(WARP_KEY::WP_LSHIFT))
		fSpeedUp *= 10.0f;

	XMStoreFloat3(&m_xmf3Pos, XMLoadFloat3(&m_xmf3Pos) + ((xmvShift * fSpeedUp) * fTime));
}
void CCamera::BaseMouse(const float& fTime)
{
	if (INPUT->GetOldcxDelta() || INPUT->GetOldcyDelta())
	{
		/*cxDelta는 y-축의 회전을 나타내고 cyDelta는 x-축의 회전을 나타낸다. 오른쪽 마우스 버튼이 눌려진 경우 cxDelta는 z-축의 회전을 나타낸다.*/
		if (INPUT->KeyDown(WARP_KEY::WP_RBUTTON))
			Rotate(INPUT->GetOldcyDelta(), 0.0f, -INPUT->GetOldcxDelta());
		else
			Rotate(INPUT->GetOldcyDelta(), INPUT->GetOldcxDelta(), 0.0f);
	}
}

void CCamera::UpdateShaderState()
{

}
