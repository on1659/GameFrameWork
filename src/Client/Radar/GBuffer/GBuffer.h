
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

class CCamera;

struct RTVInfo
{
	ID3D11Texture2D*			txt{ nullptr };
	ID3D11ShaderResourceView*	srv{ nullptr };
	ID3D11RenderTargetView*		rtv{ nullptr };
	ID3D11DepthStencilView*     dsv{ nullptr };

	RTVInfo()
	{
	}

	void operator=(ID3D11RenderTargetView* inputRTV)
	{
		if (rtv)rtv->Release();
		rtv = inputRTV;
	}

	ID3D11RenderTargetView* operator()()
	{
		return rtv;
	}

	void SetRTV(const std::string& name, D3D11_TEXTURE2D_DESC& dtd, D3D11_RENDER_TARGET_VIEW_DESC& rtsvd, D3D11_SHADER_RESOURCE_VIEW_DESC& dsrvd)
	{
		std::string setName;
		setName = name;
		setName += " - TXT";
		gDevice->CreateTexture2D(&dtd, NULL, &txt);
		Radar::DXUT_SetDebugName(txt, setName.c_str());


		setName.clear();
		setName = name;
		setName += " - RTV";
		auto result = gDevice->CreateRenderTargetView(txt, &rtsvd, &rtv);
		Radar::DXUT_SetDebugName(rtv, setName.c_str());

		setName.clear();
		setName = name;
		setName += " - SRV";
		result = gDevice->CreateShaderResourceView(txt, &dsrvd, &srv);
		Radar::DXUT_SetDebugName(srv, setName.c_str());
	}

	void Release()
	{
		clear();
	}

	void clear()
	{
		SAFE_RELEASE(txt);
		SAFE_RELEASE(srv);
		SAFE_RELEASE(rtv);
		SAFE_RELEASE(dsv);
	}

};

class CGBuffer : public CDXObject
{

	// Texture formats
	static const DXGI_FORMAT depthStencilTextureFormat = DXGI_FORMAT_R24G8_TYPELESS;
	static const DXGI_FORMAT basicColorTextureFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	static const DXGI_FORMAT normalTextureFormat = DXGI_FORMAT_R11G11B10_FLOAT;
	static const DXGI_FORMAT specPowTextureFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Render view formats
	static const DXGI_FORMAT depthStencilRenderViewFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	static const DXGI_FORMAT basicColorRenderViewFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	static const DXGI_FORMAT normalRenderViewFormat = DXGI_FORMAT_R11G11B10_FLOAT;
	static const DXGI_FORMAT specPowRenderViewFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Resource view formats
	static const DXGI_FORMAT depthStencilResourceViewFormat = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	static const DXGI_FORMAT basicColorResourceViewFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	static const DXGI_FORMAT normalResourceViewFormat = DXGI_FORMAT_R11G11B10_FLOAT;
	static const DXGI_FORMAT specPowResourceViewFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

public:
	CGBuffer(const std::string& name = "GBuffer");

	~CGBuffer();

	HRESULT Init(UINT width, UINT height);
	void Deinit();

	void PreRender(ID3D11DepthStencilView* pDSV);
	void PostRender(ID3D11DepthStencilView* pDSV = nullptr);
	void PrepareForUnpack(CCamera* pCamera);
	void ClearRender();
	ID3D11DepthStencilView* GetReadOnlyDSV() const;

private:
	HRESULT RTVCreate(const UINT& width, const UINT& height);
	HRESULT DepthCreate(const UINT& width, const UINT& height);


	ID3D11Buffer* m_pGBufferUnpackCB;

	RTVInfo		m_Albedo;
	RTVInfo		m_Normal;
	RTVInfo		m_SpecPower;


	// GBuffer DepthStencil
	ID3D11Texture2D* m_DepthStencilRT;
	ID3D11DepthStencilView* m_DepthStencilDSV;
	ID3D11DepthStencilView* m_DepthStencilReadOnlyDSV;
	ID3D11ShaderResourceView* m_DepthStencilSRV;
	ID3D11DepthStencilState *m_DepthStencilState;

	ID3D11RenderTargetView	 *m_arrRTVs[RNDER_TARGET_NUM]{ nullptr, nullptr, nullptr };
	ID3D11ShaderResourceView *m_arrSRVs[RNDER_TARGET_NUM]{ nullptr, nullptr, nullptr };

};
