
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.


#include "PreComplie.h"
#include "GameObject.h"

CGameObject::CGameObject(const tstring& name) : Object(name)
{
	m_xmf4x4World = Radar::Math::Identity();
}

CGameObject::~CGameObject()
{
}

const bool CGameObject::IsVisible(CCamera *pCamera) const
{
	return true;
}

void CGameObject::Update(const float fTimeElapsed)
{
}

void CGameObject::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	if (IsVisible(pCamera) == false)
		return;
}

void CGameObject::SetPosition(const float x, const float y, const float z)
{
	m_xmf4x4World._41 = x;
	m_xmf4x4World._42 = y;
	m_xmf4x4World._43 = z;
}

void CGameObject::SetPosition(const XMFLOAT3 xmf3Position)
{
	SetPosition(xmf3Position.x, xmf3Position.y, xmf3Position.z);
}

const XMFLOAT3 CGameObject::GetPosition() const
{
	return(XMFLOAT3(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43));
}

const XMFLOAT3 CGameObject::GetLook() const
{
	XMFLOAT3 xm3{ m_xmf4x4World._31, m_xmf4x4World._32, m_xmf4x4World._33 };
	return Radar::Math::Normalize(xm3);
}

const XMFLOAT3 CGameObject::GetUp()const
{
	XMFLOAT3 xm3{ m_xmf4x4World._21, m_xmf4x4World._22, m_xmf4x4World._23 };
	return Radar::Math::Normalize(xm3);
}

const XMFLOAT3 CGameObject::GetRight()const
{
	XMFLOAT3 xm3{ m_xmf4x4World._11, m_xmf4x4World._12, m_xmf4x4World._13 };
	return Radar::Math::Normalize(xm3);
}

void CGameObject::MoveStrafe(const float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Right = GetRight();
	xmf3Position = Radar::Math::Add(xmf3Position, xmf3Right, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

void CGameObject::MoveUp(const float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Up = GetUp();
	xmf3Position = Radar::Math::Add(xmf3Position, xmf3Up, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

void CGameObject::MoveForward(const float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Look = GetLook();
	xmf3Position = Radar::Math::Add(xmf3Position, xmf3Look, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

void CGameObject::Rotate(const float fPitch, const float fYaw, const float fRoll)
{
	XMMATRIX mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians(fPitch), XMConvertToRadians(fYaw), XMConvertToRadians(fRoll));
	m_xmf4x4World = Radar::Math::Multiply(mtxRotate, m_xmf4x4World);
}

void CGameObject::Rotate(XMFLOAT3 *pxmf3Axis, const float fAngle)
{
	XMMATRIX mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(pxmf3Axis), XMConvertToRadians(fAngle));
	m_xmf4x4World = Radar::Math::Multiply(mtxRotate, m_xmf4x4World);
}