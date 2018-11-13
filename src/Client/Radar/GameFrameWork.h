#pragma once

// https://code-examples.net/ko/q/8d0b80
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

class CGameTimer;

class CGameFrameWork
	: public CSingleTonBase<CGameFrameWork>
{

public:
	CGameFrameWork(tstring name = _XTT("CGameFrameWork"));

	~CGameFrameWork();
	
	virtual WARP_RESULT_ENUM Initialize() override;

	virtual WARP_RESULT_ENUM Start(void* pdata) override;

	virtual WARP_RESULT_ENUM LateStart()override;

	virtual WARP_RESULT_ENUM Reset() override;

	virtual WARP_RESULT_ENUM Release() override;

	void Update();

	void Render();

	WARP_RESULT_ENUM CreateDeivce();

	WARP_RESULT_ENUM CreateCommandQueueAndList();

	WARP_RESULT_ENUM CreateRtvAndDsvDescriptorHeaps();

	WARP_RESULT_ENUM CreateCommandComplete();

	WARP_RESULT_ENUM CreateSwapChain();

	WARP_RESULT_ENUM OnResizeBackBuffers(const WORD width, const WORD height);
	
	void CreateRenderTargetViews();

	void CreateDepthStencilView();

	WARP_RESULT_ENUM WaitForGpuComplete();

	WARP_RESULT_ENUM MoveToNextFrame();

private:
	HINSTANCE						m_hInstance;
	HWND							m_hWnd;
	RECT							m_rcClient;
	int								m_nWndClientWidth;
	int								m_nWndClientHeight;


	ComPtr<D3DFactory>				m_pdxgiFactory;
	DXGISSwapChain					*m_pDXGISwapChain;
	// ComPtr<DXGISSwapChain>		m_pDXGISwapChain;
	        
	bool							m_bMsaa4xEnable;
	UINT							m_nMsaa4xQualityLevels;

	static const UINT				m_nSwapChainBuffers = 2;
	UINT							m_nSwapChainBufferIndex;

	ComPtr<ID3D12Fence>				m_pd3dFence;
	UINT64							m_nFenceValues[SWAP_CHAIN_BUFFER_COUNT];
	HANDLE							m_hFenceEvent;

	ComPtr<ID3D12Resource>			m_ppd3dSwapChainBackBuffers[SWAP_CHAIN_BUFFER_COUNT];
	ComPtr<ID3D12DescriptorHeap>	m_pd3dRtvDescriptorHeap;
	UINT							m_nRtvDescriptorIncrementSize;
	D3D12_CPU_DESCRIPTOR_HANDLE		m_pd3dRtvSwapChainBackBufferCPUHandles[SWAP_CHAIN_BUFFER_COUNT];

	ComPtr<ID3D12Resource>			m_pd3dDepthStencilBuffer;
	ComPtr<ID3D12DescriptorHeap>	m_pd3dDsvDescriptorHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE		m_d3dDsvDepthStencilBufferCPUHandle;

	int lastTerm{ 0 };
	int lastValue{ 0 };

#ifdef _DEBUG
	ID3D12Debug						*m_pd3dDebugController;
#endif //_DEBUG

#ifdef NOSCENE_CREATE_CUBE_
private:

	//Camera
	CCamera * m_pCamera;

	ComPtr<ID3D12RootSignature>		m_mRootSignature;

	// Mesh
	ComPtr<D3DBuffer>m_VertexBufferGPU = nullptr;
	ComPtr<D3DBuffer> uploadBuffer;

	//unique_ptr<UploadBuffer<D3DBuffer>>	m_TextureuploadBuffer;
	ComPtr<D3DBuffer>m_TextureuploadBuffer = nullptr;
	ComPtr<D3DBuffer>m_pTexture = nullptr;
	ComPtr<ID3D12DescriptorHeap>m_pd3dCbvSrvDescriptorHeap = NULL;
	ComPtr<ID3D12DescriptorHeap>m_SamplerHeap = NULL;


	ComPtr<D3DBuffer> vsBuffer;
	ComPtr<D3DBuffer> psBuffer;
	ComPtr<D3DBuffer> gsBuffer;

	D3D12_VERTEX_BUFFER_VIEW		vsBufferView;
	D3D12_INDEX_BUFFER_VIEW			inBufferView;

	// GameObject
	ComPtr<ID3D12DescriptorHeap>			descriptorHeap;
	unique_ptr<UploadBuffer<XMFLOAT4X4>>	cbWorldMatrix;
	//D3DBuffer*							cbWorldMatrix;

	// XMFLOAT4X4					worldMatrix;
	// D3DBuffer				*m_pd3dcbGameObject = NULL;			// constant버퍼

	//Shader
	ComPtr<ID3DBlob> vsShader;
	ComPtr<ID3DBlob> psShader;
	ComPtr<ID3DBlob> gsShader;

	//vector<D3D12_INPUT_ELEMENT_DESC> inputLayOut;
	D3D12_INPUT_LAYOUT_DESC			inputLayOut;

	ComPtr<ID3D12PipelineState>		pipeState;

public:
	void CreateCube();
	void RenderCube(ID3D12GraphicsCommandList *pd3dCommandList);
	void UpdateCube(ID3D12GraphicsCommandList *pd3dCommandList);
	void ReleaseCube();
#endif // NOSCENE_CREATE_CUBE_
};

