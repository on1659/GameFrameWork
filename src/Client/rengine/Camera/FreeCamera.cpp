
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once
#include "PreComplie.h"
#include "FreeCamera.h"
#include "Camera.h"


CFreeCamera::CFreeCamera(const tstring& name) : CCamera(name)
{
}

WARP_RESULT_ENUM CFreeCamera::Start()
{
	//m_pGBufferUnpackingBuffer = Radar::Util::CreateBuffer(sizeof(GBUFFER_UNPACKING_DATA), 1, nullptr, D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DEFAULT, 0);
	return CCamera::Start();
}
WARP_RESULT_ENUM CFreeCamera::Release()
{
	return CCamera::Release();
}

void CFreeCamera::Rotate(const float& x, const float& y, const float& z) {
	XMMATRIX xmmtxRotate;
	if (x != 0.0f)
	{
		//카메라의 로컬 x-축을 기준으로 회전하는 행렬을 생성한다. 고개를 끄떡이는 동작이다.
		xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Right), (float)XMConvertToRadians(x));
		//카메라의 로컬 x-축, y-축, z-축을 회전한다.
		XMStoreFloat3(&m_xmf3Right, XMVector3TransformNormal(XMLoadFloat3(&m_xmf3Right), xmmtxRotate));
		XMStoreFloat3(&m_xmf3Up, XMVector3TransformNormal(XMLoadFloat3(&m_xmf3Up), xmmtxRotate));
		XMStoreFloat3(&m_xmf3Look, XMVector3TransformNormal(XMLoadFloat3(&m_xmf3Look), xmmtxRotate));
	}
	if (y != 0.0f)
	{
		//플레이어의 로컬 y-축을 기준으로 회전하는 행렬을 생성한다.
		xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Up), (float)XMConvertToRadians(y));
		//카메라의 로컬 x-축, y-축, z-축을 회전한다.
		XMStoreFloat3(&m_xmf3Right, XMVector3TransformNormal(XMLoadFloat3(&m_xmf3Right), xmmtxRotate));
		XMStoreFloat3(&m_xmf3Up, XMVector3TransformNormal(XMLoadFloat3(&m_xmf3Up), xmmtxRotate));
		XMStoreFloat3(&m_xmf3Look, XMVector3TransformNormal(XMLoadFloat3(&m_xmf3Look), xmmtxRotate));
	}
	if (z != 0.0f)
	{
		//플레이어의 로컬 z-축을 기준으로 회전하는 행렬을 생성한다.
		xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Look), (float)XMConvertToRadians(z));
		//카메라의 로컬 x-축, y-축, z-축을 회전한다.
		XMStoreFloat3(&m_xmf3Right, XMVector3TransformNormal(XMLoadFloat3(&m_xmf3Right), xmmtxRotate));
		XMStoreFloat3(&m_xmf3Up, XMVector3TransformNormal(XMLoadFloat3(&m_xmf3Up), xmmtxRotate));
		XMStoreFloat3(&m_xmf3Look, XMVector3TransformNormal(XMLoadFloat3(&m_xmf3Look), xmmtxRotate));
	}
}

void CFreeCamera::Update(const float& fTime) {
	BaseMove(fTime);
	BaseMouse(fTime);
	UpdateShaderState();
}

//상수버퍼 갱신
void CFreeCamera::UpdateShaderState() {
	//정보 갱신
	XMMATRIX xmMtxProjection = (XMLoadFloat4x4(&m_xmf4x4Projection));
	UpdateViewMatrix();

	XMMATRIX xmMtxView = XMLoadFloat4x4(&m_xmf4x4View);

	XMStoreFloat4x4(&m_stCameraBufferData.m_xmf4x4ViewProjection, XMMatrixTranspose(XMMatrixMultiply(xmMtxView, xmMtxProjection)));
	m_stCameraBufferData.m_CameraPos = XMFLOAT4(m_xmf3Pos.x, m_xmf3Pos.y, m_xmf3Pos.z, 1.0f);
	//정보 갱신

	//상수버퍼 업데이트
	//gDeviceContext->UpdateSubresource(m_pViewProjectionBuffer, 0, NULL, &m_stCameraBufferData, 0, 0);

	//--------------------------------deferred lighting--------------------------------
	XMFLOAT4 xmf4PerspectiveValues;
	xmf4PerspectiveValues.x = 1.0f / m_xmf4x4Projection.m[0][0];
	xmf4PerspectiveValues.y = 1.0f / m_xmf4x4Projection.m[1][1];
	xmf4PerspectiveValues.z = m_xmf4x4Projection.m[3][2];
	xmf4PerspectiveValues.w = -m_xmf4x4Projection.m[2][2];

	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(GetWorldMatrix()));

	GBUFFER_UNPACKING_DATA data{ xmf4PerspectiveValues , xmf4x4World };
	//gDeviceContext->UpdateSubresource(m_pGBufferUnpackingBuffer, 0, NULL, &data, 0, 0);
	//--------------------------------deferred lighting--------------------------------

	SetShaderState();

}

void CFreeCamera::SetShaderState()
{
	//gDeviceContext->VSSetConstantBuffers(VS_CB_SLOT_CAMERA_PROJECTION, 1, &m_pViewProjectionBuffer);
	//gDeviceContext->GSSetConstantBuffers(GS_CB_SLOT_CAMERA_PROJECTION, 1, &m_pViewProjectionBuffer);
	//gDeviceContext->DSSetConstantBuffers(DS_CB_SLOT_CAMERA_PROJECTION, 1, &m_pViewProjectionBuffer);

	//gDeviceContext->PSSetConstantBuffers(UNPACK_BUFFER_SLOT, 1, &m_pGBufferUnpackingBuffer);

}

