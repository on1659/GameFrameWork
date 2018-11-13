
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.


#include "PreComplie.h"

#pragma once
#include "GBuffer.h"

UINT8 g_nSkyStencilFlag = 0;
UINT8 g_nSceneStencilFlag = 0;

#pragma pack(push,1)
struct CB_GBUFFER_UNPACK
{
	D3DXVECTOR4 PerspectiveValues;
	D3DXMATRIX  ViewInv;
};
#pragma pack(pop)

CGBuffer::CGBuffer(const std::string& name)
	: m_pGBufferUnpackCB(nullptr)
	, m_DepthStencilRT(nullptr)
	, m_DepthStencilDSV(nullptr)
	, m_DepthStencilReadOnlyDSV(nullptr)
	, m_DepthStencilSRV(nullptr)
	, m_DepthStencilState(nullptr)
{

}

CGBuffer::~CGBuffer()
{

}

HRESULT CGBuffer::Init(UINT width, UINT height)
{
	HRESULT hr;
	
	Deinit(); // Clear the previous targets
	
	hr = RTVCreate(width, height);
	if (hr != S_OK) return hr;

	hr = DepthCreate(width, height);
	if (hr != S_OK) return hr;

	return S_OK;
}

HRESULT CGBuffer::RTVCreate(const UINT& width, const UINT& height)
{
	HRESULT hr = S_OK;

	// Allocate the depth stencil target
	D3D11_TEXTURE2D_DESC dtd =
	{
		width, //UINT Width;
		height, //UINT Height;
		1, //UINT MipLevels;
		1, //UINT ArraySize;
		DXGI_FORMAT_R32G32B32A32_FLOAT, //DXGI_FORMAT Format;
		1, //DXGI_SAMPLE_DESC SampleDesc;
		0,
		D3D11_USAGE_DEFAULT,//D3D11_USAGE Usage;
		D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE,//UINT BindFlags;
		0,//UINT CPUAccessFlags;
		0//UINT MiscFlags;    
	};

	{
		D3D11_RENDER_TARGET_VIEW_DESC rtsvd =
		{
			basicColorRenderViewFormat,
			D3D11_RTV_DIMENSION_TEXTURE2D
		};

		// Create the resource views
		D3D11_SHADER_RESOURCE_VIEW_DESC dsrvd =
		{
			basicColorResourceViewFormat,
			D3D11_SRV_DIMENSION_TEXTURE2D,
			0,
			0
		};

		dtd.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		dtd.Format = basicColorTextureFormat;
		rtsvd.Format = basicColorRenderViewFormat;
		dsrvd.Format = basicColorRenderViewFormat;
		dsrvd.Texture2D.MipLevels = 1;

		m_Albedo.SetRTV("GbufferAlbedo", dtd, rtsvd, dsrvd);

		dtd.Format = normalTextureFormat;
		rtsvd.Format = normalRenderViewFormat;
		dsrvd.Format = normalRenderViewFormat;
		m_Normal.SetRTV("GbufferNormal", dtd, rtsvd, dsrvd);

		dtd.Format = specPowTextureFormat;
		dsrvd.Format = specPowRenderViewFormat;
		rtsvd.Format = specPowRenderViewFormat;
		m_SpecPower.SetRTV("GbufferSpecPower", dtd, rtsvd, dsrvd);
	}

	return S_OK;
}

