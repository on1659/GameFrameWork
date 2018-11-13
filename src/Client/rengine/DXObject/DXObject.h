
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

class CDXObject : public Object
{
public:

	CDXObject(const tstring& name = _XTT("DXObject"));

	virtual ~CDXObject();

	virtual	WARP_RESULT_ENUM ReleaseUploadBuffers();

	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList = nullptr);


public:
	BoundingBox* GetBoundingBox() { return (&m_xmBoundingBox); }

protected:
	BoundingBox						m_xmBoundingBox;

/*

	virtual WARP_RESULT_ENUM Release() override;


	virtual void OnPrepareRender() {}
	virtual void Render() {}
	virtual void InstanceRender(const UINT& nInstance = 1u) {}
	virtual void LateRender() {}
	
	virtual void Update(const float& fTime = 0.0f) {}
	virtual void LateUpdate(const float& fTime = 0.0f) {}

	virtual void CreateConstBuffer() {}
	virtual void UpdateConstBuffer() {}
	virtual void CleanConstBuffer()  {}

	virtual void SetShaderState(){}
	virtual void ClearShaderState(){}
	virtual void UpdateShaderState(){}


protected:
	UINT							 m_uBindFlag;
	ID3D11RasterizerState			*m_pd3dRasterizerState;
	ID3D11DepthStencilState			*m_pd3dDepthStencilState;
	ID3D11BlendState				*m_pd3dBlendState;
	std::string						 m_strBlendstate;

	void SetBindFlag(const UINT& flag = SHADER_BIND_NOT) { m_uBindFlag = flag; }
	const UINT& GetBindFlag() { return m_uBindFlag; }


	virtual WARP_RESULT_ENUM CreateBlendState(const D3D11_BLEND_DESC& desc);
	virtual WARP_RESULT_ENUM CreateBlendState();
	virtual WARP_RESULT_ENUM CreateDepthStencilState();
	virtual WARP_RESULT_ENUM CreateRasterizerState(const D3D11_CULL_MODE& cullMode = D3D11_CULL_NONE, const D3D11_FILL_MODE& fillMode = D3D11_FILL_SOLID);

	void SetBlendState(ID3D11BlendState *pd3dBlendState);
	void SetBlendState(const std::string& name);
	const std::string& GetBlendStatePath() { return m_strBlendstate; }

	ID3D11RasterizerState			*m_pd3dPrevRasterizerState;
	ID3D11DepthStencilState			*m_pd3dPrevDepthStencilState;
	ID3D11BlendState				*m_pd3dPrevBlendState;
	UINT							 uPrevDS;
	float							*fPrevBS;
	UINT							 uPrevBS;
*/

};

