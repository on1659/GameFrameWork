
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

#include "PreComplie.h"
#include "DXObject.h"

CDXObject::CDXObject(const tstring& name)
	: Object(name)
	//, m_uBindFlag(SHADER_BIND_NOT)
	//, m_strBlendstate("")
	//, m_pd3dRasterizerState(nullptr)
	//, m_pd3dDepthStencilState(nullptr)
	//, m_pd3dBlendState(nullptr)
{
}

CDXObject::~CDXObject()
{
	// if (m_pd3dBlendState)		m_pd3dBlendState->Release();
	// if (m_pd3dRasterizerState)   m_pd3dRasterizerState->Release();
	// if (m_pd3dDepthStencilState) m_pd3dDepthStencilState->Release();
	// 
	// m_pd3dDepthStencilState = nullptr;
	// m_pd3dRasterizerState = nullptr;
	// m_pd3dRasterizerState = nullptr;
}

WARP_RESULT_ENUM CDXObject::ReleaseUploadBuffers()
{
	return WARP_RESULT_ENUM::OK;
}

void CDXObject::Render(ID3D12GraphicsCommandList *pd3dCommandList)
{

}

/*
	WARP_RESULT_ENUM CDXObject::Release()
	{
		Object::Release();

		if (m_pd3dBlendState)		 m_pd3dBlendState->Release();
		if (m_pd3dRasterizerState)   m_pd3dRasterizerState->Release();
		if (m_pd3dDepthStencilState) m_pd3dDepthStencilState->Release();

		m_pd3dDepthStencilState = nullptr;
		m_pd3dRasterizerState = nullptr;
		m_pd3dRasterizerState = nullptr;

		return WARP_RESULT_ENUM::OK;
	}


	WARP_RESULT_ENUM CDXObject::CreateBlendState()
	{
		SAFE_RELEASE(m_pd3dBlendState);

		CDXObject::SetBlendState("Default");
		return WARP_RESULT_ENUM::OK;
	}

	WARP_RESULT_ENUM CDXObject::CreateBlendState(const D3D11_BLEND_DESC& desc)
	{
		SAFE_RELEASE(m_pd3dBlendState);
		gDevice->CreateBlendState(&desc, &m_pd3dBlendState);
		if(m_pd3dBlendState)
			return CWARPResult::FAIL_CREATE_BS(ERR_INFO);

		return WARP_RESULT_ENUM::OK;
	}

	WARP_RESULT_ENUM CDXObject::CreateRasterizerState(const D3D11_CULL_MODE& cullMode, const D3D11_FILL_MODE& fillMode)
	{
		SAFE_RELEASE(m_pd3dRasterizerState);

		D3D11_RASTERIZER_DESC d3dRasterizerDesc;
		ZeroMemory(&d3dRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
		d3dRasterizerDesc.CullMode = cullMode;
		d3dRasterizerDesc.FillMode = fillMode;
		d3dRasterizerDesc.DepthClipEnable = true;
		gDevice->CreateRasterizerState(&d3dRasterizerDesc, &m_pd3dRasterizerState);

		if (m_pd3dRasterizerState)
			return WARP_RESULT_ENUM::OK;

		return CWARPResult::FAIL_CREATE_RS(ERR_INFO);
	}
	WARP_RESULT_ENUM CDXObject::CreateDepthStencilState()
	{
		SAFE_RELEASE(m_pd3dDepthStencilState);
		return WARP_RESULT_ENUM::OK;
	}

	void CDXObject::SetBlendState(ID3D11BlendState *pd3dBlendState)
	{
		if (nullptr == pd3dBlendState) return;

		if (m_pd3dBlendState)m_pd3dBlendState->Release();
		m_pd3dBlendState = nullptr;
		m_pd3dBlendState = pd3dBlendState;

	}

	void CDXObject::SetBlendState(const std::string& name)
	{
		m_strBlendstate = name;
	}
*/