HRESULT CGBuffer::DepthCreate(const UINT& width, const UINT& height)
{
	HRESULT hr;

	// Allocate the depth stencil target
	D3D11_TEXTURE2D_DESC dtd =
	{
		width, //UINT Width;
		height, //UINT Height;
		1, //UINT MipLevels;
		1, //UINT ArraySize;
		DXGI_FORMAT_R32G32B32A32_FLOAT, //DXGI_FORMAT Format;
		1, //DXGI_SAMPLE_DESC SampleDesc;
		0,
		D3D11_USAGE_DEFAULT,//D3D11_USAGE Usage;
		D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE,//UINT BindFlags;
		0,//UINT CPUAccessFlags;
		0//UINT MiscFlags;    
	};	

	D3D11_DEPTH_STENCIL_DESC descDepth;
	descDepth.DepthEnable = TRUE;
	descDepth.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	descDepth.DepthFunc = D3D11_COMPARISON_LESS;
	descDepth.StencilEnable = TRUE;
	descDepth.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	descDepth.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	const D3D11_DEPTH_STENCILOP_DESC stencilMarkOp = { D3D11_STENCIL_OP_REPLACE, D3D11_STENCIL_OP_REPLACE, D3D11_STENCIL_OP_REPLACE, D3D11_COMPARISON_ALWAYS };
	descDepth.FrontFace = stencilMarkOp;
	descDepth.BackFace = stencilMarkOp;
	V_RETURN(gDevice->CreateDepthStencilState(&descDepth, &m_DepthStencilState));
	Radar::DXUT_SetDebugName(m_DepthStencilState, "GBuffer - Depth Stencil Mark DS");

	// Create constant buffers
	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(cbDesc));
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.ByteWidth = sizeof(CB_GBUFFER_UNPACK);
	V_RETURN(gDevice->CreateBuffer(&cbDesc, NULL, &m_pGBufferUnpackCB));
	Radar::DXUT_SetDebugName(m_pGBufferUnpackCB, "GBufferUnpack CB");

	// Create the render target views
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd =
	{
		depthStencilRenderViewFormat,
		D3D11_DSV_DIMENSION_TEXTURE2D,
		0
	};

	dtd.Format = depthStencilTextureFormat;
	V_RETURN(gDevice->CreateTexture2D(&dtd, NULL, &m_DepthStencilRT));
	Radar::DXUT_SetDebugName(m_DepthStencilRT, "GBuffer - Depth Stencil");

	V_RETURN(gDevice->CreateDepthStencilView(m_DepthStencilRT, &dsvd, &m_DepthStencilDSV));
	Radar::DXUT_SetDebugName(m_DepthStencilDSV, "GBuffer - Depth Stencil DSV");

	dsvd.Flags = D3D11_DSV_READ_ONLY_DEPTH | D3D11_DSV_READ_ONLY_STENCIL;
	V_RETURN(gDevice->CreateDepthStencilView(m_DepthStencilRT, &dsvd, &m_DepthStencilReadOnlyDSV));
	Radar::DXUT_SetDebugName(m_DepthStencilReadOnlyDSV, "GBuffer - Depth Stencil Read Only DSV");


	// Create the resource views
	D3D11_SHADER_RESOURCE_VIEW_DESC dsrvd =
	{
		depthStencilResourceViewFormat,
		D3D11_SRV_DIMENSION_TEXTURE2D,
		0,
		0
	};
	dsrvd.Texture2D.MipLevels = 1;
	V_RETURN(gDevice->CreateShaderResourceView(m_DepthStencilRT, &dsrvd, &m_DepthStencilSRV));
	Radar::DXUT_SetDebugName(m_DepthStencilSRV, "GBuffer - Depth SRV");

	if (m_Albedo.srv && m_Normal.srv && m_SpecPower.srv)
	{
		m_arrSRVs[0] = m_Albedo.srv;
		m_arrSRVs[1] = m_Normal.srv;
		m_arrSRVs[2] = m_SpecPower.srv;

		m_arrRTVs[0] = m_Albedo.rtv;
		m_arrRTVs[1] = m_Normal.rtv;
		m_arrRTVs[2] = m_SpecPower.rtv;
	}
	return S_OK;
}

void CGBuffer::Deinit()
{
	SAFE_RELEASE( m_pGBufferUnpackCB );

	// Clear all allocated targets
	SAFE_RELEASE( m_DepthStencilRT );

	// Clear all views
	SAFE_RELEASE( m_DepthStencilDSV );
	SAFE_RELEASE( m_DepthStencilReadOnlyDSV );
	SAFE_RELEASE( m_DepthStencilSRV );

	// Clear the depth stencil state
	SAFE_RELEASE( m_DepthStencilState );

	
	m_Albedo.Release();
	m_Normal.Release();
	m_SpecPower.Release();

	for (int i = 0; i < RNDER_TARGET_NUM; ++i)
	{
		m_arrRTVs[i] = nullptr;
		m_arrSRVs[i] = nullptr;
	}

}

