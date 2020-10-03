
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

class CCamera;

class CGameObject : public Object

{
public:
	CGameObject();
    virtual ~CGameObject();

public:
	XMFLOAT4X4						m_xmf4x4World;

	virtual void Update(const float fTimeElapsed);
	virtual void OnPrepareRender() { }
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera = nullptr);

	const XMFLOAT3 GetPosition() const;
	const XMFLOAT3 GetLook() const;
	const XMFLOAT3 GetUp() const;
	const XMFLOAT3 GetRight() const;

	void SetPosition(const float x, const float y, const float z);
	void SetPosition(const XMFLOAT3 xmf3Position);

	void MoveStrafe(const float fDistance = 1.0f);
	void MoveUp(const float fDistance = 1.0f);
	void MoveForward(const float fDistance = 1.0f);

	void Rotate(const float fPitch = 10.0f, const float fYaw = 10.0f, const float fRoll = 10.0f);
	void Rotate(XMFLOAT3 *pxmf3Axis, const float fAngle);

	const bool IsVisible(CCamera *pCamera = nullptr) const;
};
