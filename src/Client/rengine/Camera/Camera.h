
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once


//#define _FIRST_
class CCamera : public CDXObject
{
	static CCamera* CamPtr;

public:

	CCamera(const tstring& name = _XTT("Camera"));
	~CCamera() { }
	CCamera* operator()() { return CamPtr; }
	void operator=(CCamera* ptr) { CamPtr = ptr; }

	//--------------------------- DX Object ----------------------------

	virtual WARP_RESULT_ENUM Start() override;
	virtual WARP_RESULT_ENUM Release() override;

	virtual void SetShaderState() {};
	virtual void CleanShaderState() {}
	void UpdateShaderState() {}

	//--------------------------- DX Object ----------------------------

	bool IsInFrustum(const BoundingBox& boundingBox);			//FrustumCulling

	//---------------------------------------카메라 조정---------------------------------
	void SetLookAt(XMFLOAT3 xmvPos, XMFLOAT3 xmvLookAt, XMFLOAT3 xmvUp);
	void SetScissorRect(LONG xLeft, LONG yTop, LONG xRight, LONG yBottom);

	virtual void SetPosition(const XMVECTOR& xmPosition);
	virtual void Rotate(const float& x = 0.0f, const float& y = 0.0f, const float& z = 0.0f) {}

	virtual void Update(const float& fTimeElapsed) {}
	virtual void ProcessInput(const float& fTimeElapsed) {}



	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList);


	//--------------------------------------- Camera Buffer ------------------------------//
	void CreatesProjectionMatrix(const float& fFov, const float& fRatio, const float& fNear, const float& fFar); //Projectino Create
	void UpdateViewMatrix();
	void SetViewport(const DWORD& xTopLeft, const DWORD& yTopLeft, const DWORD& nWidth,
		const DWORD& nHeight, const float& fMinZ, const float& fMaxZ);							//ViewPort
	virtual void SetViewportsAndScissorRects(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	//--------------------------------------- Camera Buffer ------------------------------//

	//-------------------------- Player ------------------------------------//
		//void SetPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; }
		//CPlayer* GetPlayer() { return m_pPlayer; }
	//-------------------------- Player ------------------------------------//


	D3DBuffer* GetViewProjectionBuffer() { return m_pViewProjectionBuffer.Get(); }
	D3DBuffer* GetGBufferUnpackingBuffer() { return m_pGBufferUnpackingBuffer.Get(); }
	
	virtual XMMATRIX& GetWorldMatrix() final;

	virtual XMMATRIX& GetViewMatrix() final;

	virtual XMMATRIX& GetProjectionMatrix() final;

	virtual DX_VIEWPORT& GetViewport() final;

	virtual XMVECTOR& GetPosition() final;

	const XMFLOAT3& GetPositionXMFLOAT3() const { return m_xmf3Pos; }
	void SetPosition(const XMFLOAT3& f3) { m_xmf3Pos = f3; }
	RECT GetClientSize() const { return m_rcClient; };


protected:

	const static int DEFAULT_CAM_SPEED = 5;

	void BaseMove(const float& fTime);
	void BaseMouse(const float& fTime);

	//--------------------------- AABB Frustum --------------------------- //
		BoundingFrustum						m_OriBoundingFrustum;
		BoundingFrustum						m_BoundingFrustum;
	//--------------------------- AABB Frustum --------------------------- //
		RECT								m_rcClient;						//Windows Size
	//CPlayer*							m_pPlayer;						//Player

	//----------------------- Camera Const Buffer ----------------------- //
		stCameraBuffer						m_stCameraBufferData;
		ComPtr<D3DBuffer>					m_pViewProjectionBuffer;

		XMFLOAT4X4							m_xmf4x4View;
		XMFLOAT4X4							m_xmf4x4Projection;
	//----------------------- Camera Const Buffer ----------------------- //


	// //----------------------------- ViewPort----------------------------- //
		DX_VIEWPORT							m_d3dViewport;
		D3D12_RECT							m_d3dScissorRect;
	// //----------------------------- ViewPort----------------------------- //

	//--  WorldMatrix를 가지고 Camera look,up,right,position Vector를 만든다. --//
		XMFLOAT3							m_xmf3Right;
		XMFLOAT3							m_xmf3Up;
		XMFLOAT3							m_xmf3Look;
		XMFLOAT3							m_xmf3Pos;

	//----------------------------------- Deferred light --------------------//
		GBUFFER_UNPACKING_DATA				m_GBufferUnpackingData;
		ComPtr<D3DBuffer>					m_pGBufferUnpackingBuffer;
	//----------------------------------- Deferred light --------------------//
};