void CGBuffer::PreRender(ID3D11DepthStencilView* pDSV)
{
#ifdef _USE_GBUFFER_CHANGE_171001_
	// Clear the depth stencil
	gDeviceContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);

	// You only need to do this if your scene doesn't cover the whole visible area
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	gDeviceContext->ClearRenderTargetView(m_Albedo.rtv, ClearColor);
	gDeviceContext->ClearRenderTargetView(m_Normal.rtv, ClearColor);
	gDeviceContext->ClearRenderTargetView(m_SpecPower.rtv, ClearColor);

	// Bind all the render targets togther
	ID3D11RenderTargetView* rt[3] = { m_Albedo.rtv, m_Normal.rtv, m_SpecPower.rtv };
	gDeviceContext->OMSetRenderTargets(3, rt, pDSV);

	gDeviceContext->OMSetDepthStencilState(m_DepthStencilState, 1);

#else // _USE_GBUFFER_CHANGE_171001_

	// Clear the depth stencil
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	gDeviceContext->ClearRenderTargetView( m_Albedo.rtv, ClearColor );
	gDeviceContext->ClearRenderTargetView( m_Normal.rtv, ClearColor );
	gDeviceContext->ClearRenderTargetView( m_SpecPower.rtv, ClearColor );
	
	gDeviceContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);
	
	// Bind all the render targets togther
	gDeviceContext->OMSetRenderTargets( 3, m_arrRTVs, pDSV);

	gDeviceContext->OMSetDepthStencilState(m_DepthStencilState, 1);
#endif // _USE_GBUFFER_CHANGE_171001_

}

void CGBuffer::PostRender(ID3D11DepthStencilView* pDSV /*= nullptr*/ )
{
#ifdef _USE_GBUFFER_CHANGE_171001_
	gDeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Little cleanup
	ID3D11RenderTargetView* rt[3] = { NULL, NULL, NULL };
	gDeviceContext->OMSetRenderTargets(3, rt, m_DepthStencilReadOnlyDSV);
#else // _USE_GBUFFER_CHANGE_171001_

	// Little cleanup
	ID3D11RenderTargetView* rt[3] = { NULL, NULL, NULL };
	gDeviceContext->OMSetRenderTargets(3, rt, m_DepthStencilReadOnlyDSV);
	
	gDeviceContext->PSSetShaderResources(0, RNDER_TARGET_NUM, m_arrSRVs);
#endif // _USE_GBUFFER_CHANGE_171001_
}


void CGBuffer::PrepareForUnpack(CCamera* pCamera)
{
	//HRESULT hr;
	//
	//// Fill the GBuffer unpack constant buffer
	//D3D11_MAPPED_SUBRESOURCE MappedResource;
	//gDeviceContext->Map( m_pGBufferUnpackCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
	//CB_GBUFFER_UNPACK* pGBufferUnpackCB = ( CB_GBUFFER_UNPACK* )MappedResource.pData;
	//auto pProj = pCamera->GetProjectionMatrix();
	//pGBufferUnpackCB->PerspectiveValues.x = 1.0f / pProj->m[0][0];
	//pGBufferUnpackCB->PerspectiveValues.y = 1.0f / pProj->m[1][1];
	//pGBufferUnpackCB->PerspectiveValues.z = pProj->m[3][2];
	//pGBufferUnpackCB->PerspectiveValues.w = -pProj->m[2][2];
	//D3DXMatrixTranspose( &pGBufferUnpackCB->ViewInv, g_Camera.GetWorldMatrix() );
	//gDeviceContext->Unmap( m_pGBufferUnpackCB, 0 );
	//
	//gDeviceContext->PSSetConstantBuffers( 0, 1, &m_pGBufferUnpackCB );
}
void CGBuffer::ClearRender()
{
	gDeviceContext->PSSetShaderResources(0, 3, m_arrSRVs);
}

ID3D11DepthStencilView* CGBuffer::GetReadOnlyDSV() const
{
	return m_DepthStencilReadOnlyDSV;
}
